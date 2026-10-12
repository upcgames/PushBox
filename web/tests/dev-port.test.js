import test from 'node:test';
import assert from 'node:assert/strict';
import { createServer as createListener } from 'node:net';
import { createServer as createViteServer } from 'vite-plus';
import { findAvailablePort, availablePortPlugin } from '../plugins/available-port.js';
import { mkdtemp, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';

async function occupy(host) {
  const server = createListener();
  await new Promise((resolve, reject) => {
    server.once('error', reject);
    server.listen({ port: 0, host, ...(host.includes(':') ? { ipv6Only: true } : {}) }, resolve);
  });
  return server;
}
const close = server => new Promise((resolve, reject) => server.close(error => error ? reject(error) : resolve()));

for (const host of ['127.0.0.1', '::1']) {
  test(`Vite skips an occupied ${host} port and retains a wildcard LAN listener`, async t => {
    let occupied;
    try { occupied = await occupy(host); }
    catch (error) {
      if (host === '::1' && ['EADDRNOTAVAIL', 'EAFNOSUPPORT', 'EPROTONOSUPPORT'].includes(error.code)) {
        t.skip('IPv6 unavailable on this system'); return;
      }
      throw error;
    }
    t.after(() => close(occupied));
    const port = occupied.address().port;
    // Load the real repo config, with an ephemeral starting point to avoid
    // making this test depend on port 5173 or disturbing existing servers.
    const cacheDir = await mkdtemp(join(tmpdir(), 'pushbox-port-test-'));
    const vite = await createViteServer({ cacheDir, server: { port, open: false, watch: null }, logLevel: 'silent' });
    t.after(async () => { await vite.close(); await rm(cacheDir, { recursive: true, force: true }); });
    await vite.listen();
    const address = vite.httpServer.address();
    assert.ok(address.port > port);
    assert.ok(['::', '0.0.0.0'].includes(address.address), address.address);
    assert.equal(vite.config.server.host, true);
    const response = await fetch(`http://127.0.0.1:${address.port}/index.html`);
    assert.equal(response.status, 200);
  });
}

test('free ports are retained and strictPort rejects occupied ports', async t => {
  const occupied = await occupy('127.0.0.1');
  const port = occupied.address().port;
  t.after(() => close(occupied));
  await assert.rejects(findAvailablePort(port, true), /already in use/);
  const free = await findAvailablePort(port);
  assert.equal(await findAvailablePort(free), free);
  assert.equal(await findAvailablePort(0), 0);
});

test('port probing is not applied to middleware servers', async () => {
  await availablePortPlugin().configureServer({ config: { server: { middlewareMode: true } } });
});
