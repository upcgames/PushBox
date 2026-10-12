import test from 'node:test';
import assert from 'node:assert/strict';
import { createGameState } from '../src/state/gameState.js';
import { createSeenProgress } from '../src/state/seenProgress.js';
import { createPlayerProfile } from '../src/presentation/playerIdentity.js';
import { createOpeningFlow } from '../src/presentation/openingFlow.js';
import { availableDestinations, destinationSettings, mountSeenDestinations } from '../src/presentation/seenDestinations.js';
import { runMobileRuntime } from '../src/runtime/runMobileRuntime.js';

const gameplay = level => ({ screen: { id: 'gameplay' }, game: { level }, inputRequest: { kind: 'key', consumer: 'ControlDeMovimiento' } });
function fixture(progress = createSeenProgress({ storage: null })) {
  const calls = [];
  const flow = createOpeningFlow({ progress, profile: createPlayerProfile({ storage: null }), audio: { play() {}, stop() {} }, onEnter: destination => calls.push(destination) });
  return { flow, calls, progress };
}

test('actual level-one input unlocks destinations; lore and other previews do not', () => {
  const store = createGameState(), progress = createSeenProgress({ storage: null });
  const other = createSeenProgress({ storage: null });
  let enabled = true;
  const stop = mountSeenDestinations(store.api, progress, () => enabled);
  store.publish({ screen: { id: 'MenuPrincipal' } });
  store.publish({ screen: { id: 'Lore', level: 1 }, game: { level: 1 } });
  assert.deepEqual(availableDestinations(progress), []);
  store.publish({ ...gameplay(1), inputRequest: null });
  assert.equal(progress.has('level:1'), false);
  enabled = false; store.publish(gameplay(1));
  assert.equal(progress.has('level:1'), false);
  enabled = true; store.publish(gameplay(1));
  assert.deepEqual(availableDestinations(progress).map(item => item.id), ['menu', 'level-1']);
  assert.equal(other.has('level:1'), false);
  store.publish(gameplay(3));
  assert.equal(progress.has('level:2'), false);
  assert.equal(progress.has('level:3'), true);
  stop();
});

test('visits persist and cleared progress immediately removes launch eligibility', () => {
  const data = new Map(), storage = { getItem: key => data.get(key), setItem: (key, value) => data.set(key, value) };
  const progress = createSeenProgress({ storage });
  progress.mark('level:1'); progress.mark('scene:InterfazInstructions');
  const reloaded = createSeenProgress({ storage });
  const { flow } = fixture(reloaded);
  flow.setLoading(100, true); flow.openDestinations();
  assert.equal(flow.getSnapshot().destinationOpen, true);
  reloaded.clear('level:1');
  assert.equal(flow.getSnapshot().destinationOpen, false);
  assert.equal(flow.chooseDestination('instructions'), false);
  assert.equal(destinationSettings(reloaded, 'instructions', false), null);
  flow.dispose();
});

test('selector waits for assets and launches only seen destinations, preserving skip-lore', () => {
  const { flow, calls, progress } = fixture();
  progress.mark('level:1'); progress.mark('level:4');
  flow.setLoading(40); flow.openDestinations();
  assert.equal(flow.getSnapshot().destinationOpen, false);
  flow.setLoading(100, true); flow.openDestinations();
  assert.equal(flow.chooseDestination('level-5'), false);
  flow.continue(); assert.deepEqual(calls, [], 'Enter behind the modal must not launch');
  assert.equal(flow.chooseDestination('level-4'), true);
  flow.hideLoading();
  assert.deepEqual(flow.takeDestination(true), { entry: 'main', skipIntro: true, startLevel: 4, skipLore: true });
  assert.equal(flow.takeDestination(false), null, 'selection is consumed once');
  assert.deepEqual(calls, ['level-4']);
  flow.dispose();
});

test('selected named entry composes original instructions and leaves normal Enter unchanged', async () => {
  const { flow, progress } = fixture();
  progress.mark('level:1'); progress.mark('scene:InterfazInstructions');
  flow.setLoading(100, true); flow.openDestinations(); flow.chooseDestination('instructions');
  const calls = [], names = [], config = { entry: 'main', skipIntro: false, startLevel: 0, skipLore: false };
  const opening = { enabled: () => true, getNames: () => ['Ana'], takeDestination: flow.takeDestination,
    begin: async () => { calls.push('warning after main'); throw new DOMException('reset', 'AbortError'); } };
  await assert.rejects(runMobileRuntime({ InterfazInstructions: async () => calls.push('instructions'), desvanecimiento() {}, main: async () => calls.push('main') }, {
    settings: config, opening, configure: patch => Object.assign(config, patch), runAnim: async () => calls.push('fade'), setPlayerNames: value => names.push(value),
  }), { name: 'AbortError' });
  assert.deepEqual(calls, ['instructions', 'fade', 'main', 'warning after main']);
  assert.deepEqual(names, [['Ana']]);
  flow.setLoading(100, true); flow.continue();
  assert.equal(flow.takeDestination(false), null);
  flow.dispose();
});

test('per-device persisted flags survive reload and clearing stays isolated from game progress', () => {
  const data = new Map(), storage = { getItem: key => data.get(key), setItem: (key, value) => data.set(key, value) };
  const savedGame = createSeenProgress({ storage });
  const phoneKey = 'pushboxInspectorSeen:360x800';
  const phone = createSeenProgress({ storage, key: phoneKey });
  const otherPhone = createSeenProgress({ storage, key: 'pushboxInspectorSeen:393x852' });
  savedGame.mark('carita');
  phone.mark('level:1'); phone.mark('scene:InterfazInstructions');
  otherPhone.mark('warning');
  const reloaded = createSeenProgress({ storage, key: phoneKey });
  assert.deepEqual(availableDestinations(reloaded).map(item => item.id), ['instructions', 'level-1']);
  assert.equal(savedGame.has('level:1'), false);
  assert.equal(otherPhone.has('level:1'), false);
  reloaded.clear();
  assert.deepEqual(createSeenProgress({ storage, key: phoneKey }).getSnapshot(), {});
  assert.equal(createSeenProgress({ storage }).has('carita'), true);
  assert.equal(createSeenProgress({ storage, key: 'pushboxInspectorSeen:393x852' }).has('warning'), true);
});
