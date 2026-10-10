import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { createRequire } from 'node:module';
import vm from 'node:vm';
import { runtimeStatePlugin } from '../plugins/runtime-state.js';
import { GameState } from '../src/state/gameState.js';
import { selectControlMode } from '../src/shell/controlPolicy.js';
import * as bridge from '../src/state/runtimeBridge.js';

// Use the parser from the declared ESLint dependency, matching Vite's ESTree API.
const require = createRequire(import.meta.resolve('eslint'));
const { parse } = require('espree');
const context = { parse: source => parse(source, { ecmaVersion: 'latest', sourceType: 'module' }) };
const read = name => readFileSync(new URL(`../src/generated/${name}.js`, import.meta.url), 'utf8');
const executable = source => source.replace(/^import .*;\n/gm, '').replace(/export /g, '');

test('adapter produces valid JavaScript for each runtime module without editing artifacts', () => {
  for (const name of ['main', 'game_logic', 'interfaces', 'gui']) {
    const original = read(name);
    assert.doesNotMatch(original, /\bGameState\b/, 'Regenerate browser artifacts through the host pipeline');
    const result = runtimeStatePlugin().transform.call(context, original, `/src/generated/${name}.js`);
    context.parse(result.code);
    if (name === 'interfaces' || name === 'gui') {
      const gallery = runtimeStatePlugin().transform.call(context, original, `/src/generated_anim/${name}.js`);
      context.parse(gallery.code);
    }
    assert.equal(read(name), original);
  }
  assert.throws(() => runtimeStatePlugin().transform.call(context, '', '/src/generated/game_logic.js'), /missing/);
  assert.equal(runtimeStatePlugin().transform.call(context, '', '/src/generated/maps.js'), undefined);
});

function runtime(keys, arrays, { x = 36, y = 34, pauseOption = 1 } = {}) {
  const snapshots = [], events = [];
  const off = GameState.subscribe(state => { if (state.game) snapshots.push(state); });
  const offEvents = GameState.on('*', event => events.push(event));
  const noop = () => {};
  const globals = { ...bridge, GameState, console,
    Ref: class { constructor(value) { this.v = value; } },
    _getch: async () => {
      bridge.recordInput(null, 'waiting');
      assert.ok(keys.length, 'test exhausted its input before gameplay exited');
      const key = keys.shift(); bridge.recordInput(key, 'consumed'); return key;
    },
    toupper: key => typeof key === 'string' ? key.toUpperCase() : key,
    movi: (a, b, direction) => { if (direction === 1) b.v -= 2; if (direction === 2) b.v += 2;
      if (direction === 3) a.v += 2; if (direction === 4) a.v -= 2; },
    mod: (box, direction) => { if (direction === 1) box[1] -= 2; if (direction === 2) box[1] += 2;
      if (direction === 3) box[0] += 2; if (direction === 4) box[0] -= 2; },
    movinv: direction => { direction.v = ({ 1: 2, 2: 1, 3: 4, 4: 3 })[direction.v]; },
    limpiartecla: noop, CuadroDeVidas: noop, Sleep: noop,
    PintarCaja: noop, PintarHueco: noop, PintarMovil: noop, PintarPortal: noop,
    PintarPuente: noop, ArmarPuente: noop, PBorrar: noop, PintarMuerte: noop, Retroceder: noop,
    ir: noop, colorfondo: noop, colorletra: noop,
    SonidoMovilSeMueve: noop, SonidoMovilNoSeMueve: noop, SonidoCajaHueco: noop,
    SonidoCajaVacio: noop, Musicatiempo: noop, Teletransporte: noop, PortalInteractivo: noop,
    InterfazYouWin: noop, InterfazYouLose: noop,
    runAnim: noop,
    InterfazPausa: async (matrix, option) => {
      const leave = bridge.enterScreen('InterfazPausa');
      const leaveInput = bridge.enterInput({ kind: 'key', consumer: 'InterfazPausa' });
      try { option.v = pauseOption; } finally { leaveInput(); leave(); }
    },
    Fondo01: noop, mapa01: noop,
    Console: { Write: noop },
  };
  const sandbox = vm.createContext(globals);
  vm.runInContext(executable(read('world_logic')), sandbox);
  // Painting is outside this test; the small fixture deliberately differs from level art.
  sandbox.PonerPuentes = noop;
  const source = read('game_logic');
  const result = runtimeStatePlugin().transform.call(context, source, '/src/generated/game_logic.js');
  vm.runInContext(executable(result.code), sandbox);
  const level = { v: 1 }, lives = { v: 5 }, sound = { v: 1 };
  const positions = Array.from({ length: 200 }, () => Array(5).fill(0));
  const matrix = Array.from({ length: 60 }, () => Array(80).fill(0));
  return sandbox.ControlDeMovimiento(level, lives, x, y,
    arrays.Cajas, arrays.Paredes, arrays.Vacios, arrays.Huecos, arrays.Cantidades, positions, matrix, sound)
    .then(() => ({ snapshots, events, level, lives })).finally(() => { off(); offEvents(); });
}

const board = () => ({ Cajas: [null, [[38, 34]]], Paredes: [null, []],
  Vacios: [null, [[42, 34]]], Huecos: [null, [[40, 34]]], Cantidades: [null, [1, 0, 1, 1]] });

test('rejected pushes report the actual obstacle once per attempt even with sound off', async () => {
  const walls = board();
  walls.Paredes[1] = [[40, 34]]; walls.Cantidades[1][1] = 1;
  const { events, snapshots } = await runtime(['f', 'd', 'd', 'c', 'c', 'c'], walls);
  const hits = events.filter(event => event.type === 'pushBlocked');
  assert.equal(hits.length, 2);
  for (const { payload } of hits) {
    assert.deepEqual(payload.obstacle, { x: 40, y: 34, kind: 'wall' });
    assert.deepEqual(payload.direction, { x: 1, y: 0 });
    assert.equal(payload.box.index, 0);
  }
  assert.ok(snapshots.some(({ game }) => !game.sound && game.steps === 0));
  const boxes = board();
  boxes.Cajas[1].push([40, 34]); boxes.Cantidades[1][0] = 2;
  const result = await runtime(['d', 'c', 'c', 'c'], boxes);
  const blocked = result.events.filter(event => event.type === 'pushBlocked');
  assert.equal(blocked.length, 1);
  assert.equal(blocked[0].payload.obstacle.kind, 'box');
});

test('real movement reports targets, portal activation, undo, pause, bridges and level exit', async () => {
  const { snapshots, level } = await runtime(['d', 'r', 'p', 'd', 'd', 'c', 'c', 'c'], board());
  assert.ok(snapshots.some(({ game }) => game.steps === 1 && game.portal.active && game.board.boxes[0].onTarget));
  assert.ok(snapshots.some(({ game }) => game.steps === 4 && game.player.x === 36 && !game.portal.active));
  assert.ok(snapshots.some(state => selectControlMode(state) === 'paused' && state.game.steps === 4));
  assert.ok(snapshots.some(({ game }) => game.board.gaps.length === 0 && game.board.boxes.length === 0));
  assert.equal(level.v, 2);
  assert.equal(GameState.getSnapshot().game, null);
  assert.equal(GameState.getSnapshot().screen, null);
  assert.equal(GameState.getSnapshot().inputRequest, null);
});

function evaluateModule(name, overrides) {
  const source = read(name);
  const globals = { ...bridge, console, system() {}, Sleep: async () => {}, toupper: key => key.toUpperCase(),
    Ref: class { constructor(value) { this.v = value; } },
    strlen: value => { const end = value.indexOf('\0'); return end === -1 ? value.length : end; } };
  for (const node of context.parse(source).body) {
    if (node.type === 'ImportDeclaration') {
      for (const specifier of node.specifiers) globals[specifier.local.name] = () => {};
    }
  }
  Object.assign(globals, overrides);
  const sandbox = vm.createContext(globals);
  const output = runtimeStatePlugin().transform.call(context, source, `/src/generated/${name}.js`);
  vm.runInContext(executable(output.code), sandbox);
  return sandbox;
}

test('real intro shows warning, choice and text controls only while requested', async () => {
  const modes = [];
  const sandbox = evaluateModule('main', {
    Console: { Write() {}, SetWindowSize() {}, Clear() {} },
    getDevConfig: () => 0,
    runAnim: async () => { assert.equal(selectControlMode(GameState.getSnapshot()), 'none'); },
    Escribir: async () => { assert.equal(selectControlMode(GameState.getSnapshot()), 'none'); },
    _kbhit: () => { assert.equal(selectControlMode(GameState.getSnapshot()), 'continue'); return true; },
    _getch: async () => { modes.push(selectControlMode(GameState.getSnapshot())); return 'E'; },
    scanf: async (format, target) => {
      modes.push(selectControlMode(GameState.getSnapshot()));
      target[0] = format === '%1s' ? '1' : 'A'; target[1] = '\0';
    },
    ControlDeNiveles: async () => { assert.equal(selectControlMode(GameState.getSnapshot()), 'none'); },
  });
  await sandbox.main();
  assert.deepEqual(modes, ['continue', '1v2', 'qwerty']);
  assert.equal(GameState.getSnapshot().inputRequest, null);
});

test('real menu clears confirmation and navigation before exit animations', async () => {
  const modes = [], keys = ['s', 'e'];
  const sandbox = evaluateModule('interfaces', {
    Console: { Write() {} },
    runAnim: async () => { assert.equal(selectControlMode(GameState.getSnapshot()), 'none'); },
    esperartecla: async () => { modes.push(selectControlMode(GameState.getSnapshot())); },
    _getch: async () => { modes.push(selectControlMode(GameState.getSnapshot())); return keys.shift(); },
  });
  const level = { v: 0 };
  sandbox.PushBox = sandbox.Cplusplus = sandbox.OpcionesMenu = () => {};
  await sandbox.MenuPrincipal(level, []);
  assert.equal(level.v, 8);
  assert.deepEqual(modes, ['continue', 'paused', 'paused']);
  assert.equal(GameState.getSnapshot().inputRequest, null);
});

test('real pause restores gameplay input only after pause transitions finish', async () => {
  const parent = bridge.enterScreen('gameplay');
  const parentInput = bridge.enterInput({ kind: 'key', consumer: 'ControlDeMovimiento' });
  const phases = [], keys = ['s', 'w', 'e'];
  const sandbox = evaluateModule('interfaces', {
    Console: { Write() {} },
    Sleep: async () => { phases.push(selectControlMode(GameState.getSnapshot())); },
    _getch: async () => {
      assert.equal(selectControlMode(GameState.getSnapshot()), 'paused');
      return keys.shift();
    },
  });
  sandbox.AsciiFuncion = () => {};
  const option = { v: 0 };
  try {
    await sandbox.InterfazPausa([], option, { v: 1 });
    assert.equal(option.v, 1);
    assert.equal(phases[0], 'none');
    assert.equal(phases.at(-1), 'none');
    assert.equal(selectControlMode(GameState.getSnapshot()), 'dpad');
  } finally { parentInput(); parent(); }
  assert.equal(selectControlMode(GameState.getSnapshot()), 'none');
});

test('death reports the lost life before clearing the finished board', async () => {
  const arrays = board(); arrays.Vacios[1] = [[36, 32]];
  const { snapshots, lives } = await runtime(['w'], arrays);
  assert.equal(lives.v, 4);
  assert.ok(snapshots.some(({ game }) => game.lives === 4));
  assert.equal(GameState.getSnapshot().game, null);
});

test('runtime exceptions detach observation and restore screen context', async () => {
  await assert.rejects(runtime([], board()), /exhausted/);
  assert.equal(GameState.getSnapshot().game, null);
  assert.equal(GameState.getSnapshot().screen, null);
});
