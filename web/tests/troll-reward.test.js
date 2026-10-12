import test from 'node:test';
import assert from 'node:assert/strict';
import { createGameState } from '../src/state/gameState.js';
import { createSeenProgress } from '../src/state/seenProgress.js';
import { mountTrollReward } from '../src/presentation/trollReward.js';

function gameplay(level, placed, patch = {}) {
  return { screen: { id: 'gameplay' }, inputRequest: { kind: 'key', consumer: 'ControlDeMovimiento' },
    playerAnimation: null,
    game: { level, nextLevel: level, board: { boxes: Array.from({ length: 6 }, (_, index) => ({ index, onTarget: index < placed })) } },
    ...patch };
}
function memoryStorage() {
  const data = new Map();
  return { getItem: key => data.get(key), setItem: (key, value) => data.set(key, value) };
}

test('three canonical placed cajas in visible level four earn carita once and preserve it through undo/retry', () => {
  const storage = memoryStorage(), store = createGameState();
  let mobile = true;
  const reward = mountTrollReward(store.api, { progress: createSeenProgress({ storage }), enabled: () => mobile });
  store.publish(gameplay(1, 3));
  assert.equal(store.api.getSnapshot().trollReward.unlocked, false);
  store.publish(gameplay(4, 3, { screen: { id: 'Lore' } }));
  assert.equal(store.api.getSnapshot().trollReward.unlocked, false, 'lore illustration does not count as seeing the earned button');
  store.publish(gameplay(4, 2));
  assert.equal(store.api.getSnapshot().trollReward.unlocked, false);
  store.publish(gameplay(4, 3, { playerAnimation: 'Regresar' }));
  assert.equal(store.api.getSnapshot().trollReward.unlocked, false, 'wait for canonical animation to finish');
  mobile = false;
  store.publish(gameplay(4, 3));
  assert.equal(store.api.getSnapshot().trollReward.unlocked, false, 'desktop cannot mark an unseen mobile button');
  mobile = true; reward.refresh();
  assert.deepEqual(store.api.getSnapshot().trollReward, { unlocked: true, hinted: true });
  store.publish(gameplay(4, 2));
  store.publish(gameplay(4, 0));
  store.publish(gameplay(1, 0));
  assert.deepEqual(store.api.getSnapshot().trollReward, { unlocked: true, hinted: true });
  const reloaded = createGameState();
  const again = mountTrollReward(reloaded.api, { progress: createSeenProgress({ storage }) });
  reloaded.publish(gameplay(2, 0));
  assert.deepEqual(reloaded.api.getSnapshot().trollReward, { unlocked: true, hinted: true }, 'available in earlier levels after refresh');
  reloaded.api.useTrollReward();
  assert.deepEqual(reloaded.api.getSnapshot().trollReward, { unlocked: true, hinted: false });
  assert.equal(createSeenProgress({ storage }).has('caritaUsed'), true);
  const nextVisit = createGameState();
  const final = mountTrollReward(nextVisit.api, { progress: createSeenProgress({ storage }) });
  assert.deepEqual(nextVisit.api.getSnapshot().trollReward, { unlocked: true, hinted: false });
  reward.dispose(); again.dispose(); final.dispose();
});

test('preview progression remains local and unavailable storage still permits earning this visit', () => {
  const storage = memoryStorage(), preview = createGameState();
  const local = createSeenProgress({ storage: null });
  const reward = mountTrollReward(preview.api, { progress: local });
  preview.publish(gameplay(4, 3));
  assert.equal(local.has('carita'), true);
  assert.equal(createSeenProgress({ storage }).has('carita'), false);
  reward.dispose();
  const reset = createGameState();
  const restored = mountTrollReward(reset.api, { progress: local });
  assert.equal(reset.api.getSnapshot().trollReward.unlocked, true);
  restored.dispose();
  const unavailable = createGameState();
  const denied = createSeenProgress({ storage: { getItem() { throw new Error('blocked'); }, setItem() { throw new Error('blocked'); } } });
  const live = mountTrollReward(unavailable.api, { progress: denied });
  unavailable.publish(gameplay(4, 3));
  assert.equal(unavailable.api.getSnapshot().trollReward.unlocked, true);
  live.dispose();
  const hidden = createGameState();
  const disposed = mountTrollReward(hidden.api, { progress: createSeenProgress({ storage: null }) });
  disposed.dispose();
  hidden.publish(gameplay(4, 3));
  assert.equal(hidden.api.getSnapshot().trollReward.unlocked, false);
});

test('inspector clearing can reset first use or unlock without removing unrelated seen flags', () => {
  const storage = memoryStorage(), progress = createSeenProgress({ storage });
  progress.mark('carita'); progress.mark('caritaUsed'); progress.mark('otherScene');
  const store = createGameState();
  const reward = mountTrollReward(store.api, { progress });
  progress.clear('caritaUsed');
  assert.deepEqual(store.api.getSnapshot().trollReward, { unlocked: true, hinted: true });
  progress.clear(['carita', 'caritaUsed']);
  assert.deepEqual(store.api.getSnapshot().trollReward, { unlocked: false, hinted: false });
  assert.deepEqual(createSeenProgress({ storage }).getSnapshot(), { otherScene: true });
  progress.clear();
  assert.deepEqual(createSeenProgress({ storage }).getSnapshot(), {});
  reward.dispose();
});

test('saved seen flags synchronize with another tab and release storage listeners', () => {
  const previous = globalThis.window;
  const target = new EventTarget();
  globalThis.window = target;
  try {
    const storage = memoryStorage(), progress = createSeenProgress({ storage });
    let updates = 0;
    const stop = progress.subscribe(() => updates++);
    const notify = () => target.dispatchEvent(Object.assign(new Event('storage'), { key: 'pushboxSeen', storageArea: storage }));
    storage.setItem('pushboxSeen', JSON.stringify({ carita: true }));
    notify();
    assert.equal(progress.has('carita'), true);
    storage.setItem('pushboxSeen', '{}'); notify();
    assert.equal(progress.has('carita'), false);
    assert.equal(updates, 2);
    stop();
    storage.setItem('pushboxSeen', JSON.stringify({ carita: true })); notify();
    assert.equal(updates, 2);
  } finally {
    if (previous === undefined) delete globalThis.window;
    else globalThis.window = previous;
  }
});
