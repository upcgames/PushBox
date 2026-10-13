import { GameState } from '../state/gameState.js';
import { feedbackScene, feedbackInputs, sameFeedbackInputs } from './model.js';
import { drawFeedback } from './draw.js';
import { sampleLavaContrast, sampleTileContrast } from './contrast.js';
import { drawWallImpact, WALL_IMPACT_DURATION } from './wallImpact.js';

const FRAME_INTERVAL = 1000 / 24;

export function setupBoardFeedback(baseCanvas, store = GameState, { mobile = () => false } = {}) {
  const canvas = document.createElement('canvas');
  canvas.className = 'board-feedback';
  canvas.setAttribute('aria-hidden', 'true');
  baseCanvas.parentElement.append(canvas);
  const ctx = canvas.getContext('2d');
  const reducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)');
  const completedAt = new Map();
  const contrastCache = new Map();
  let scene = null, previousGame = null;
  let frame = null, lastPaint = -Infinity, disposed = false;
  let contrastPending = false;
  let impact = null;

  function clear() { ctx.clearRect(0, 0, canvas.width, canvas.height); }
  function buildScene(inputs) {
    const next = feedbackScene(inputs);
    for (const cue of next?.cues || []) {
      if (cue.kind === 'danger') cue.contrast = contrastCache.get(`${next.level}:${cue.x},${cue.y}`);
    }
    return next;
  }
  function cancel() {
    if (frame !== null) window.cancelAnimationFrame(frame);
    frame = null;
  }
  function paint(time, sample = true) {
    frame = null;
    if (disposed || !scene || document.hidden) return;
    if (impact && time - impact.startedAt >= WALL_IMPACT_DURATION) {
      impact = null; lastPaint = -Infinity;
    }
    if (sample && contrastPending) {
      sampleLavaContrast(baseCanvas, scene);
      for (const cue of scene.cues) {
        if (cue.contrast) contrastCache.set(`${scene.level}:${cue.x},${cue.y}`, cue.contrast);
      }
      contrastPending = false;
      lastPaint = -Infinity;
    }
    const smooth = !!impact || scene.cues.some(cue => cue.kind === 'danger');
    if (smooth || time - lastPaint >= FRAME_INTERVAL) {
      clear();
      drawFeedback(ctx, scene, time, { motion: !reducedMotion.matches, completedAt, strongPush: mobile(), showPortal: !mobile() });
      if (impact) drawWallImpact(ctx, scene.grid, impact, time, !reducedMotion.matches);
      lastPaint = time;
    }
    if (!reducedMotion.matches || contrastPending || impact) frame = requestAnimationFrame(paint);
  }
  function redraw() {
    cancel(); lastPaint = -Infinity;
    // Paint new coordinates immediately, without a blank frame between moves.
    if (scene && !document.hidden && !disposed) paint(performance.now(), false);
    else clear();
  }
  function update(inputs) {
    const game = inputs.game;
    if (!game || game.level !== previousGame?.level) {
      completedAt.clear(); contrastCache.clear();
    }
    if (game) {
      const previouslyCovered = new Set(previousGame?.board.targets.filter(target => target.covered)
        .map(target => `${target.x},${target.y}`));
      for (const target of game.board.targets) {
        const key = `${target.x},${target.y}`;
        if (!target.covered) completedAt.delete(key);
        else if (previousGame?.level === game.level && !previouslyCovered.has(key)) {
          completedAt.set(key, performance.now());
        }
      }
    }
    previousGame = game;
    scene = buildScene(inputs);
    if (!scene || scene.level !== impact?.level) impact = null;
    contrastPending = !!scene;
    // Match the actual backing canvas as well as its shared responsive wrapper.
    if (canvas.width !== baseCanvas.width) canvas.width = baseCanvas.width;
    if (canvas.height !== baseCanvas.height) canvas.height = baseCanvas.height;
    redraw();
  }
  const stop = store.select(feedbackInputs, update, sameFeedbackInputs);
  function wallImpact(event) {
    if (!scene || document.hidden || event.level !== scene.level || event.obstacle?.kind !== 'wall') return;
    impact = { ...event.obstacle, direction: event.direction, level: event.level,
      contrast: sampleTileContrast(baseCanvas, scene.grid, event.obstacle), startedAt: performance.now() };
    redraw();
  }
  const stopImpacts = store.on('pushBlocked', event => { if (!mobile()) wallImpact(event); });
  const stopMovement = store.on('movementBlocked', event => { if (mobile()) wallImpact(event); });
  reducedMotion.addEventListener('change', redraw);
  document.addEventListener('visibilitychange', redraw);
  const dispose = () => {
    disposed = true; cancel(); stop(); stopImpacts(); stopMovement(); canvas.remove();
    reducedMotion.removeEventListener('change', redraw);
    document.removeEventListener('visibilitychange', redraw);
  };
  if (import.meta.hot) import.meta.hot.dispose(dispose);
  return dispose;
}
