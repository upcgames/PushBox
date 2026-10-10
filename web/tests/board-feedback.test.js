import test from 'node:test';
import assert from 'node:assert/strict';
import { feedbackScene } from '../src/feedback/model.js';
import { drawFeedback } from '../src/feedback/draw.js';
import { setupBoardFeedback } from '../src/feedback/boardFeedback.js';
import { createGameState } from '../src/state/gameState.js';
import { sampleLavaContrast } from '../src/feedback/contrast.js';

const state = () => ({ screen: { id: 'gameplay' }, inputRequest: { consumer: 'ControlDeMovimiento' },
  input: { stage: 'waiting' }, game: { level: 2, nextLevel: 2,
    player: { x: 2, y: 4 }, grid: { cols: 80, rows: 63, cellSize: 14, objectSize: 2 },
    board: { boxes: [{ x: 8, y: 4, index: 0, onTarget: false }, { x: 12, y: 4, index: 1, onTarget: true }],
      targets: [{ x: 2, y: 4, covered: false }, { x: 12, y: 4, covered: true }], gaps: [{ x: 16, y: 4 }] },
    portal: { x: 20, y: 4, active: true } } });

test('feedback marks targets, boxes, gaps and portal without obscuring the player', () => {
  const scene = feedbackScene(state());
  assert.deepEqual(scene.cues.map(cue => cue.kind), ['danger', 'target', 'box', 'complete', 'portal']);
  assert.equal(scene.cues.find(cue => cue.kind === 'target').showCenter, false);
  assert.equal(scene.cues.filter(cue => cue.x === 12 && cue.y === 4).length, 1);
});

test('feedback stays visible through input processing and hides on pause or level exit', () => {
  const snapshot = state();
  assert.equal(feedbackScene({ ...snapshot, game: null }), null);
  assert.equal(feedbackScene({ ...snapshot, screen: { id: 'InterfazPausa' } }), null);
  assert.deepEqual(feedbackScene({ ...snapshot, input: { stage: 'consumed' } }), feedbackScene(snapshot));
  assert.deepEqual(feedbackScene({ ...snapshot, inputRequest: null }), feedbackScene(snapshot));
  assert.equal(feedbackScene({ ...snapshot, game: { ...snapshot.game, nextLevel: 3 } }), null);
});

test('final-level hardened blocks stop inviting movement', () => {
  const snapshot = state();
  snapshot.game.board.gaps = [];
  snapshot.game.board.boxes = [{ x: 8, y: 4, index: 10, onTarget: false }];
  snapshot.game.level = snapshot.game.nextLevel = 5;
  const scene = feedbackScene(snapshot);
  assert.ok(!scene.cues.some(cue => cue.kind === 'danger'));
  assert.equal(scene.cues.find(cue => cue.x === 8).kind, 'locked');
});

test('box proximity follows cardinal tile distance, without guessing push legality', () => {
  const snapshot = state();
  const boxCue = () => feedbackScene(snapshot).cues.find(cue => cue.kind === 'box');
  assert.equal(boxCue().nearby, false);
  snapshot.game.player = { x: 6, y: 4 };
  assert.equal(boxCue().nearby, true);
  assert.deepEqual(boxCue().direction, { x: 1, y: 0 });
  snapshot.game.player = { x: 8, y: 6 };
  assert.equal(boxCue().nearby, true);
  assert.deepEqual(boxCue().direction, { x: 0, y: -1 });
  snapshot.game.player = { x: 6, y: 6 };
  assert.equal(boxCue().nearby, false);
});

test('gap feedback disappears when bridged', () => {
  const snapshot = state();
  snapshot.game.board.gaps = [];
  assert.ok(!feedbackScene(snapshot).cues.some(cue => cue.kind === 'danger'));
});

function recordingContext() {
  return { rectangles: [], paths: [], clears: 0, globalAlpha: 1, stack: [],
    clearRect() { this.rectangles = []; this.paths = []; this.clears++; },
    save() { this.stack.push(this.globalAlpha); this.paths.push(['save']); },
    restore() { this.globalAlpha = this.stack.pop(); this.paths.push(['restore']); },
    beginPath() { this.paths.push(['begin']); },
    rect(...args) { this.paths.push(['rect', ...args]); },
    clip() { this.paths.push(['clip']); },
    arc(...args) { this.paths.push(['arc', ...args]); },
    fill() { this.paths.push(['fill', typeof this.fillStyle === 'string' ? this.fillStyle : 'gradient', this.globalAlpha]); },
    stroke() { this.paths.push(['stroke', this.strokeStyle, this.globalAlpha]); },
    fillRect(x, y, width, height) {
      this.rectangles.push({ x, y, width, height,
        color: typeof this.fillStyle === 'string' ? this.fillStyle : 'gradient', opacity: this.globalAlpha });
    } };
}

test('lava chooses dark detail on white/yellow gaps and light detail on blue gaps', () => {
  for (const [rgb, expected] of [[[255, 255, 255], 'dark'], [[255, 255, 0], 'dark'], [[0, 0, 255], 'light']]) {
    const scene = feedbackScene(state());
    const base = { getContext: () => ({ getImageData(x, y, width, height) {
      assert.deepEqual([x, y, width, height], [237, 69, 3, 3]);
      return { data: Array.from({ length: 9 }, () => [...rgb, 255]).flat() };
    } }) };
    sampleLavaContrast(base, scene);
    assert.equal(scene.cues.find(cue => cue.kind === 'danger').contrast, expected);
  }
});

test('hidden final-level boxes have only proximity markers until the portal reveals them', () => {
  const snapshot = state();
  snapshot.game.level = snapshot.game.nextLevel = 5;
  snapshot.game.portal.active = false;
  snapshot.game.board.boxes[0].index = 10;
  assert.ok(!feedbackScene(snapshot).cues.some(cue => cue.x === 8));
  snapshot.game.player = { x: 6, y: 4 };
  const cue = feedbackScene(snapshot).cues.find(cue => cue.x === 8);
  assert.equal(cue.kind, 'box');
  assert.equal(cue.idle, false);
  for (const motion of [true, false]) {
    const ctx = recordingContext();
    drawFeedback(ctx, { ...feedbackScene(snapshot), cues: [cue] }, 1000, { motion });
    assert.ok(ctx.rectangles.length > 0);
    assert.ok(ctx.rectangles.every(rect => rect.color !== '#ffffff'));
  }
  snapshot.game.portal.active = true;
  snapshot.game.player = { x: 2, y: 4 };
  assert.equal(feedbackScene(snapshot).cues.find(cue => cue.x === 8).kind, 'locked');
});

test('reduced-motion rendering is stable and marks stay inside original tile bounds', () => {
  const snapshot = state();
  snapshot.game.player = { x: 6, y: 4 };
  const scene = feedbackScene(snapshot);
  const first = recordingContext(), second = recordingContext();
  drawFeedback(first, scene, 0, { motion: false });
  drawFeedback(second, scene, 4000, { motion: false });
  assert.deepEqual(first.rectangles, second.rectangles);
  assert.deepEqual(first.paths, second.paths);
  assert.equal(first.stack.length, 0);
  for (const rect of first.rectangles) {
    assert.ok(Number.isInteger(rect.x) && Number.isInteger(rect.y));
    assert.ok(scene.cues.some(cue => rect.x >= cue.x * 14 && rect.y >= cue.y * 14 &&
      rect.x + rect.width <= (cue.x + 2) * 14 && rect.y + rect.height <= (cue.y + 2) * 14));
  }
  assert.equal(first.globalAlpha, 1);
});

test('proximity chevrons travel across the box in under a second in every direction', () => {
  const scene = feedbackScene(state());
  for (const direction of [{ x: 1, y: 0 }, { x: -1, y: 0 }, { x: 0, y: 1 }, { x: 0, y: -1 }]) {
    const cue = { x: 8, y: 4, kind: 'box', nearby: true, idle: false, direction };
    const start = recordingContext(), end = recordingContext();
    drawFeedback(start, { ...scene, cues: [cue] }, 0);
    drawFeedback(end, { ...scene, cues: [cue] }, 300);
    const axis = direction.x ? 'x' : 'y';
    assert.ok(Math.abs(end.rectangles[1][axis] - start.rectangles[1][axis]) >= 9);
    for (const rect of [...start.rectangles, ...end.rectangles]) {
      assert.ok(rect.x >= 112 && rect.y >= 56 && rect.x + rect.width <= 140 && rect.y + rect.height <= 84);
    }
  }
});

test('completed cues stay steady while unfinished boxes and the portal gently change', () => {
  const scene = feedbackScene(state());
  const complete = { ...scene, cues: scene.cues.filter(cue => cue.kind === 'complete') };
  const a = recordingContext(), b = recordingContext();
  drawFeedback(a, complete, 0); drawFeedback(b, complete, 1000);
  assert.deepEqual(a.rectangles, b.rectangles);
  const c = recordingContext(), d = recordingContext();
  drawFeedback(c, scene, 0); drawFeedback(d, scene, 1000);
  assert.notDeepEqual(c.rectangles, d.rectangles);
  const box = { ...scene, cues: scene.cues.filter(cue => cue.kind === 'box') };
  const e = recordingContext(), f = recordingContext();
  drawFeedback(e, box, 0); drawFeedback(f, box, 1000);
  assert.notDeepEqual(e.rectangles.map(({ x, y }) => [x, y]), f.rectangles.map(({ x, y }) => [x, y]));
});

test('overlay follows the store, stops when hidden or disabled and releases subscriptions', () => {
  const original = { window: globalThis.window, document: globalThis.document,
    requestAnimationFrame: globalThis.requestAnimationFrame };
  const frames = new Map(), preferences = new Map(), context = recordingContext();
  let frameId = 0, removed = false, samples = 0;
  const motion = Object.assign(new EventTarget(), { matches: false });
  const canvas = { width: 0, height: 0, setAttribute() {}, getContext: () => context,
    remove() { removed = true; } };
  const base = { width: 1120, height: 882, parentElement: { append() {} },
    getContext: () => ({ getImageData() { samples++; return { data: new Array(36).fill(255) }; } }) };
  const button = Object.assign(new EventTarget(), { attrs: {},
    setAttribute(key, value) { this.attrs[key] = value; } });
  globalThis.requestAnimationFrame = callback => { const id = ++frameId; frames.set(id, callback); return id; };
  globalThis.window = { matchMedia: () => motion,
    cancelAnimationFrame: id => frames.delete(id),
    localStorage: { getItem: key => preferences.get(key), setItem: (key, value) => preferences.set(key, value) } };
  globalThis.document = Object.assign(new EventTarget(), { hidden: false, createElement: () => canvas });
  const store = createGameState();
  const tick = time => { const [id, callback] = frames.entries().next().value; frames.delete(id); callback(time); };
  let dispose;
  try {
    dispose = setupBoardFeedback(base, button, store.api);
    assert.equal(frames.size, 0);
    store.publish(state()); tick(0);
    assert.equal(canvas.width, 1120); assert.equal(canvas.height, 882);
    assert.ok(context.rectangles.length > 0);
    assert.equal(button.hidden, false);
    assert.ok(context.paths.some(path => path[0] === 'clip'));
    assert.ok(context.paths.some(path => path[0] === 'arc'));
    assert.equal(context.stack.length, 0);
    tick(performance.now() + 100);
    assert.ok(context.paths.some(path => path[0] === 'stroke' && path[1] === 'rgba(0, 0, 0, 0.75)'));
    const cachedSamples = samples;
    tick(performance.now() + 200);
    assert.equal(samples, cachedSamples);
    const beforeInput = context.clears;
    store.publish({ input: { stage: 'consumed' }, inputRequest: null });
    assert.equal(context.clears, beforeInput);
    assert.ok(context.rectangles.length > 0);
    const moved = state().game;
    moved.board.boxes[0].x = 10;
    store.publish({ game: moved });
    assert.ok(context.rectangles.some(rect => rect.x >= 140 && rect.x < 168));
    assert.ok(!context.rectangles.some(rect => rect.x >= 112 && rect.x < 140));
    const hit = { level: 2, direction: { x: 1, y: 0 }, obstacle: { x: 24, y: 4, kind: 'wall' } };
    const wallRipples = () => context.paths.filter(path => path[0] === 'arc' && path[1] === 338);
    store.event('pushBlocked', hit);
    assert.equal(wallRipples().length, 2);
    const beforeBoxCollision = context.clears;
    store.event('pushBlocked', { ...hit, obstacle: { ...hit.obstacle, kind: 'box' } });
    assert.equal(context.clears, beforeBoxCollision);
    store.event('pushBlocked', hit);
    assert.equal(wallRipples().length, 2);
    tick(performance.now() + 400);
    assert.equal(wallRipples().length, 0);
    button.dispatchEvent(new Event('click'));
    assert.equal(frames.size, 0); assert.equal(context.rectangles.length, 0);
    assert.equal(preferences.get('pushboxBoardHints'), 'off');
    button.dispatchEvent(new Event('click')); tick(50);
    document.hidden = true; document.dispatchEvent(new Event('visibilitychange'));
    assert.equal(frames.size, 0);
    document.hidden = false; document.dispatchEvent(new Event('visibilitychange')); tick(100);
    motion.matches = true; motion.dispatchEvent(new Event('change'));
    assert.equal(frames.size, 0); assert.ok(context.rectangles.length > 0);
    store.publish({ screen: { id: 'InterfazPausa' } });
    assert.equal(button.hidden, true); assert.equal(context.rectangles.length, 0);
    dispose(); const clears = context.clears;
    store.publish(state()); assert.equal(context.clears, clears);
    store.event('pushBlocked', hit); assert.equal(context.clears, clears);
    assert.equal(removed, true);
  } finally {
    dispose?.();
    for (const [key, value] of Object.entries(original)) {
      if (value === undefined) delete globalThis[key]; else globalThis[key] = value;
    }
  }
});
