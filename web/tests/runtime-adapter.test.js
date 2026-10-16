import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { createRequire } from 'node:module';
import vm from 'node:vm';
import { runtimeStatePlugin } from '../plugins/runtime-state.js';
import { setAudioMuted } from '../src/audio/audioState.js';
import { GameState, runtimeState } from '../src/state/gameState.js';
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

test('winner prompt markers survive copy edits and reject invalid boundaries', () => {
  const original = read('interfaces');
  const begin = '// @web:begin congratulations-prompts';
  const end = '// @web:end congratulations-prompts';
  const changedCopy = original.replace("Presiona 'K' para cambiar de nombre o 'E' para salir.", 'Choose an action.');
  const result = runtimeStatePlugin().transform.call(context, changedCopy, '/src/generated/interfaces.js');
  context.parse(result.code);
  assert.match(result.code, /presentPrompt\('InterfazCongratulations', \(\) => Escribir\("Choose an action\."/);
  for (const invalid of [
    original.replace(begin, ''), original.replace(end, ''),
    original.replace(begin, `${begin}\n${begin}`),
    original.replace(begin, '// SWAP').replace(end, begin).replace('// SWAP', end),
    // A marker inside a quoted string does not define a section.
    original.replace(begin, `const markerText = ${JSON.stringify(begin)};`),
    original.replace(begin, '').replace('export async function* InterfazCongratulations', `${begin}\nexport async function* InterfazCongratulations`),
  ]) {
    assert.throws(() => runtimeStatePlugin().transform.call(context, invalid, '/src/generated/interfaces.js'), /@web section/);
  }
});

test('rejection event annotations survive condition changes and reject missing or duplicate markers', () => {
  const original = read('game_logic');
  const changed = original.replace('if (caja <10)', 'if (10 > caja)')
    .replace('if (MovilDentroDeMapa(', 'if (!!MovilDentroDeMapa(');
  assert.notEqual(changed, original);
  const output = runtimeStatePlugin().transform.call(context, changed, '/src/generated/game_logic.js');
  context.parse(output.code);
  assert.equal([...output.code.matchAll(/reportBlockedPush\(mov, caja\);/g)].length, 2);
  assert.equal([...output.code.matchAll(/reportBlockedMove\(mov\);/g)].length, 1);
  for (const name of ['movement-rejected', 'push-rejected', 'locked-push-rejected']) {
    const marker = `// @web:event ${name}`;
    for (const invalid of [original.replace(marker, ''), original.replace(marker, `${marker}\n${marker}`)]) {
      assert.throws(() => runtimeStatePlugin().transform.call(context, invalid,
        '/src/generated/game_logic.js'), new RegExp(`@web event ${name}`));
    }
  }
});

function runtime(keys, arrays, { x = 36, y = 34, pauseOption = 1, startLevel = 1 } = {}) {
  setAudioMuted({ api: GameState, ...runtimeState }, false);
  const snapshots = [], events = [], sounds = [], huds = [];
  const off = GameState.subscribe(state => { if (state.game) snapshots.push(state); });
  const offEvents = GameState.on('*', event => events.push(event));
  const noop = () => {};
  const globals = { ...bridge, GameState, console,
    Ref: class { constructor(value) { this.v = value; } },
    _getch: async () => {
      bridge.recordInput(null, 'waiting');
      assert.ok(keys.length, 'test exhausted its input before gameplay exited');
      const key = keys.shift(); bridge.handleAudioInput(key); bridge.recordInput(key, 'consumed'); return key;
    },
    toupper: key => typeof key === 'string' ? key.toUpperCase() : key,
    movi: (a, b, direction) => { if (direction === 1) b.v -= 2; if (direction === 2) b.v += 2;
      if (direction === 3) a.v += 2; if (direction === 4) a.v -= 2; },
    mod: (box, direction) => { if (direction === 1) box[1] -= 2; if (direction === 2) box[1] += 2;
      if (direction === 3) box[0] += 2; if (direction === 4) box[0] -= 2; },
    movinv: direction => { direction.v = ({ 1: 2, 2: 1, 3: 4, 4: 3 })[direction.v]; },
    limpiartecla: noop, CuadroDeVidas: (...args) => huds.push(args), Sleep: noop,
    PintarCaja: noop, PintarHueco: noop, PintarMovil: noop, PintarPortal: noop,
    PintarPuente: noop, ArmarPuente: noop, PBorrar: noop, PintarMuerte: noop, Retroceder: noop,
    ir: noop, colorfondo: noop, colorletra: noop,
    SonidoMovilSeMueve: kind => sounds.push(`move:${kind}`), SonidoMovilNoSeMueve: noop, SonidoCajaHueco: () => sounds.push('bell'),
    SonidoCajaVacio: noop, Musicatiempo: kind => sounds.push(`undo:${kind}`), Teletransporte: noop, PortalInteractivo: noop,
    InterfazYouWin: noop, InterfazYouLose: noop,
    runAnim: noop, Endurecimiento: async () => sounds.push('hardening'),
    InterfazPausa: async (matrix, option) => {
      const leave = bridge.enterScreen('InterfazPausa');
      const leaveInput = bridge.enterInput({ kind: 'key', consumer: 'InterfazPausa' });
      try { option.v = pauseOption; } finally { leaveInput(); leave(); }
    },
    Fondo01: noop, mapa01: noop,
    Console: { Write: noop, enterDrawScope: () => noop },
  };
  const sandbox = vm.createContext(globals);
  vm.runInContext(executable(read('world_data')), sandbox);
  vm.runInContext(executable(read('world_logic')), sandbox);
  // Painting is outside this test; the small fixture deliberately differs from level art.
  sandbox.PonerPuentes = noop;
  const source = read('game_logic');
  const result = runtimeStatePlugin().transform.call(context, source, '/src/generated/game_logic.js');
  vm.runInContext(executable(result.code), sandbox);
  const level = { v: startLevel }, lives = { v: 5 }, sound = { v: 1 };
  const positions = Array.from({ length: 200 }, () => Array(5).fill(0));
  const matrix = Array.from({ length: 60 }, () => Array(80).fill(0));
  return sandbox.ControlDeMovimiento(level, lives, x, y,
    arrays.Cajas, arrays.Paredes, arrays.Vacios, arrays.Huecos, arrays.Cantidades, positions, matrix, sound)
    .then(() => ({ snapshots, events, sounds, huds, level, lives })).finally(() => { off(); offEvents(); });
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
  assert.ok(snapshots.some(({ game }) => game.steps === 6 && game.player.x === 36 && !game.portal.active));
  assert.ok(snapshots.some(state => selectControlMode(state) === 'paused' && state.game.steps === 6));
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

test('Game Over exit annotation survives drawing changes and rejects missing boundaries', () => {
  const original = read('interfaces');
  const changed = original.replace('yield* GameOver(46, 1, 9, 219, 1);', 'yield* GameOver(40, 2, 2, 219, 0);');
  assert.notEqual(changed, original);
  const output = runtimeStatePlugin().transform.call(context, changed, '/src/generated/interfaces.js');
  context.parse(output.code);
  assert.match(output.code, /presentScene\('InterfazGameOver'/);
  for (const marker of ['// @web:begin game-over-exit', '// @web:end game-over-exit']) {
    assert.throws(() => runtimeStatePlugin().transform.call(context,
      original.replace(marker, ''), '/src/generated/interfaces.js'), /@web section game-over-exit/);
  }
});

test('mobile Game Over waits for Salir before erasing; desktop retains automatic exit', async () => {
  for (const mobile of [true, false]) {
    const stopOverride = GameState.registerPresentationOverride('InterfazGameOver', () => mobile);
    const drawings = []; let release, notify, flushed = 0;
    const waiting = new Promise(resolve => { notify = resolve; });
    const sandbox = evaluateModule('interfaces', {
      FlushConsoleInputBuffer() { flushed++; },
      _getch: () => { notify(); return new Promise(resolve => { release = resolve; }); },
    });
    sandbox.GameOver = async function* (x, y, color) { drawings.push(color); yield 0; };
    sandbox.desvanecimiento = async function* () { yield 0; };
    sandbox.jokerGif = async function* () { yield 0; };
    const done = (async () => { for await (const delay of sandbox.InterfazGameOver([])) { void delay; } })();
    try {
      if (mobile) {
        await waiting;
        assert.deepEqual(drawings, [1, 8], 'The final visible artwork remains until Salir');
        assert.equal(selectControlMode(GameState.getSnapshot()), 'gameover');
        assert.equal(flushed, 1, 'Earlier keypresses cannot dismiss the scene');
        release('e');
      }
      await done;
      assert.deepEqual(drawings, [1, 8, 9]);
      assert.equal(GameState.getSnapshot().inputRequest, null);
      if (!mobile) assert.equal(flushed, 0);
    } finally { stopOverride(); }
  }
});

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


test('rejected walking emits structured blocked feedback once, independently of sound', async () => {
  const arrays = board();
  arrays.Paredes[1] = [[36, 32]]; arrays.Cantidades[1][1] = 1;
  const { events } = await runtime(['f', 'w', 'w', 'c', 'c', 'c'], arrays);
  const blocked = events.filter(event => event.type === 'movementBlocked');
  assert.equal(blocked.length, 2);
  for (const { payload } of blocked) {
    assert.deepEqual(payload.player, { x: 36, y: 34 });
    assert.deepEqual(payload.direction, { x: 0, y: -1 });
    assert.deepEqual(payload.obstacle, { x: 36, y: 32, kind: 'wall' });
  }
  assert.equal(events.filter(event => event.type === 'pushBlocked').length, 0);
  const push = board();
  push.Paredes[1] = [[40, 34]]; push.Cantidades[1][1] = 1;
  const pushed = await runtime(['f', 'd', 'c', 'c', 'c'], push);
  assert.equal(pushed.events.filter(event => event.type === 'movementBlocked').length, 1);
});


test('original pause exit reports its selected action before restoring gameplay', async () => {
  for (const [keys, expected] of [[['e'], 1], [['s', 'e'], 2], [['s', 's', 'e'], 3]]) {
    const parent = bridge.enterScreen('gameplay');
    const exits = [];
    const stop = GameState.on('screenExited', event => {
      if (event.screen.id === 'InterfazPausa') exits.push({ option: event.option, screen: GameState.getSnapshot().screen.id });
    });
    const sandbox = evaluateModule('interfaces', { Console: { Write() {} }, Sleep: async () => {}, _getch: async () => keys.shift() });
    sandbox.AsciiFuncion = () => {};
    try {
      await sandbox.InterfazPausa([], { v: 0 }, { v: 1 });
      assert.deepEqual(exits, [{ option: expected, screen: 'InterfazPausa' }]);
      assert.equal(GameState.getSnapshot().screen.id, 'gameplay');
    } finally { stop(); parent(); }
  }
});

test('explicit toolbar Resume selects original option one without altering normal P or E behavior', async () => {
  for (const [input, expected] of [[['s', 'Resume'], 1], [['s', 's', 'Resume'], 1], [['s', 'p'], 2], [['s', 's', 'e'], 3]]) {
    const keys = [...input], parent = bridge.enterScreen('gameplay');
    const exits = [], waits = [];
    const stop = GameState.on('screenExited', event => { if (event.screen.id === 'InterfazPausa') exits.push(event.option); });
    const sandbox = evaluateModule('interfaces', { Console: { Write() {} },
      Sleep: async milliseconds => waits.push(milliseconds), _getch: async () => keys.shift() });
    sandbox.AsciiFuncion = () => {};
    const option = { v: 0 };
    try {
      await sandbox.InterfazPausa([], option, { v: 1 });
      assert.equal(option.v, expected);
      assert.deepEqual(exits, [expected]);
      assert.equal(keys.length, 0, 'No synthetic navigation commands');
      assert.equal(waits.at(-1), 200, 'Original pause exit delay remains');
    } finally { stop(); parent(); }
  }
});


test('original push, pause and successful undo drive mobile hints from canonical board/history', async () => {
  const { mountUndoHint } = await import('../src/presentation/undoHint.js');
  const { createSeenProgress } = await import('../src/state/seenProgress.js');
  const { mountRewindDiscovery } = await import('../src/presentation/rewindDiscovery.js');
  const progress = createSeenProgress({ storage: null });
  const discovery = mountRewindDiscovery(GameState, { progress });
  const hint = mountUndoHint(GameState);
  const samples = [];
  const stop = GameState.on('input:waiting', ({ request }) => {
    if (request?.consumer !== 'ControlDeMovimiento') return;
    const state = GameState.getSnapshot();
    samples.push({ hint: state.undoHint, game: state.game });
  });
  const arrays = board();
  arrays.Paredes[1] = [[42, 34], [40, 32]];
  arrays.Vacios[1] = [];
  arrays.Huecos[1] = [[60, 50]];
  arrays.Cantidades[1] = [1, 2, 0, 1];
  try {
    await runtime(['d', 'p', 'r', 'c', 'c', 'c'], arrays);
    assert.equal(samples[0].hint, false);
    assert.ok(samples.some(sample => sample.hint && sample.game.board.boxes[0].x === 40 && sample.game.undoDepth === 1));
    assert.ok(samples.some(sample => !sample.hint && sample.game.board.boxes[0].x === 38 && sample.game.steps === 6 && sample.game.undoDepth === 0));
    assert.equal(GameState.getSnapshot().undoHint, false);
    assert.equal(GameState.getSnapshot().game, null);
    assert.equal(progress.has('rewind:recovered'), true, 'Original Regresar earns the saved recovery milestone');
    assert.equal(GameState.getSnapshot().rewindDiscovery.visible, true);
  } finally { stop(); hint.dispose(); discovery.dispose(); }
});

test('level-one hints catch the earlier movable trap and persist until both cajas recover', async () => {
  const { mountUndoHint, boxHasLegalPush } = await import('../src/presentation/undoHint.js');
  const data = vm.createContext({}); vm.runInContext(executable(read('world_data')), data);
  const slots = () => Array.from({ length: 8 }, () => Array.from({ length: 200 }, () => []));
  const arrays = { Cajas: slots(), Paredes: slots(), Vacios: slots(), Huecos: slots(), Cantidades: slots() };
  data.DataCantidades(arrays.Cantidades); data.DataICajas(1, arrays.Cajas); data.DataParedes(1, arrays.Paredes); data.DataVacios(1, arrays.Vacios); data.DataHuecos(1, arrays.Huecos);
  const hint = mountUndoHint(GameState), samples = [];
  const stop = GameState.on('input:waiting', ({ request }) => {
    if (request?.consumer === 'ControlDeMovimiento') samples.push({ hint: GameState.getSnapshot().undoHint, game: GameState.getSnapshot().game });
  });
  try {
    await runtime(['a', ...Array(5).fill('w'), 'd', ...Array(5).fill('w'), 'a', 'a', 'r', 'r', 'r', 'c', 'c', 'c'], arrays);
    const trapped = samples.find(sample => sample.game.steps === 14);
    assert.equal(trapped.hint, true);
    assert.ok(trapped.game.board.boxes.some(box => box.x === 30 && box.y === 14));
    const earlier = samples.find(sample => sample.game.steps === 12);
    assert.equal(earlier.hint, true, 'Earlier caja at (36,12) is movable but lost');
    assert.equal(boxHasLegalPush(earlier.game, earlier.game.board.boxes[2]), true);
    assert.equal(samples.find(sample => sample.game.steps === 19).hint, true, 'One undo recovers only the later corner trap');
    const recovered = samples.find(sample => sample.game.steps === 44);
    assert.equal(recovered.hint, false);
  } finally { stop(); hint.dispose(); }
});


test('original pushes hint for a movable wall-strip caja and undo recovers it', async () => {
  const { mountUndoHint, boxHasLegalPush } = await import('../src/presentation/undoHint.js');
  const arrays = board();
  arrays.Paredes[1] = Array.from({ length: 40 }, (_, index) => [index * 2, 30]);
  arrays.Huecos[1] = [[40, 36]]; arrays.Vacios[1] = [];
  arrays.Cantidades[1] = [1, 40, 0, 1];
  const hint = mountUndoHint(GameState), samples = [];
  const stop = GameState.on('input:waiting', ({ request }) => {
    if (request?.consumer === 'ControlDeMovimiento') samples.push({ hint: GameState.getSnapshot().undoHint, game: GameState.getSnapshot().game });
  });
  try {
    await runtime(['w', 'r', 'c', 'c', 'c'], arrays, { x: 38, y: 36 });
    const lost = samples.find(sample => sample.game.steps === 1);
    assert.equal(boxHasLegalPush(lost.game, lost.game.board.boxes[0]), true);
    assert.equal(lost.hint, true);
    const recovered = samples.find(sample => sample.game.steps === 6);
    assert.equal(recovered.hint, false);
  } finally { stop(); hint.dispose(); }
});

test('original bridge creation/removal drives sacrifice hints and exempts the intended level-three routes', async () => {
  const { mountUndoHint } = await import('../src/presentation/undoHint.js');
  for (const [level, caja, gap, player, move, expected] of [
    [2, [38, 34], [40, 34], [36, 34], 'd', true],
    [3, [42, 32], [42, 34], [42, 30], 's', false],
    [3, [38, 38], [36, 38], [40, 38], 'a', false],
    [3, [34, 28], [34, 26], [34, 30], 'w', true],
  ]) {
    const hint = mountUndoHint(GameState), samples = [];
    const stop = GameState.on('input:waiting', ({ request }) => {
      if (request?.consumer === 'ControlDeMovimiento') samples.push({ hinted: GameState.getSnapshot().undoHint, game: GameState.getSnapshot().game });
    });
    const rows = () => Array.from({ length: 8 }, () => []);
    const arrays = { Cajas: rows(), Paredes: rows(), Vacios: rows(), Huecos: rows(), Cantidades: rows() };
    arrays.Cajas[level] = [caja, [30, 30]];
    arrays.Vacios[level] = [gap]; arrays.Huecos[level] = [[20, 20]]; arrays.Cantidades[level] = [2, 0, 1, 1];
    try {
      await runtime([move, 'r', 'c', 'c', 'c'], arrays, { startLevel: level, x: player[0], y: player[1] });
      const created = samples.find(sample => sample.game.steps === 1);
      assert.equal(created.game.board.boxes.length, 1);
      assert.equal(created.game.board.gaps.length, 0);
      assert.equal(created.hinted, expected);
      const recovered = samples.find(sample => sample.game.steps === 6);
      assert.equal(recovered.game.board.boxes.length, 2);
      assert.equal(recovered.game.board.gaps.length, 1);
      assert.equal(recovered.hinted, false);
    } finally { stop(); hint.dispose(); }
  }
});

function levelFiveBoard() {
  const data = vm.createContext({}); vm.runInContext(executable(read('world_data')), data);
  const slots = () => Array.from({ length: 8 }, () => Array.from({ length: 200 }, () => []));
  const arrays = { Cajas: slots(), Paredes: slots(), Vacios: slots(), Huecos: slots(), Cantidades: slots() };
  data.DataCantidades(arrays.Cantidades); data.DataICajas(5, arrays.Cajas); data.DataHuecos(5, arrays.Huecos);
  // Isolate the sound rule from routing: retain original identities, origins,
  // counts and huecos, with an unobstructed approach to the pushed object.
  arrays.Cantidades[5][1] = 0;
  return arrays;
}

test('canonical level-five sound distinguishes real huecos from any DP position', async () => {
  for (const scenario of [
    { index: 0, before: [34, 16], player: [34, 18], bell: true },
    { index: 10, before: [34, 16], player: [34, 18], bell: false },
    ...Array.from({ length: 7 }, (_, offset) => {
      const index = 10 + offset, origin = levelFiveBoard().Cajas[5][index];
      return { index, before: [origin[0], origin[1] + 2], player: [origin[0], origin[1] + 4], bell: true };
    }),
    { index: 10, before: [34, 28], player: [34, 30], bell: true, otherOrigin: true },
  ]) {
    const arrays = levelFiveBoard(); arrays.Cajas[5][scenario.index] = [...scenario.before];
    if (scenario.otherOrigin) arrays.Cajas[5][11] = [70, 50];
    const result = await runtime(['w', 'c', 'c', 'c'], arrays,
      { startLevel: 5, x: scenario.player[0], y: scenario.player[1] });
    assert.equal(result.sounds.includes('bell'), scenario.bell, `Object ${scenario.index} from ${scenario.before}`);
    assert.equal(result.sounds.includes('hardening'), false);
    assert.ok(result.snapshots.some(({ game }) => game.steps === 1 && game.board.boxes[scenario.index].y === scenario.before[1] - 2));
  }
});

test('final DP return rings before endurecimiento takes priority; DPs cannot replace real cajas for completion', async () => {
  const arrays = levelFiveBoard();
  for (let index = 0; index < 10; index++) arrays.Cajas[5][index] = [...arrays.Huecos[5][index]];
  // DP 10 completes DP 11's position; DP 11 already occupies DP 10's.
  arrays.Cajas[5][11] = [32, 24];
  arrays.Cajas[5][10] = [34, 28];
  const result = await runtime(['w', 'c', 'c', 'c'], arrays, { startLevel: 5, x: 34, y: 30 });
  assert.deepEqual(result.sounds.slice(0, 2), ['bell', 'hardening']);
  assert.ok(result.snapshots.some(({ game }) => game.portal.active));

  const rules = vm.createContext({}); vm.runInContext(executable(read('world_logic')), rules);
  assert.equal(rules.PortalVisible(5, arrays.Cajas, arrays.Huecos, arrays.Cantidades), true);
  arrays.Cajas[5][0] = [70, 50]; arrays.Cajas[5][10] = [...arrays.Huecos[5][0]];
  assert.equal(rules.CajayHueco(5, 10, arrays.Cajas, arrays.Huecos, arrays.Cantidades), true);
  assert.equal(rules.PortalVisible(5, arrays.Cajas, arrays.Huecos, arrays.Cantidades), false);
});

test('level-five completion accepts interchangeable DP but still requires all seven positions and ten real cajas', () => {
  const rules = vm.createContext({}); vm.runInContext(executable(read('world_logic')), rules);
  const origins = levelFiveBoard().Cajas[5].slice(10, 17).map(position => [...position]);
  for (let shift = 0; shift < 7; shift++) {
    const arrays = levelFiveBoard();
    for (let index = 0; index < 10; index++) arrays.Cajas[5][index] = [...arrays.Huecos[5][index]];
    for (let index = 0; index < 7; index++) arrays.Cajas[5][10 + index] = [...origins[(index + shift) % 7]];
    assert.equal(rules.PortalVisible(5, arrays.Cajas, arrays.Huecos, arrays.Cantidades), true);
    arrays.Cajas[5][10] = [70, 50];
    assert.equal(rules.PortalVisible(5, arrays.Cajas, arrays.Huecos, arrays.Cantidades), false, 'An unfilled DP position prevents completion');
    arrays.Cajas[5][0] = [...origins[shift]];
    assert.equal(rules.PortalVisible(5, arrays.Cajas, arrays.Huecos, arrays.Cantidades), false, 'Real cajas cannot substitute for DP');
  }
});

function undoBoard() {
  return { Cajas: [null, [[20, 20]]], Paredes: [null, []], Vacios: [null, []],
    Huecos: [null, [[22, 20]]], Cantidades: [null, [1, 0, 0, 1]] };
}
const walks = count => Array.from({ length: count }, (_, index) => index % 2 ? 'd' : 'a');

test('canonical undo prices grow on successes only, survive pause, and reset on a fresh attempt', async () => {
  const result = await runtime(['r', 'a', 'd', 'a', 'r', 'p', 'r', 'r', 'r', 'c', 'c', 'c'], undoBoard());
  for (const [steps, nextCost, depth] of [[0, 5, 0], [3, 5, 3], [8, 10, 2], [18, 15, 1], [33, 20, 0]]) {
    assert.ok(result.snapshots.some(({ game }) => game.steps === steps && game.nextUndoCost === nextCost && game.undoDepth === depth));
  }
  assert.equal(result.sounds.filter(sound => sound === 'undo:2').length, 2, 'Unavailable attempts do not consume steps or raise price');
  assert.ok(result.snapshots.some(state => state.screen?.id === 'InterfazPausa' && state.game.nextUndoCost === 10));
  const retry = await runtime(['a', 'r', 'p'], undoBoard(), { pauseOption: 2 });
  assert.equal(retry.lives.v, 4);
  assert.ok(retry.snapshots.some(({ game }) => game.nextUndoCost === 10));
  const death = await runtime(['a', 'r', ...walks(144)], undoBoard());
  assert.equal(death.lives.v, 4);
  assert.ok(death.snapshots.some(({ game }) => game.nextUndoCost === 10));
  const fresh = await runtime(['c', 'c', 'c'], undoBoard());
  assert.ok(fresh.snapshots.some(({ game }) => game.steps === 0 && game.nextUndoCost === 5));
});

test('capped undo leaves one step, then blocks despite retained history without changing cost', async () => {
  const result = await runtime([...walks(143), 'r', 'r', 'r', 'c', 'c', 'c'], undoBoard());
  const twoLeft = result.snapshots.find(({ game }) => game.steps === 148).game;
  assert.equal(twoLeft.remainingMoves, 2); assert.equal(twoLeft.nextUndoCost, 10);
  assert.equal(twoLeft.undoCharge, 1); assert.equal(twoLeft.undoAffordableDepth, 1);
  const last = result.snapshots.findLast(({ game }) => game.steps === 149).game;
  assert.equal(last.remainingMoves, 1); assert.equal(last.nextUndoCost, 15);
  assert.equal(last.undoDepth, 3); assert.equal(last.undoAvailable, false);
  assert.equal(last.undoCharge, 0); assert.equal(last.undoAffordableDepth, 0);
  assert.equal(result.sounds.filter(sound => sound === 'undo:2').length, 1);
  assert.equal(result.lives.v, 5, 'Undo cannot spend the last step');
});

test('only five stored moves can rewind, charging 5 through 25 consecutively', async () => {
  const result = await runtime([...walks(7), 'r', 'r', 'r', 'r', 'r', 'r', 'c', 'c', 'c'], undoBoard());
  for (const [steps, cost, depth] of [[7, 5, 5], [12, 10, 4], [22, 15, 3], [37, 20, 2], [57, 25, 1], [82, 30, 0]]) {
    assert.ok(result.snapshots.some(({ game }) => game.steps === steps && game.nextUndoCost === cost && game.undoDepth === depth));
  }
  assert.equal(result.snapshots.findLast(({ game }) => game.steps === 82).game.undoAvailable, false);
  assert.equal(result.sounds.filter(sound => sound === 'undo:2').length, 1);
});

test('successful walking or pushing resets the consecutive rewind price to five', async () => {
  const walking = await runtime(['a', 'd', 'a', 'r', 'r', 'a', 'r', 'c', 'c', 'c'], undoBoard());
  assert.ok(walking.snapshots.some(({ game }) => game.steps === 19 && game.nextUndoCost === 5));
  assert.ok(walking.snapshots.some(({ game }) => game.steps === 24 && game.nextUndoCost === 10));
  const board = undoBoard(); board.Cajas[1][0] = [34, 34];
  const pushing = await runtime(['d', 'd', 'r', 'r', 'a', 'r', 'c', 'c', 'c'], board);
  assert.ok(pushing.snapshots.some(({ game }) => game.steps === 18 && game.nextUndoCost === 5 && game.board.boxes[0].x === 32));
  assert.ok(pushing.snapshots.some(({ game }) => game.steps === 23 && game.nextUndoCost === 10 && game.board.boxes[0].x === 34));
});

test('rejected movement does not reset the consecutive rewind price', async () => {
  const board = undoBoard(); board.Paredes[1] = [[36, 32]]; board.Cantidades[1][1] = 1;
  const result = await runtime(['a', 'd', 'a', 'r', 'w', 'r', 'c', 'c', 'c'], board);
  assert.ok(result.snapshots.some(({ game }) => game.steps === 18 && game.nextUndoCost === 15));
  assert.ok(result.events.some(event => event.type === 'movementBlocked'));
});

test('warning fires once when walking or undo crosses below twenty, never on pause redraw', async () => {
  const walking = await runtime([...walks(131), 'p', 'c', 'c', 'c'], undoBoard());
  assert.deepEqual(walking.huds.filter(args => args[4]).map(args => args[2]), [131]);
  assert.ok(walking.huds.some(args => args[2] === 130 && !args[4]), 'Exactly twenty is not below twenty');
  const undo = await runtime([...walks(126), 'r', 'p', 'r', 'c', 'c', 'c'], undoBoard());
  assert.deepEqual(undo.huds.filter(args => args[4]).map(args => args[2]), [131]);
});
