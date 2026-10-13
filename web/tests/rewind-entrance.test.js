import test from 'node:test';
import assert from 'node:assert/strict';
import { sampleRewindEntrance, createRewindEntranceDriver, rewindEntranceGeometry } from '../src/presentation/rewindEntrance.js';
import { createGameState } from '../src/state/gameState.js';
import { createSeenProgress } from '../src/state/seenProgress.js';
import { mountRewindDiscovery } from '../src/presentation/rewindDiscovery.js';
import { mountTrollReward } from '../src/presentation/trollReward.js';

const geometry = { x: 82, y: 108, top: 38, right: 324, endX: 298, endY: 333 };
test('canonical coordinates map through canvas zoom and Inspector scaling into the actual slot', () => {
  const source = { level: 1, x: 40, y: 32 }, game = { level: 1, grid: { objectSize: 2 } };
  const surface = { tileSize: 14, canvas: { width: 1120, height: 882 } };
  const rects = { canvas: { left: -600, top: -750, width: 2240, height: 1764 },
    slot: { left: 500, top: 600, width: 64.6, height: 64.6 }, viewport: { right: 580 }, board: { top: 20 } };
  const measured = rewindEntranceGeometry(source, game, surface, rects);
  assert.deepEqual(measured.sourceBox, { x: 520, y: 146, width: 56, height: 56 });
  assert.equal(measured.x, 548); assert.equal(measured.y, 174);
  assert.equal(measured.scale, 0.85);
  assert.equal(measured.endX, 532.3); assert.equal(measured.endY, 632.3);
  assert.equal(rewindEntranceGeometry({ ...source, level: 2 }, game, surface, rects), null);
});
test('accepted boomerang preserves stationary reveal, curved flight, glow tail, and exact landing', () => {
  const popped = sampleRewindEntrance(400, geometry), departure = sampleRewindEntrance(900, geometry);
  assert.equal(popped.size, 48); assert.equal(popped.rotation, 0);
  assert.equal(departure.x, popped.x); assert.equal(departure.y, popped.y);
  assert.equal(departure.size, popped.size); assert.equal(departure.rotation, 0);
  assert.equal(sampleRewindEntrance(1200, geometry).glowOpacity, 1);
  assert.equal(sampleRewindEntrance(1400, geometry).glowOpacity, 0.5);
  assert.equal(sampleRewindEntrance(1500, geometry).glowOpacity, 0);
  const midflight = sampleRewindEntrance(1500, geometry);
  assert.ok(midflight.rotation < 0);
  assert.ok(midflight.x > geometry.endX, 'Outward sweep overshoots the slot horizontally before returning');
  const landing = sampleRewindEntrance(2550, geometry);
  assert.deepEqual([landing.x, landing.y, landing.size, landing.rotation, landing.complete], [298, 333, 40, -720, true]);
  const scaled = sampleRewindEntrance(2550, { ...geometry, scale: 0.85 });
  assert.equal(scaled.size, 34, 'Inspector scaling matches the destination icon');
});

function fixture({ reduced = false, learned = false } = {}) {
  const store = createGameState(() => assert.fail('Entrance must never send game input'));
  const progress = createSeenProgress({ storage: null });
  if (learned) progress.mark('rewind:recovered');
  const discovery = mountRewindDiscovery(store.api, { progress });
  const frames = new Map(), rendered = []; let id = 0, clears = 0;
  const driver = createRewindEntranceDriver(store.api, {
    measure: source => { assert.deepEqual(source, { level: 1, x: 40, y: 32 }); return geometry; },
    hidden: () => false, reducedMotion: () => reduced,
    render: pose => rendered.push(pose), clear: () => clears++,
    requestFrame: fn => { frames.set(++id, fn); return id; }, cancelFrame: token => frames.delete(token),
  });
  function reveal() {
    store.publish({ screen: { id: 'gameplay' }, game: { level: 1, nextLevel: 1 }, playerAnimation: null });
    store.api.setUndoHint(true, { level: 1, x: 40, y: 32 });
  }
  function tick(time) {
    const [token, callback] = frames.entries().next().value;
    frames.delete(token); callback(time);
  }
  return { store, progress, reveal, tick, frames, rendered, clears: () => clears,
    dispose() { driver.dispose(); discovery.dispose(); } };
}

test('runtime hides only the button during flight and acknowledges actual playback once per page', () => {
  const view = fixture();
  try {
    view.reveal(); assert.equal(view.store.api.getSnapshot().rewindEntranceActive, true);
    view.tick(0); assert.equal(view.store.api.getSnapshot().rewindDiscovery.entrancePending, false);
    assert.deepEqual(view.progress.getSnapshot(), {}, 'Entrance playback is not persisted');
    view.tick(900); view.tick(2550);
    assert.equal(view.store.api.getSnapshot().rewindEntranceActive, false);
    assert.equal(view.store.api.getSnapshot().rewindDiscovery.visible, true);
    assert.equal(view.frames.size, 0);
    view.store.api.setUndoHint(false); view.reveal();
    assert.equal(view.frames.size, 0, 'A later hint does not replay the entrance');
  } finally { view.dispose(); }
});

test('pause, canonical animation, scene exit, and disposal cancel overlays without retaining hidden controls', () => {
  for (const patch of [{ screen: { id: 'InterfazPausa' } }, { playerAnimation: 'Regresar' }, { game: null }]) {
    const view = fixture();
    try {
      view.reveal(); view.tick(0); view.store.publish(patch);
      assert.equal(view.frames.size, 0);
      assert.equal(view.store.api.getSnapshot().rewindEntranceActive, false);
      assert.ok(view.clears() > 0);
    } finally { view.dispose(); }
  }
  const view = fixture(); view.reveal(); view.dispose();
  assert.equal(view.frames.size, 0); assert.equal(view.store.api.getSnapshot().rewindEntranceActive, false);
  const failed = fixture();
  failed.reveal(); failed.store.event('runtimeError', {});
  assert.equal(failed.frames.size, 0, 'An error before the first frame cannot restart the entrance');
  assert.equal(failed.store.api.getSnapshot().rewindEntranceActive, false);
  failed.dispose();
});

test('reduced motion reveals immediately; previously learned recovery never schedules a flight', () => {
  const reduced = fixture({ reduced: true }), learned = fixture({ learned: true });
  try {
    reduced.reveal(); reduced.tick(0);
    assert.equal(reduced.frames.size, 0); assert.equal(reduced.rendered.length, 0);
    assert.equal(reduced.store.api.getSnapshot().rewindEntranceActive, false);
    learned.reveal(); assert.equal(learned.frames.size, 0);
    assert.equal(learned.store.api.getSnapshot().rewindDiscovery.visible, true);
  } finally { reduced.dispose(); learned.dispose(); }
});

test('carita uses the third placed caja and the shared entrance, then stays unlocked across interruption and reload', () => {
  const store = createGameState(() => assert.fail('Entrance cannot send input'));
  const progress = createSeenProgress({ storage: null });
  const reward = mountTrollReward(store.api, { progress });
  const frames = new Map(), sources = [], poses = []; let id = 0;
  const driver = createRewindEntranceDriver(store.api, {
    kind: 'troll', hidden: () => false,
    measure: source => { sources.push(source); return geometry; },
    render: pose => poses.push(pose), clear() {},
    requestFrame: fn => { frames.set(++id, fn); return id; }, cancelFrame: token => frames.delete(token),
  });
  const boxes = [0, 1, 2].map(index => ({ index, x: 10 + index * 2, y: 8, onTarget: index < 2 }));
  const game = { level: 4, nextLevel: 4, board: { boxes } };
  store.publish({ screen: { id: 'gameplay' }, inputRequest: { kind: 'key', consumer: 'ControlDeMovimiento' }, game });
  store.publish({ playerAnimation: 'Regresar', game: { ...game, board: { boxes: boxes.map(box => ({ ...box, onTarget: true })) } } });
  assert.equal(store.api.getSnapshot().trollReward.unlocked, false);
  store.publish({ playerAnimation: null });
  assert.equal(store.api.getSnapshot().trollEntrance.active, true);
  const tick = time => {
    const [token, callback] = frames.entries().next().value;
    frames.delete(token); callback(time);
  };
  tick(0); tick(1500);
  assert.deepEqual(sources.at(-1), { level: 4, x: 14, y: 8 });
  assert.deepEqual(poses.at(-1), sampleRewindEntrance(1500, geometry));
  tick(2550);
  assert.equal(store.api.getSnapshot().trollEntrance.active, false);
  assert.equal(store.api.getSnapshot().trollReward.unlocked, true);
  assert.equal(frames.size, 0);
  store.publish({ screen: { id: 'InterfazPausa' } });
  store.publish({ screen: { id: 'gameplay' } });
  assert.equal(frames.size, 0);
  driver.dispose(); reward.dispose();
  const reloaded = createGameState();
  const again = mountTrollReward(reloaded.api, { progress });
  assert.equal(reloaded.api.getSnapshot().trollReward.unlocked, true);
  assert.equal(reloaded.api.getSnapshot().trollEntrance.pending, false);
  again.dispose();
});

test('carita entrance interruption or reduced motion reveals the earned button without another flight', () => {
  for (const mode of ['pause', 'error', 'reduced']) {
    const store = createGameState(), frames = new Map(); let id = 0;
    const driver = createRewindEntranceDriver(store.api, {
      kind: 'troll', hidden: () => false, reducedMotion: () => mode === 'reduced',
      measure: () => geometry, render() {}, clear() {},
      requestFrame: fn => { frames.set(++id, fn); return id; }, cancelFrame: token => frames.delete(token),
    });
    store.publish({ screen: { id: 'gameplay' }, game: { level: 4, nextLevel: 4 },
      trollReward: { unlocked: true, hinted: true }, trollEntrance: { source: { level: 4, x: 14, y: 8 }, pending: true, active: false } });
    const [token, callback] = frames.entries().next().value; frames.delete(token); callback(0);
    if (mode === 'pause') store.publish({ screen: { id: 'InterfazPausa' } });
    if (mode === 'error') store.event('runtimeError', {});
    assert.equal(frames.size, 0);
    assert.equal(store.api.getSnapshot().trollEntrance.active, false);
    assert.equal(store.api.getSnapshot().trollReward.unlocked, true);
    driver.dispose();
  }
});
