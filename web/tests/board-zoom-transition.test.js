import test from 'node:test';
import assert from 'node:assert/strict';
import { boardZoomTransform, createBoardZoomTransition, BOARD_ZOOM_DURATION } from '../src/presentation/boardZoomTransition.js';

const cropped = { left: -120, top: -200, width: 960, height: 756 };
const full = { left: 0, top: 60, width: 360, height: 283.5 };
function fixture() {
  const frame = { dataset: {} }, tasks = new Map(), animations = [];
  let sequence = 0, reduced = false;
  const style = { removeProperty(name) { delete this[name]; } };
  const wrap = { style, getBoundingClientRect: () => full, animate: (frames, options) => {
    let resolve, reject;
    const finished = new Promise((yes, no) => { resolve = yes; reject = no; });
    const animation = { frames, options, finished, finish: resolve, cancel: () => reject(new Error('cancelled')) };
    animations.push(animation); return animation;
  } };
  const zoom = createBoardZoomTransition(frame, wrap, {
    reducedMotion: () => reduced,
    schedule: callback => { tasks.set(++sequence, callback); return sequence; },
    cancelSchedule: id => tasks.delete(id),
  });
  return { zoom, frame, wrap, tasks, animations, reduce() { reduced = true; },
    tick() { const callbacks = [...tasks.values()]; tasks.clear(); callbacks.forEach(callback => callback()); } };
}
const enter = zoom => zoom.update({ active: true, rect: cropped, eligible: true, screen: 'gameplay' });
const scene = (zoom, screen) => zoom.update({ active: false, eligible: true, screen });

test('zoom maps live cropped console geometry into full framing and cleans up after completion', async () => {
  const view = fixture(); enter(view.zoom); scene(view.zoom, 'InterfazPausa');
  assert.equal(view.wrap.style.transform, boardZoomTransform(cropped, full), 'Hold old pose before the next frame');
  view.tick();
  assert.equal(view.animations.length, 1);
  assert.equal(view.animations[0].options.duration, BOARD_ZOOM_DURATION);
  assert.deepEqual(view.animations[0].frames, [{ transform: boardZoomTransform(cropped, full) }, { transform: 'none' }]);
  scene(view.zoom, 'InterfazPausa');
  assert.equal(view.tasks.size, 0, 'Repeated runtime paints do not restart the zoom');
  view.animations[0].finish(); await Promise.resolve();
  assert.equal(view.frame.dataset.framingTransition, undefined);
  assert.equal(view.wrap.style.transform, undefined);
});

test('win/loss exits survive transient gameplay teardown; lore never gets an entrance animation', () => {
  for (const target of ['InterfazYouWin', 'InterfazYouLose', 'InterfazCongratulations', 'InterfazGameOver']) {
    const view = fixture(); enter(view.zoom);
    scene(view.zoom, 'gameplay'); scene(view.zoom, 'main'); scene(view.zoom, target); view.tick();
    assert.equal(view.animations.length, 1, target);
    view.zoom.dispose();
  }
  const view = fixture(); enter(view.zoom); scene(view.zoom, 'main'); scene(view.zoom, 'Lore'); view.tick();
  assert.equal(view.animations.length, 0);
  enter(view.zoom); view.tick(); assert.equal(view.animations.length, 0, 'Gameplay returns immediately');
});

test('desktop/full-console modes, reduced motion, scene changes and disposal cancel queued transitions', () => {
  const view = fixture(); enter(view.zoom); scene(view.zoom, 'InterfazPausa');
  view.zoom.update({ active: false, screen: 'InterfazPausa', eligible: false }); view.tick();
  assert.equal(view.animations.length, 0);
  enter(view.zoom); scene(view.zoom, 'InterfazPausa'); scene(view.zoom, 'Lore'); view.tick();
  assert.equal(view.animations.length, 0);
  enter(view.zoom); view.reduce(); scene(view.zoom, 'InterfazYouLose'); view.tick();
  assert.equal(view.animations.length, 0);
  const other = fixture(); enter(other.zoom); scene(other.zoom, 'InterfazPausa'); other.zoom.dispose(); other.tick();
  assert.equal(other.animations.length, 0);
  assert.equal(other.wrap.style.transform, undefined);
  assert.equal(boardZoomTransform({ ...cropped, width: 0 }, full), null);
});

test('offsets use local CSS pixels under scaled Inspector phones', () => {
  const transformed = boardZoomTransform(
    { left: 50, top: 100, width: 600, height: 450 },
    { left: 100, top: 200, width: 200, height: 150 },
    { width: 400, height: 300 },
  );
  assert.equal(transformed, 'translate(-100px, -200px) scale(3, 3)');
});

test('Resume zooms from full console into an offset cropped canvas and ignores ordinary gameplay updates', async () => {
  const view = fixture();
  const canvas = { getBoundingClientRect: () => cropped };
  const zoom = createBoardZoomTransition(view.frame, view.wrap, { canvas,
    schedule: callback => { view.tasks.set(1, callback); return 1; }, cancelSchedule: id => view.tasks.delete(id),
    reducedMotion: () => false,
  });
  zoom.update({ active: true, screen: 'gameplay', rect: cropped, eligible: true, resumeFrom: full });
  assert.equal(view.frame.dataset.framingTransition, 'in');
  assert.equal(view.wrap.style.transform, 'translate(45px, 97.5px) scale(0.375, 0.375)');
  view.tick();
  zoom.update({ active: true, screen: 'gameplay', rect: cropped, eligible: true });
  assert.equal(view.animations.length, 1);
  assert.equal(view.frame.dataset.framingTransition, 'in');
  assert.equal(view.animations[0].options.duration, BOARD_ZOOM_DURATION);
  view.animations[0].finish(); await Promise.resolve();
  assert.equal(view.frame.dataset.framingTransition, undefined);
  zoom.dispose();
});

test('retry/exit and lore returns have no Resume zoom; re-pausing cancels an in-progress zoom', () => {
  for (const previous of ['InterfazPausa', 'Lore']) {
    const view = fixture(); scene(view.zoom, previous); enter(view.zoom); view.tick();
    assert.equal(view.animations.length, 0);
  }
  const view = fixture();
  view.zoom.update({ active: true, screen: 'gameplay', rect: cropped, eligible: true, resumeFrom: full });
  view.tick();
  scene(view.zoom, 'Lore');
  assert.equal(view.frame.dataset.framingTransition, undefined);
  assert.equal(view.wrap.style.transform, undefined);
  const reduced = fixture(); reduced.reduce();
  reduced.zoom.update({ active: true, screen: 'gameplay', rect: cropped, eligible: true, resumeFrom: full });
  reduced.tick(); assert.equal(reduced.animations.length, 0);
});
