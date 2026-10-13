import test from 'node:test';
import assert from 'node:assert/strict';
import vm from 'node:vm';
import { readFileSync } from 'node:fs';
import { createRequire } from 'node:module';
import { runtimeStatePlugin } from '../plugins/runtime-state.js';
import { createGameState } from '../src/state/gameState.js';
import { createRuntimeBridge } from '../src/state/runtimeBridge.js';
import { drawBlockedBobby, BLOCKED_DURATION } from '../src/presentation/blockedBobby.js';
import { drawBobby, sampleBobby } from '../src/presentation/bobby.js';
import { VirtualConsole } from '../src/shims/consoleSurface.js';

const require = createRequire(import.meta.resolve('eslint'));
const { parse } = require('espree');
const parser = { parse: source => parse(source, { ecmaVersion: 'latest', sourceType: 'module' }) };
const read = name => readFileSync(new URL(`../src/generated/${name}.js`, import.meta.url), 'utf8');
const executable = source => source.replace(/^import .*;\n/gm, '').replace(/export /g, '');

function fixture(adapted) {
  const writes = [], waits = [], painted = [], phases = [], fills = [];
  const ctx = { fillRect(x, y, width, height) { fills.push({ x, y, width, height, color: this.fillStyle }); }, clearRect() {}, save() {}, restore() {}, beginPath() {}, rect() {}, clip() {},
    fillText(char, x, y) { painted.push({ char, x, y }); } };
  const surface = new VirtualConsole({ getContext: () => ctx }, 80, 63, 14);
  surface.observer = { clear() {}, write: (...args) => writes.push(args) };
  const store = createGameState();
  const bridge = createRuntimeBridge(store);
  store.api.subscribe(state => {
    phases.push(state.playerAnimation);
    surface.setPlayerHidden(!state.playerAnimation || state.playerAnimation === 'TeclasOcultas');
  });
  const noop = () => {};
  const sandbox = vm.createContext({ ...bridge, Console: surface,
    Ref: class { constructor(value) { this.v = value; } },
    ir: (x, y) => surface.SetCursorPosition(x, y),
    colorfondo: value => surface.SetBackgroundColor(value),
    colorletra: value => surface.SetForegroundColor(value),
    Sleep: async ms => waits.push(ms),
    Musicatiempo: noop, MusicaMuerte: noop, SonidoTeletransporte: noop,
    MusicaAparecePortal: noop, MusicaDesaparecePortal: noop, SonidoEndurecimiento: noop,
  });
  for (const name of ['world_objects', 'world_logic']) {
    const source = read(name);
    const result = adapted ? runtimeStatePlugin().transform.call(parser, source, `/src/generated/${name}.js`) : null;
    if (result) parser.parse(result.code);
    vm.runInContext(executable(result?.code || source), sandbox);
  }
  return { sandbox, surface, store, writes, waits, painted, phases, fills };
}

// Real original routines, not reimplemented animation fixtures. Web observation
// must leave every canonical cell write and delay unchanged.
test('Bobby hooks preserve canonical death, teleport, troll and complete undo choreography', async () => {
  for (const name of ['PintarMuerte', 'Teletransporte', 'TeclasOcultas', 'Regresar']) {
    const original = fixture(false), adapted = fixture(true);
    for (const run of [original, adapted]) {
      run.sandbox.PintarMovil(1, 36, 32);
      if (name === 'Regresar') {
        const { Ref } = run.sandbox;
        const boxes = [null, [[30, 30]]], gaps = [null, []], targets = [null, [[32, 30]]];
        const counts = [null, [1, 0, 0, 1]], positions = [[], [1, 34, 32, 3, -1]];
        await run.sandbox.Regresar(1, new Ref(2), new Ref(36), new Ref(32), 3,
          boxes, gaps, targets, counts, positions, []);
      } else {
        await run.sandbox[name](...(name === 'Teletransporte' ? [1, 36, 32] : [36, 32]));
      }
    }
    assert.deepEqual(adapted.writes, original.writes, name);
    assert.deepEqual(adapted.waits, original.waits, name);
    assert.ok(adapted.phases.includes(name), `${name} publishes its actual scope`);
    assert.equal(adapted.store.api.getSnapshot().playerAnimation,
      ['PintarMuerte', 'Teletransporte'].includes(name) ? name : null);
    if (name === 'Regresar') {
      assert.equal(adapted.store.api.getSnapshot().playerDrawing.x, 34);
      assert.equal(adapted.store.api.getSnapshot().playerDrawing.y, 32);
    }
  }
});

test('tagged player glyphs restore without changing the canonical transcript or cursor', () => {
  const { sandbox, surface, writes, painted } = fixture(true);
  sandbox.PintarMovil(1, 36, 32);
  assert.equal(writes.length, 4);
  assert.ok(painted.slice(-4).every(cell => cell.char === ' '));
  const cursor = { x: surface.cursorX, y: surface.cursorY };
  surface.setPlayerHidden(false);
  assert.deepEqual(painted.slice(-4).map(cell => cell.char), ['╔', '╗', '╚', '╝']);
  assert.equal(writes.length, 4);
  assert.deepEqual({ x: surface.cursorX, y: surface.cursorY }, cursor);
  surface.Clear();
  surface.setPlayerHidden(true);
  surface.setPlayerHidden(false);
  assert.equal(surface.cells.flat().filter(Boolean).length, 0);
});

test('animation observation releases nested scopes on errors and stays session-local', async () => {
  const one = fixture(true), two = fixture(true);
  const leave = one.sandbox.enterPlayerAnimation('Regresar');
  one.sandbox.Sleep = async () => { throw new Error('reset'); };
  await assert.rejects(one.sandbox.PintarMuerte(36, 32), /reset/);
  assert.equal(one.store.api.getSnapshot().playerAnimation, 'Regresar');
  assert.equal(two.store.api.getSnapshot().playerAnimation, null);
  leave();
  assert.equal(one.store.api.getSnapshot().playerAnimation, null);
});


test('shared mobile layer yields to canonical phases, pause and disposal', () => {
  const store = createGameState();
  const bridge = createRuntimeBridge(store);
  const drawn = [], images = [], hidden = [], scheduled = new Map(), listeners = new Map();
  const ctx = { clearRect() {}, fillRect() {}, save() {}, restore() {}, beginPath() {}, rect() {}, clip() {},
    translate() {}, scale() {}, fillText: glyph => drawn.push(glyph) };
  const sprite = { width: 28, height: 28, getContext: () => ctx };
  const canvas = { width: 1120, height: 882, ownerDocument: { createElement: () => sprite }, getContext: () => ctx, setAttribute() {}, remove() { this.removed = true; } };
  ctx.canvas = canvas;
  ctx.drawImage = (_sprite, x, y, width, height) => images.push({ x, y, width, height });
  const surface = { tileSize: 14, canvas: { width: 1120, height: 882, parentElement: { append() {} } },
    setPlayerHidden: value => hidden.push(value) };
  let sequence = 0;
  const sandbox = vm.createContext({ drawBobby, sampleBobby, drawBlockedBobby, BLOCKED_DURATION,
    BOBBY_PALETTE: ['#000000', '#ffffff'], performance: { now: () => 500 },
    document: { hidden: false, createElement: () => canvas,
      addEventListener: (name, fn) => listeners.set(name, fn), removeEventListener: name => listeners.delete(name) },
    window: { matchMedia: () => ({ matches: false, addEventListener() {}, removeEventListener() {} }) },
    requestAnimationFrame: fn => { scheduled.set(++sequence, fn); return sequence; },
    cancelAnimationFrame: id => scheduled.delete(id),
  });
  const source = readFileSync(new URL('../src/presentation/mountBobby.js', import.meta.url), 'utf8');
  vm.runInContext(executable(source), sandbox);
  const layer = sandbox.mountBobby(surface, store.api);
  bridge.reportPlayerDraw(1, 36, 32, 9, 1);
  const stopGame = bridge.observeGame(() => ({ level: 1, nextLevel: 1 }));
  const leaveGame = bridge.enterScreen('gameplay');
  assert.equal(hidden.at(-1), true);
  assert.deepEqual(drawn.slice(-4), ['╔', '╗', '╚', '╝']);
  bridge.reportPlayerDraw(1, 38, 32, 9, 1);
  const tick = time => {
    const [id, paint] = scheduled.entries().next().value;
    scheduled.delete(id);
    paint(time);
  };
  tick(545);
  assert.ok(images.at(-1).x < 38 * 14, 'Bobby still travels halfway through A');
  tick(590);
  assert.deepEqual(images.at(-1), { x: 38 * 14, y: 32 * 14, width: 28, height: 28 }, 'A arrives after 90 ms');
  tick(625);
  assert.equal(images.at(-1).width, 26, 'A still contracts during its 70 ms settle');
  tick(660);
  assert.equal(images.at(-1).height, sampleBobby(660).height, 'A resumes the shared idle after 160 ms');
  for (const name of ['Regresar', 'Teletransporte', 'PintarMuerte']) {
    const leave = bridge.enterPlayerAnimation(name);
    assert.equal(hidden.at(-1), false);
    assert.equal(scheduled.size, 0);
    leave();
    // A new canonical drawing is the only way back from a terminal animation.
    if (name !== 'Regresar') assert.equal(hidden.at(-1), false);
    bridge.reportPlayerDraw(1, 34, 32, 9, 1);
    assert.equal(hidden.at(-1), true);
  }
  const leavePause = bridge.enterScreen('InterfazPausa');
  assert.equal(hidden.at(-1), false);
  assert.equal(scheduled.size, 0);
  leavePause();
  assert.equal(hidden.at(-1), true);
  store.event('movementBlocked', { level: 1, direction: { x: 1, y: 0 }, obstacle: null });
  assert.equal(hidden.at(-1), true, 'blocked tremble remains in the mobile rendering layer');
  store.api.setTrollActive(true);
  assert.equal(store.api.getSnapshot().trollActive, true);
  stopGame(); leaveGame();
  assert.equal(hidden.at(-1), false);
  assert.equal(store.api.getSnapshot().trollActive, false);
  layer.dispose();
  assert.equal(canvas.removed, true);
  assert.equal(scheduled.size, 0);
  assert.equal(listeners.size, 0);
});


test('gameplay and portal retain the approved idle, with strength affecting movement only', () => {
  for (const time of [0, 150, 320, 503, 750, 1100, 1500]) {
    const portal = sampleBobby(time);
    const game = sampleBobby(time, { strength: 0.4 });
    assert.deepEqual(game, portal);
    assert.equal(game.height, 28 + Math.round(Math.sin(time / 320) * 4));
    assert.equal(game.width, 28 - Math.round(Math.sin(time / 320)));
  }
});


test('walking and pushing expose original terrain instead of a black destination or stale caja', () => {
  const { sandbox, surface, writes, fills } = fixture(true);
  for (const [x, y, push] of [[36, 30, false], [38, 32, false], [36, 28, true]]) {
    // The original floor routine supplies terrain independently of actors.
    sandbox.PBorrar(1, x, y);
    if (push) sandbox.PintarCaja(1, x, y);
    const before = writes.length;
    sandbox.PintarMovil(1, x, y);
    assert.equal(writes.length - before, 4, 'No extra canonical drawing calls');
    assert.ok(fills.slice(-4).every(cell => cell.color === '#d946ef'), 'destination shows original magenta terrain');
    assert.equal(surface.cells[y][x].background, '#000000', 'canonical player background is retained');
    surface.setPlayerHidden(false);
    assert.ok(fills.slice(-4).every(cell => cell.color === '#000000'), 'canonical effects receive the original black player tile');
    surface.setPlayerHidden(true);
    assert.ok(fills.slice(-4).every(cell => cell.color === '#d946ef'));
  }
  // Dynamic terrain updates come from original bridge/target routines too.
  sandbox.PintarPuente(3, 36, 28);
  sandbox.PintarMovil(3, 36, 28);
  assert.equal(surface.terrainCells[28][36].background, '#06b6d4');
  assert.ok(fills.slice(-4).every(cell => cell.color === '#06b6d4'));
  sandbox.DestruirPuente(3, 36, 28);
  sandbox.PintarMovil(3, 36, 28);
  assert.equal(surface.terrainCells[28][36].background, '#1e3a8a');
  assert.ok(fills.slice(-4).every(cell => cell.color === '#1e3a8a'));
});
