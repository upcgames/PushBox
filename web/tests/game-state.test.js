import test from 'node:test';
import assert from 'node:assert/strict';
import { createGameState, GameState } from '../src/state/gameState.js';
import { observeGame, refreshGame, enterScreen, boardSnapshot, recordInput, enterInput, withInput } from '../src/state/runtimeBridge.js';
import { selectControlMode } from '../src/shell/controlPolicy.js';
import { observeConsole } from '../src/state/consoleTranscript.js';

test('snapshots are detached and immutable; subscriptions replay and unsubscribe', () => {
  const { api, publish } = createGameState();
  const received = [];
  const stop = api.subscribe(state => received.push(state));
  const game = { board: { boxes: [{ x: 4, y: 6 }] } };
  publish({ game });
  game.board.boxes[0].x = 99;
  assert.equal(api.getSnapshot().game.board.boxes[0].x, 4);
  assert.throws(() => { api.getSnapshot().game.board.boxes[0].x = 7; }, TypeError);
  stop(); publish({ game: null });
  assert.equal(received.length, 2);
});

test('presentation selectors derive controls from retained input requests', () => {
  const { api, publish } = createGameState(), modes = [], events = [];
  api.on('*', event => events.push(event));
  const stop = api.select(selectControlMode, mode => modes.push(mode));
  publish({ inputRequest: { kind: 'key', consumer: 'ControlDeMovimiento' } });
  publish({ inputRequest: { kind: 'key', consumer: 'ControlDeMovimiento' } });
  publish({ inputRequest: { kind: 'key', consumer: 'InterfazPausa' } });
  stop(); publish({ inputRequest: null });
  assert.deepEqual(modes, ['none', 'dpad', 'paused']);
  assert.ok(events.every((event, index) => event.sequence === index + 1));
  assert.equal(api.emit, undefined);
});

test('consumer failures do not interrupt the runtime or other subscribers', () => {
  const { api, publish, event } = createGameState();
  const warn = console.warn;
  let called = 0;
  try {
    console.warn = () => {};
    api.subscribe(() => { throw new Error('consumer'); });
    api.subscribe(() => called++);
    api.on('custom', () => { throw new Error('consumer'); });
    api.on('custom', () => called++);
    publish({ game: null }); event('custom', {});
    assert.equal(called, 3);
  } finally { console.warn = warn; }
});

test('reentrant publications keep each delivered snapshot coherent', () => {
  const { api, publish } = createGameState(), versions = [];
  api.subscribe(state => {
    if (state.version === 1) publish({ inputRequest: { consumer: 'pause' } });
  });
  api.subscribe(state => versions.push([state.version, state.inputRequest?.consumer || null]));
  publish({ inputRequest: { consumer: 'game' } });
  assert.deepEqual(versions, [[0, null], [1, 'game'], [2, 'pause']]);
});

test('board snapshots respect active counts and distinguish covered targets from gaps', () => {
  const arrays = { Cajas: [null, [[2, 4], [8, 8], [99, 99]]], Paredes: [null, [[0, 0]]],
    Huecos: [null, [[2, 4], [6, 4]]], Vacios: [null, [[10, 4]]], Cantidades: [null, [2, 1, 1, 2]] };
  const snapshot = boardSnapshot(1, { x: 4, y: 4 }, 7, 5, 1, arrays, { active: false }, 1, 2);
  assert.equal(snapshot.board.boxes.length, 2);
  assert.equal(snapshot.board.boxes[0].onTarget, true);
  assert.deepEqual(snapshot.board.targets.map(target => target.covered), [true, false]);
  assert.deepEqual(snapshot.board.gaps, [{ x: 10, y: 4 }]);
  assert.equal(snapshot.undoAvailable, true);
});

test('runtime refresh deduplicates, retains paused state, and clears on exit', () => {
  let steps = 0;
  const stop = observeGame(() => ({ steps, lives: 5 }));
  const version = GameState.getSnapshot().version;
  refreshGame(); assert.equal(GameState.getSnapshot().version, version);
  steps++; refreshGame(); assert.equal(GameState.getSnapshot().game.steps, 1);
  const leave = enterScreen('InterfazPausa');
  assert.equal(GameState.getSnapshot().game.steps, 1);
  assert.equal(GameState.getSnapshot().screen.id, 'InterfazPausa');
  leave(); stop();
  assert.equal(GameState.getSnapshot().game, null);
  assert.equal(GameState.getSnapshot().screen, null);
});

test('nested screens restore their parent and input events include the request', () => {
  const parent = enterScreen('menu'), child = enterScreen('instructions');
  child(); assert.equal(GameState.getSnapshot().screen.id, 'menu');
  const events = [], off = GameState.on('input:consumed', event => events.push(event));
  const request = { kind: 'confirmation', key: 'E' };
  const leaveInput = enterInput(request); recordInput('e', 'consumed');
  assert.deepEqual(events, [{ key: 'e', stage: 'consumed', request }]);
  off(); leaveInput(); parent();
});

test('console transcript batches writes, preserves coordinates/colors, overwrites and clears', () => {
  const frames = [], consoleInstance = { cols: 6, rows: 2, tileSize: 14 };
  const stop = observeConsole(consoleInstance, callback => frames.push(callback));
  const observer = consoleInstance.observer;
  observer.write(1, 0, 'H', '#fff', '#000'); observer.write(2, 0, 'i', '#fff', '#000');
  observer.write(99, 0, '!', '#fff', '#000');
  assert.equal(frames.length, 1); frames.shift()();
  const first = GameState.getSnapshot().console;
  assert.equal(first.lines[0], ' Hi');
  assert.equal(first.cells[0][1].foreground, '#fff');
  observer.write(1, 0, 'B', '#fff', '#000'); frames.shift()();
  assert.equal(first.lines[0], ' Hi');
  assert.equal(GameState.getSnapshot().console.lines[0], ' Bi');
  observer.clear(4, 1, 12); frames.shift()();
  assert.deepEqual(GameState.getSnapshot().console.lines, ['']);
  stop(); assert.equal(consoleInstance.observer, null);
});

test('requests clear on completion and exceptions; child screens suspend parent controls', async () => {
  const leaveGame = enterScreen('gameplay');
  const leaveKeys = enterInput({ kind: 'key', consumer: 'ControlDeMovimiento' });
  assert.equal(selectControlMode(GameState.getSnapshot()), 'dpad');
  const leavePause = enterScreen('InterfazPausa');
  assert.equal(selectControlMode(GameState.getSnapshot()), 'none');
  await withInput({ kind: 'confirmation', key: 'E' }, async () => {
    assert.equal(selectControlMode(GameState.getSnapshot()), 'continue');
  });
  assert.equal(selectControlMode(GameState.getSnapshot()), 'none');
  await assert.rejects(withInput({ kind: 'text', maxLength: 8 }, () => { throw new Error('input failed'); }));
  assert.equal(GameState.getSnapshot().inputRequest, null);
  leavePause(); assert.equal(selectControlMode(GameState.getSnapshot()), 'dpad');
  leaveKeys(); assert.equal(selectControlMode(GameState.getSnapshot()), 'none');
  leaveGame();
});

test('control policy covers existing layouts without adding UI modes to the store', () => {
  const mode = request => selectControlMode({ inputRequest: request });
  assert.equal(mode(null), 'none');
  assert.equal(mode({ kind: 'confirmation' }), 'continue');
  assert.equal(mode({ kind: 'key', consumer: 'ControlDeMovimiento' }), 'dpad');
  assert.equal(mode({ kind: 'key', consumer: 'MenuPrincipal' }), 'paused');
  assert.equal(mode({ kind: 'key', consumer: 'InterfazCongratulations' }), 'congrats');
  assert.equal(mode({ kind: 'text', maxLength: 1, choices: ['1', '2'] }), '1v2');
  assert.equal(mode({ kind: 'text', maxLength: 1, choices: null }), 'qwerty');
  assert.equal(mode({ kind: 'key', consumer: 'unknown' }), 'none');
});
