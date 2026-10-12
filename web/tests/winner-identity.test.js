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
