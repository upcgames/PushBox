import test from 'node:test';
import assert from 'node:assert/strict';
import vm from 'node:vm';
import { readFileSync } from 'node:fs';
import { createGameState } from '../src/state/gameState.js';
import { drawExitCue } from '../src/presentation/exitCue.js';

test('mobile exit follows canonical activation, yields during teleport/undo and releases on reset', () => {
  const frames = new Map(), listeners = new Map(), rectangles = [];
  let sequence = 0, enabled = true;
  const context = { clearRect() { rectangles.length = 0; }, save() {}, restore() {}, translate() {}, scale() {},
    fillRect(...args) { rectangles.push(args); } };
  const canvas = { width: 1120, height: 882, setAttribute() {}, getContext: () => context,
    remove() { this.removed = true; } };
  const surface = { tileSize: 14, canvas: { width: 1120, height: 882, parentElement: { append() {} } } };
  const motion = { matches: false, addEventListener() {}, removeEventListener() {} };
  const sandbox = vm.createContext({ drawExitCue, performance: { now: () => 500 },
    document: { hidden: false, createElement: () => canvas,
      addEventListener: (name, fn) => listeners.set(name, fn), removeEventListener: name => listeners.delete(name) },
    window: { matchMedia: () => motion },
    requestAnimationFrame: fn => { frames.set(++sequence, fn); return sequence; },
    cancelAnimationFrame: id => frames.delete(id),
  });
  const source = readFileSync(new URL('../src/presentation/mountExitCue.js', import.meta.url), 'utf8');
  vm.runInContext(source.replace(/^import .*;\n/gm, '').replace(/export /g, ''), sandbox);
  const store = createGameState();
  const exit = sandbox.mountExitCue(surface, store.api, () => enabled);
  const game = { level: 1, nextLevel: 1, grid: { objectSize: 2 }, portal: { x: 36, y: 34, active: false } };
  store.publish({ screen: { id: 'gameplay' }, game });
  assert.equal(rectangles.length, 0);
  const active = { ...game, portal: { ...game.portal, active: true } };
  store.publish({ game: active });
  assert.ok(rectangles.length > 0);
  assert.equal(frames.size, 1);
  // No dependency on board feedback or console pixels.
  store.publish({ console: { lines: [] } });
  assert.ok(rectangles.length > 0);
  for (const playerAnimation of ['Teletransporte', 'Regresar', 'PintarMuerte']) {
    store.publish({ playerAnimation });
    assert.equal(rectangles.length, 0);
    assert.equal(frames.size, 0);
    store.publish({ playerAnimation: null });
    assert.ok(rectangles.length > 0);
  }
  store.publish({ screen: { id: 'InterfazPausa' } });
  assert.equal(rectangles.length, 0);
  store.publish({ screen: { id: 'gameplay' } });
  assert.ok(rectangles.length > 0);
  enabled = false; exit.refresh();
  assert.equal(rectangles.length, 0, 'desktop keeps canonical presentation');
  enabled = true; motion.matches = true; exit.refresh();
  assert.ok(rectangles.length > 0);
  assert.equal(frames.size, 0);
  store.publish({ game: null });
  assert.equal(rectangles.length, 0);
  exit.dispose();
  assert.equal(canvas.removed, true);
  assert.equal(listeners.size, 0);
  store.publish({ game: active });
  assert.equal(rectangles.length, 0);
  assert.equal(frames.size, 0);
});
