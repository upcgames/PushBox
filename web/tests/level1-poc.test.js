import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';
import { levelFromTiled } from '../src/level1-poc/level.js';
import { createSession } from '../src/level1-poc/session.js';

const map = JSON.parse(readFileSync(new URL('../public/level1-poc/level1.tmj', import.meta.url), 'utf8'));
const level = levelFromTiled(map);
const commands = { W: 'up', S: 'down', A: 'left', D: 'right' };
const send = (session, key) => session.command(key === 'R' ? { type: 'undo' } : { type: 'move', direction: commands[key] });

test('Tiled conversion preserves extracted level-one collision and artwork data', () => {
  const original = JSON.parse(readFileSync(new URL('../pushbox_modules/maps_json/collision_data.json', import.meta.url), 'utf8'))['1'];
  for (const [role, key] of [['walls', 'walls'], ['boxes', 'boxes'], ['targets', 'holes']]) {
    assert.deepEqual(level[role].map(({ x, y }) => [x, y]), original[key]);
  }
  assert.deepEqual(level.player, { x: 36, y: 34 });
  assert.equal(map.layers[0].data.length, 80 * 60);
});

test('headless sessions are isolated and immutable; events observe committed state', () => {
  const first = createSession(level), second = createSession(level);
  const initial = first.getSnapshot();
  let event;
  first.onEvent(value => { event = value; assert.equal(value.version, first.getSnapshot().version); });
  send(first, 'W');
  assert.deepEqual(first.getSnapshot().player, { x: 36, y: 32 });
  assert.deepEqual(second.getSnapshot().player, initial.player);
  assert.deepEqual(initial.player, { x: 36, y: 34 });
  assert.throws(() => { first.getSnapshot().boxes[0].x = 0; }, TypeError);
  assert.equal(event.type, 'playerMoved');
});

// Execute the actual transpiled movement loop and world rules with presentation
// replaced by no-ops. This is an independent behavioral reference, not a second
// implementation of the rules under test.
async function canonicalTrace(keys) {
  const source = name => readFileSync(new URL(`../src/generated/${name}.js`, import.meta.url), 'utf8')
    .replace(/^import .*;\n/gm, '').replace(/export /g, '');
  const noop = () => {};
  const samples = [];
  const pending = [...keys, 'C', 'C', 'C'];
  const global = {
    Ref: class { constructor(value) { this.v = value; } },
    movi: (x, y, direction) => { const delta = { 1: [0, -2], 2: [0, 2], 3: [2, 0], 4: [-2, 0] }[direction]; x.v += delta[0]; y.v += delta[1]; },
    mod: (box, direction) => { const delta = { 1: [0, -2], 2: [0, 2], 3: [2, 0], 4: [-2, 0] }[direction]; box[0] += delta[0]; box[1] += delta[1]; },
    movinv: direction => { direction.v = { 1: 2, 2: 1, 3: 4, 4: 3 }[direction.v]; },
    toupper: key => key.toUpperCase(),
    _getch: async () => {
      if (samples.length <= keys.length) samples.push(JSON.parse(JSON.stringify(context.readMovement())));
      assert.ok(pending.length, 'Canonical input exhausted');
      return pending.shift();
    },
  };
  for (const name of ['CuadroDeVidas', 'limpiartecla', 'Sleep', 'PintarCaja', 'PintarHueco',
    'PintarMovil', 'PintarPortal', 'PBorrar', 'Retroceder', 'SonidoMovilSeMueve',
    'SonidoMovilNoSeMueve', 'SonidoCajaHueco', 'Musicatiempo', 'PortalInteractivo',
    'Teletransporte', 'runAnim', 'InterfazYouWin', 'InterfazYouLose', 'PintarMuerte']) global[name] = noop;
  const context = vm.createContext(global);
  vm.runInContext(source('world_logic'), context);
  vm.runInContext(source('game_logic').replace('let posicion = 1;', `let posicion = 1;
    globalThis.readMovement = () => ({ player: { x, y }, steps: cantmovs, undoAvailable: posicion - 1,
      boxes: Cajas[1].slice(0, Cantidades[1][0]).map(([x, y]) => ({ x, y })) });`), context);
  const points = array => array.map(({ x, y }) => [x, y]);
  await context.ControlDeMovimiento({ v: 1 }, { v: 5 }, level.player.x, level.player.y,
    [null, points(level.boxes)], [null, points(level.walls)], [null, []], [null, points(level.targets)],
    [null, [4, 52, 0, 4]], Array.from({ length: 6 }, () => Array(5).fill(0)), [], { v: false });
  return samples;
}

test('walking, pushing, blocked moves and bounded undo match the port after every command', async () => {
  const traces = ['AWWDDRR', 'WWWRSSAADDAAWWDDR', 'AAAAAWWWWDDDDSSSSRRRRRR', 'DDWWWWWWAASSSSDDRR'];
  for (const trace of traces) {
    const reference = await canonicalTrace([...trace]);
    const session = createSession(level);
    const actual = [];
    const take = () => {
      const state = session.getSnapshot();
      actual.push({ player: state.player, steps: state.steps, undoAvailable: state.undoAvailable,
        boxes: state.boxes.map(({ x, y }) => ({ x, y })) });
    };
    take();
    for (const key of trace) { send(session, key); take(); }
    assert.deepEqual(actual, reference, trace);
  }
});

test('pause gates commands; move-budget loss and retry preserve remaining lives', () => {
  const session = createSession({ ...level, moveLimit: 2 });
  session.command({ type: 'pause' });
  assert.equal(send(session, 'W'), false);
  session.command({ type: 'pause' });
  send(session, 'W'); send(session, 'S');
  assert.equal(session.getSnapshot().phase, 'lifeLost');
  assert.equal(session.getSnapshot().lives, 4);
  assert.equal(send(session, 'S'), false);
  session.command({ type: 'retry' });
  assert.equal(session.getSnapshot().lives, 4);
  assert.equal(session.getSnapshot().steps, 0);
  assert.deepEqual(session.getSnapshot().player, level.player);
  session.command({ type: 'restart' });
  assert.equal(session.getSnapshot().lives, 5);
});

test('covering targets opens the portal, entering it completes level one without a next scene', () => {
  const fixture = { ...level, walls: [], player: { x: 36, y: 34 }, boxes: [{ x: 38, y: 34 }],
    targets: [{ x: 40, y: 34 }], portal: { x: 38, y: 34 }, moveLimit: 1 };
  const session = createSession(fixture);
  const events = [];
  session.onEvent(event => events.push(event.type));
  send(session, 'D');
  assert.equal(session.getSnapshot().portal.active, true);
  assert.equal(session.getSnapshot().phase, 'completed');
  assert.equal(session.getSnapshot().level, 1);
  assert.equal(session.getSnapshot().lives, 5, 'Portal completion wins before the budget check');
  assert.deepEqual(events, ['playerMoved', 'boxPushed', 'portalChanged', 'levelCompleted']);
  assert.equal(send(session, 'A'), false);
});

test('removing the renderer subscription leaves gameplay operational; disposal rejects commands', () => {
  const session = createSession(level);
  let updates = 0;
  const stop = session.subscribe(() => updates++);
  stop(); send(session, 'W');
  assert.equal(updates, 1);
  assert.equal(session.getSnapshot().steps, 1);
  session.dispose();
  assert.throws(() => send(session, 'W'), /disposed/);
});
