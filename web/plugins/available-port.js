import { createServer } from 'node:net';

const ADDRESSES = ['127.0.0.1', '::1', '0.0.0.0', '::'];
const UNSUPPORTED = new Set(['EADDRNOTAVAIL', 'EAFNOSUPPORT', 'EPROTONOSUPPORT']);

function canBind(port, host) {
  return new Promise((resolve, reject) => {
    const probe = createServer();
    probe.once('error', error => {
      if (error.code === 'EADDRINUSE') resolve(false);
      else if (host.includes(':') && UNSUPPORTED.has(error.code)) resolve(true);
      else reject(error);
    });
    probe.listen({ port, host, ...(host.includes(':') ? { ipv6Only: true } : {}) }, () => {
      probe.close(error => error ? reject(error) : resolve(true));
    });
  });
}

export async function findAvailablePort(start, strictPort = false) {
  // Preserve Node's ephemeral-port behavior when explicitly requested.
  if (start === 0) return 0;
  if (!Number.isInteger(start) || start < 1 || start > 65535) throw new Error(`Invalid dev port: ${start}`);
  for (let port = start; port <= 65535; port++) {
    let available = true;
    // Probe sequentially: wildcard and loopback probes must not collide with
    // one another. Closing each probe also leaves no background listeners.
    for (const host of ADDRESSES) {
      if (!await canBind(port, host)) { available = false; break; }
    }
    if (available) return port;
    if (strictPort) throw Object.assign(new Error(`Port ${port} is already in use`), { code: 'EADDRINUSE' });
  }
  throw new Error('No available dev-server port');
}

export function availablePortPlugin() {
  return {
    name: 'pushbox-available-port',
    configureServer(server) {
      if (server.config.server.middlewareMode) return;
      const httpServer = server.httpServer;
      const listen = httpServer.listen.bind(httpServer);
      // During restarts configureServer runs while the old listener is still
      // open. Probe only at listen time, after Vite has closed that listener.
      // Report collisions like a native bind error so Vite handles fallback,
      // strictPort, and retaining the actual port across restarts itself.
      httpServer.listen = (port, ...args) => {
        findAvailablePort(port, true).then(
          () => {
            try { listen(port, ...args); }
            catch (error) { httpServer.emit('error', error); }
          },
          error => httpServer.emit('error', error),
        );
        return httpServer;
      };
    },
  };
}
