import test from 'node:test';
import assert from 'node:assert/strict';
import { createWinnerIdentity } from '../src/presentation/winnerIdentity.js';
import { createPlayerProfile } from '../src/presentation/playerIdentity.js';
import { createGameState } from '../src/state/gameState.js';
import { createRuntimeBridge } from '../src/state/runtimeBridge.js';
import { selectControlMode } from '../src/shell/controlPolicy.js';

function fixture(enabled = () => true) {
  const store = createGameState(() => { throw new Error('Native handoff must not send keys'); });
  const profile = createPlayerProfile({ storage: null });
  const flow = createWinnerIdentity({ profile, store: store.api, enabled });
  store.api.registerNativeTextReader(flow.read, flow.accepts);
  const bridge = createRuntimeBridge(store);
  bridge.enterScreen('InterfazCongratulations');
  return { flow, profile, store, bridge };
}
const request = (maxLength, choices = null) => ({ kind: 'text', consumer: 'InterfazCongratulations', maxLength, choices });

test('native handoff feeds original choice and signed CP850 names without keyboard input', async () => {
  const { flow, profile, store, bridge } = fixture();
  const choice = [], first = [], second = [];
  const read = () => { throw new Error('Native reads must bypass canonical scanf'); };
  flow.begin();
  const pending = bridge.withInput(request(1, ['1', '2']), read, choice);
  assert.equal(selectControlMode(store.api.getSnapshot()), 'none');
  assert.equal(flow.submit('💥 !'), false);
  assert.equal(flow.submit(' Josélonglong  Ñina!  ignored'), true);
  await pending;
  await bridge.withInput(request(8), read, first);
  await bridge.withInput(request(8), read, second);
  assert.deepEqual(choice, ['2', '\0']);
  assert.deepEqual(first, ['J', 'o', 's', -126, 'l', 'o', 'n', 'g', '\0']);
  assert.deepEqual(second, [-91, 'i', 'n', 'a', '\0']);
  assert.deepEqual(profile.getNames(), ['Josélong', 'Ñina']);
  assert.deepEqual(store.api.getSnapshot().playerNames, profile.getNames());
  flow.begin();
  assert.equal(flow.getSnapshot().name, 'Josélong Ñina');
  flow.submit('Ana');
  await bridge.withInput(request(1, ['1', '2']), read, choice);
  await bridge.withInput(request(8), read, first);
  assert.equal(choice[0], '1');
  assert.deepEqual(first.slice(0, 4), ['A', 'n', 'a', '\0']);
  flow.dispose();
});

test('desktop reads stay canonical and disposal cancels native reads', async () => {
  const desktop = fixture(() => false);
  let reads = 0;
  await desktop.bridge.withInput(request(1, ['1', '2']), async () => { reads++; }, []);
  assert.equal(reads, 1);
  assert.equal(desktop.flow.getSnapshot().visible, false);
  const mobile = fixture();
  const pending = mobile.bridge.withInput(request(1, ['1', '2']), () => {}, []);
  mobile.flow.dispose();
  await assert.rejects(pending, { name: 'AbortError' });
  assert.equal(mobile.store.api.getSnapshot().inputRequest, null);
  assert.deepEqual(desktop.profile.getNames(), []);
});

test('original name retries reopen the rejected field without consuming the other name', async () => {
  const { flow, profile, bridge } = fixture();
  const choice = [], first = [], second = [];
  const read = () => assert.fail('Native retry must not queue console input');
  flow.begin();
  assert.equal(flow.submit('32132asda fafds'), true);
  await bridge.withInput(request(1, ['1', '2']), read, choice);
  await bridge.withInput(request(8), read, first);
  assert.deepEqual(first, [...'32132asd', '\0']);
  const retry = bridge.withInput(request(8), read, first);
  assert.equal(flow.getSnapshot().visible, true);
  assert.equal(flow.getSnapshot().name, '');
  assert.equal(flow.getSnapshot().rejected, true);
  assert.equal(flow.submit('$$$$$$$$$'), false);
  assert.equal(flow.getSnapshot().visible, true);
  flow.submit('Ana');
  await retry;
  assert.deepEqual(first, [...'Ana', '\0'], 'A shorter retry clears the previous target contents');
  await bridge.withInput(request(8), read, second);
  assert.deepEqual(second, [...'fafds', '\0']);
  const retrySecond = bridge.withInput(request(8), read, second);
  flow.submit('José');
  await retrySecond;
  assert.deepEqual(second, ['J', 'o', 's', -126, '\0']);
  assert.deepEqual(profile.getNames(), ['Ana', 'José']);
  assert.equal(choice[0], '2', 'Retry preserves the original name count');
  flow.dispose();
});


test('prompt presentation bypasses typewriter only for an enabled native reader', async () => {
  const mobile = fixture();
  const calls = [];
  const type = async () => calls.push('original timing and sound');
  const write = () => calls.push('immediate console write');
  await mobile.bridge.presentPrompt('InterfazCongratulations', type, write);
  assert.deepEqual(calls, ['immediate console write']);
  await mobile.bridge.presentPrompt('main', type, write);
  assert.equal(calls.at(-1), 'original timing and sound');
  const desktop = fixture(() => false);
  await desktop.bridge.presentPrompt('InterfazCongratulations', type, write);
  assert.equal(calls.at(-1), 'original timing and sound');
  mobile.flow.dispose();
  await mobile.bridge.presentPrompt('InterfazCongratulations', type, write);
  assert.equal(calls.at(-1), 'original timing and sound');
});

test('scene presentation replacement is consumer-specific, session-local, and unregisters safely', async () => {
  const mobile = fixture(), desktop = fixture();
  const calls = [];
  let enabled = true;
  const stopOld = mobile.store.api.registerPresentationOverride('InterfazInstructions', () => enabled);
  const stop = mobile.store.api.registerPresentationOverride('InterfazInstructions', () => enabled);
  stopOld();
  const original = () => calls.push('original'), immediate = () => calls.push('immediate');
  await mobile.bridge.presentScene('InterfazInstructions', original, immediate);
  await mobile.bridge.presentScene('InterfazCongratulations', original, immediate);
  await desktop.bridge.presentScene('InterfazInstructions', original, immediate);
  assert.deepEqual(calls, ['immediate', 'original', 'original']);
  enabled = false;
  await mobile.bridge.presentScene('InterfazInstructions', original, immediate);
  assert.equal(calls.at(-1), 'original');
  enabled = true;
  stop();
  await mobile.bridge.presentScene('InterfazInstructions', original, immediate);
  assert.equal(calls.at(-1), 'original');
  mobile.flow.dispose(); desktop.flow.dispose();
});

test('immediate presentation drawing completes original writes and closes generators on failure', async () => {
  const { bridge, flow } = fixture();
  const writes = [];
  let closed = false;
  async function* drawing(fail = false) {
    try {
      writes.push('first'); yield 500;
      if (fail) throw new Error('drawing failed');
      writes.push('second'); yield 20;
    } finally { closed = true; }
  }
  await bridge.drawImmediately(drawing);
  assert.deepEqual(writes, ['first', 'second']);
  assert.equal(closed, true);
  closed = false;
  await assert.rejects(bridge.drawImmediately(drawing, true), /drawing failed/);
  assert.equal(closed, true);
  flow.dispose();
});
