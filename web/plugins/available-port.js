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
    if (strictPort) throw new Error(`Port ${port} is already in use`);
  }
  throw new Error('No available dev-server port');
}

export function availablePortPlugin() {
  return {
    name: 'pushbox-available-port',
    async configureServer(server) {
      if (server.config.server.middlewareMode) return;
      // Vite has already resolved its default and any --port/--strictPort
      // overrides. This hook runs before listening and only in development.
      const settings = server.config.server;
      const port = await findAvailablePort(settings.port, settings.strictPort);
      if (port !== settings.port) {
        server.config.logger.info(`Port ${settings.port} is occupied; using ${port} for PushBox.`);
        settings.port = port;
      }
    },
  };
}
