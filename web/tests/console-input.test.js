import test from 'node:test';
import assert from 'node:assert/strict';
import { GameState, sendInput } from '../src/state/gameState.js';
import { enterInput } from '../src/state/runtimeBridge.js';
import { observeConsole } from '../src/state/consoleTranscript.js';

test('real console mirrors visible cells and shared input reaches the canonical queue', async () => {
  const frames = [], ctx = { fillRect() {}, clearRect() {}, save() {}, beginPath() {},
    rect() {}, clip() {}, fillText() {}, restore() {} };
  const windowBefore = globalThis.window, documentBefore = globalThis.document;
  globalThis.window = new EventTarget();
  window.KeyboardEvent = class extends Event {
    constructor(type, options) { super(type, options); this.key = options.key; }
  };
  globalThis.document = { getElementById: () => ({ getContext: () => ctx }) };
  const events = [], off = GameState.on('*', event => events.push(event));
  let stop, leaveInput;
  try {
    const { VirtualConsole } = await import('../src/shims/virtual_console.js');
    const main = new VirtualConsole('gameCanvas', 8, 2, 14);
    stop = observeConsole(main, callback => frames.push(callback));
    main.SetCursorPosition(2, 0); main.Write('Hey');
    main.SetCursorPosition(2, 0); main.Write('B');
    frames.shift()();
    assert.equal(GameState.getSnapshot().console.lines[0], '  Bey');
    const other = new VirtualConsole('galleryCanvas', 8, 2, 14);
    other.Write('Unrelated');
    assert.equal(frames.length, 0);
    main.SetWindowSize(4, 3); frames.shift()();
    assert.equal(GameState.getSnapshot().console.rows, 3);
    assert.deepEqual(GameState.getSnapshot().console.lines, ['', '', '']);
    leaveInput = enterInput({ kind: 'key', consumer: 'ControlDeMovimiento' });
    sendInput('d');
    assert.equal(await window._getch(), 'd');
    const waiting = window._getch();
    assert.equal(GameState.getSnapshot().input.stage, 'waiting');
    sendInput('Enter');
    assert.equal(await waiting, 13);
    GameState.setWinnerContinueBlocked(true);
    sendInput('e'); sendInput('Enter');
    assert.equal(window._kbhit(), 0, 'Production input discards blocked confirmations');
    GameState.setWinnerContinueBlocked(false);
    sendInput('e'); assert.equal(await window._getch(), 'e');
    assert.ok(events.some(event => event.type === 'input:received' && event.payload.key === 'd'));
    assert.ok(events.some(event => event.type === 'input:consumed' && event.payload.key === 13));
    assert.throws(() => sendInput(''), TypeError);
  } finally {
    GameState.setWinnerContinueBlocked(false);
    stop?.(); leaveInput?.(); off();
    if (windowBefore === undefined) delete globalThis.window; else globalThis.window = windowBefore;
    if (documentBefore === undefined) delete globalThis.document; else globalThis.document = documentBefore;
  }
});
