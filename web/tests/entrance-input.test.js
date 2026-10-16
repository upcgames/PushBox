import test from 'node:test';
import assert from 'node:assert/strict';
import { createGameState } from '../src/state/gameState.js';
import { createRuntimeBridge } from '../src/state/runtimeBridge.js';
import { createSessionShims } from '../src/runtime/sessionShims.js';
import { createRewindEntranceDriver } from '../src/presentation/rewindEntrance.js';

function fixture(kind, { enabled = true, reduced = false } = {}) {
  const store = createGameState(), bridge = createRuntimeBridge(store), abort = new AbortController();
  const stopAcknowledgement = store.api.on('rewindEntrancePlayed', () =>
    store.api.setRewindDiscovery({ visible: true, entrancePending: false }));
  const platform = createSessionShims({}, bridge, { config: {}, audio: {}, signal: abort.signal,
    requestFrame: () => 0, cancelFrame() {} });
  const frames = new Map(); let id = 0;
  const driver = createRewindEntranceDriver(store.api, {
    kind, enabled: () => enabled, hidden: () => false, reducedMotion: () => reduced,
    measure: () => ({ x: 0, y: 0, top: 0, right: 100, endX: 50, endY: 100, scale: 1 }),
    render() {}, clear() {}, requestFrame: fn => { frames.set(++id, fn); return id; },
    cancelFrame: token => frames.delete(token),
  });
  store.publish({ screen: { id: 'gameplay' }, game: { level: 1, nextLevel: 1 } });
  function reveal() {
    const source = { level: 1, x: 10, y: 10 };
    if (kind === 'troll') store.publish({ trollReward: { unlocked: true, hinted: true },
      trollEntrance: { source, pending: true, active: false } });
    else store.publish({ undoHint: true, undoHintSource: source,
      rewindDiscovery: { visible: true, entrancePending: true } });
  }
  function tick(time) {
    const [token, callback] = frames.entries().next().value;
    frames.delete(token); callback(time);
  }
  return { store, bridge, platform, reveal, tick,
    dispose() { driver.dispose(); stopAcknowledgement(); abort.abort(); } };
}

for (const kind of ['rewind', 'troll']) {
  test(`${kind} entrance discards buffered and new moves, keeps pause/audio, and restores input on landing`, async () => {
    const view = fixture(kind), { platform, bridge } = view;
    try {
      platform.sendInput('w'); platform.sendInput('d');
      view.reveal();
      assert.equal(platform.shims._kbhit(), 0, 'Previously buffered moves are discarded immediately');
      view.tick(0);
      const waiting = platform.shims._getch();
      let settled = false; waiting.then(() => { settled = true; });
      for (const key of ['w', 'A', 's', 'd', 'r']) platform.sendInput(key);
      await Promise.resolve(); assert.equal(settled, false);
      platform.sendInput('f'); assert.equal(view.store.api.getSnapshot().audio.muted, true);
      platform.sendInput('p'); assert.equal(await waiting, 'p', 'Pause stays available');
      view.tick(1500); assert.equal(bridge.inputBlocked('w'), true);
      view.tick(2550); assert.equal(bridge.inputBlocked('w'), false);
      assert.equal(platform.shims._kbhit(), 0, 'Blocked inputs never replay after landing');
      platform.sendInput('d'); assert.equal(await platform.shims._getch(), 'd');
    } finally { view.dispose(); }
  });

  test(`${kind} entrance releases input on cancellation, errors, and reduced motion; desktop stays available`, () => {
    for (const mode of ['pause', 'error', 'dispose', 'reduced', 'desktop']) {
      const view = fixture(kind, { enabled: mode !== 'desktop', reduced: mode === 'reduced' });
      try {
        view.reveal();
        if (mode === 'desktop') { assert.equal(view.bridge.inputBlocked('w'), false); continue; }
        view.tick(0);
        if (mode === 'pause') view.store.publish({ screen: { id: 'InterfazPausa' } });
        if (mode === 'error') view.store.event('runtimeError', {});
        if (mode === 'dispose') view.dispose();
        assert.equal(view.bridge.inputBlocked('w'), false, mode);
      } finally { view.dispose(); }
    }
  });
}

test('overlapping entrances keep input blocked until both have finished', () => {
  const store = createGameState(), bridge = createRuntimeBridge(store);
  store.publish({ screen: { id: 'gameplay' } });
  store.api.setRewindEntranceActive(true);
  store.api.setTrollEntrance({ source: null, pending: false, active: true });
  store.api.setRewindEntranceActive(false);
  assert.equal(bridge.inputBlocked('w'), true);
  store.api.setTrollEntrance({ source: null, pending: false, active: false });
  assert.equal(bridge.inputBlocked('w'), false);
});
