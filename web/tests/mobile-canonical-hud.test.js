import test from 'node:test';
import assert from 'node:assert/strict';
import vm from 'node:vm';
import { readFileSync } from 'node:fs';
import { createRequire } from 'node:module';
import { runtimeStatePlugin } from '../plugins/runtime-state.js';
import { VirtualConsole } from '../src/shims/consoleSurface.js';
import { ConsoleColor } from '../src/shims/consoleColor.js';
import { createGameState } from '../src/state/gameState.js';
import { createRuntimeBridge } from '../src/state/runtimeBridge.js';
import { observeConsole } from '../src/state/consoleTranscript.js';
import { gameplayHudSnapshot } from '../src/presentation/gameplayHud.js';

const { parse } = createRequire(import.meta.resolve('eslint'))('espree');
const parser = { parse: source => parse(source, { ecmaVersion: 'latest', sourceType: 'module' }) };
const read = name => readFileSync(new URL(`../src/generated/${name}.js`, import.meta.url), 'utf8');
const executable = source => source.replace(/^import .*;\n/gm, '').replace(/export /g, '');
function fixture(adapted, hidden = false) {
  const painted = [], fills = [], waits = [], calls = [], tasks = [];
  const ctx = { fillRect(x, y) { fills.push({ x, y, color: this.fillStyle }); }, clearRect() {}, save() {}, restore() {}, beginPath() {}, rect() {}, clip() {}, fillText(char, x, y) { painted.push({ char, x, y }); } };
  const surface = new VirtualConsole({ getContext: () => ctx }, 80, 63, 14);
  const store = createGameState();
  observeConsole(surface, callback => tasks.push(callback), store);
  surface.setDrawScopeHidden('canonical-hud', hidden, 'terrain');
  const terrain = surface.enterDrawScope('board');
  surface.SetBackgroundColor(3);
  for (let y = 59; y <= 61; y++) { surface.SetCursorPosition(0, y); surface.Write('.'.repeat(80)); }
  terrain(); painted.length = fills.length = 0;
  const sandbox = vm.createContext({ ...createRuntimeBridge(store), Console: surface, ConsoleColor,
    Sleep: async ms => waits.push(ms), SonidoHurryUp: () => calls.push('warning'),
    runAnim: async (routine, ...args) => { for await (const delay of routine(...args)) waits.push(delay); },
  });
  vm.runInContext(executable(read('base')), sandbox);
  vm.runInContext(executable(read('world_logic')), sandbox);
  const source = read('gui');
  vm.runInContext(executable(adapted ? runtimeStatePlugin().transform.call(parser, source, '/src/generated/gui.js').code : source), sandbox);
  return { surface, store, sandbox, painted, fills, waits, calls, flush() { tasks.splice(0).forEach(task => task()); } };
}

test('hidden mobile status panel retains original writes, delays, alarm and HUD counter', async () => {
  const desktop = fixture(false), mobile = fixture(true, true);
  for (const view of [desktop, mobile]) {
    await view.sandbox.CuadroDeVidas(1, 5, 0, 1);
    await view.sandbox.CuadroDeVidas(1, 4, 133, 0, true);
    view.flush();
  }
  assert.deepEqual(mobile.store.api.getSnapshot().console, desktop.store.api.getSnapshot().console);
  assert.deepEqual(mobile.waits, desktop.waits);
  assert.deepEqual(mobile.calls, ['warning']);
  assert.ok(mobile.painted.every(cell => cell.char === '.'), 'Board artwork replaces panel text');
  assert.ok(mobile.fills.every(cell => cell.color === '#22c55e'), 'Board artwork replaces panel background');
  assert.equal(mobile.surface.drawScope, null);
  mobile.store.publish({ screen: { id: 'gameplay' }, game: { level: 1, lives: 4, steps: 133 } });
  assert.equal(gameplayHudSnapshot(mobile.store.api.getSnapshot()).remaining, 17);
  mobile.painted.length = 0;
  mobile.surface.setDrawScopeHidden('canonical-hud', false);
  assert.ok(mobile.painted.some(cell => cell.char === 'N'), 'Desktop restores original HUD glyphs');
});

test('scene artwork may overwrite HUD cells; hiding does not mask a fixed console region', async () => {
  const view = fixture(true, true);
  await view.sandbox.CuadroDeVidas(1, 5, 0, 1);
  view.painted.length = 0;
  view.surface.SetCursorPosition(15, 60); view.surface.Write('PAUSA');
  assert.equal(view.painted.map(cell => cell.char).join(''), 'PAUSA');
  view.painted.length = 0;
  const scope = view.surface.enterDrawScope('canonical-hud');
  view.surface.SetCursorPosition(0, 10); view.surface.Write('status'); scope();
  assert.ok(view.painted.every(cell => cell.char === ' '), 'Missing terrain uses black fallback');
});

test('steps warning follows the original warning branch, including mute, reset and errors', async () => {
  const view = fixture(true, true), other = fixture(true, true);
  const during = [];
  view.store.publish({ audio: { muted: true } });
  view.sandbox.Sleep = async () => during.push(view.store.api.getSnapshot().stepsWarning);
  await view.sandbox.CuadroDeVidas(1, 5, 131, 0, true);
  assert.equal(during.length, 25);
  assert.ok(during.every(warning => warning.level === 1 && warning.remaining === 19));
  assert.equal(new Set(during.map(warning => warning.startedAt)).size, 1);
  assert.equal(view.store.api.getSnapshot().stepsWarning, null);
  assert.equal(other.store.api.getSnapshot().stepsWarning, null);
  during.length = 0;
  await view.sandbox.CuadroDeVidas(1, 5, 132, 0, false);
  assert.equal(during.length, 0, 'Ordinary low-step redraw does not trigger the warning');
  view.sandbox.Sleep = async () => { throw new Error('reset'); };
  await assert.rejects(view.sandbox.CuadroDeVidas(1, 5, 131, 0, true), /reset/);
  assert.equal(view.store.api.getSnapshot().stepsWarning, null);
  assert.equal(view.surface.drawScope, null);
});
