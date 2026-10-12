import { drawExitCue } from './exitCue.js';
import './exitCue.css';

// Replace only the visible mobile exit. The original console remains underneath
// and takes over immediately for canonical animations, including teleport/undo.
export function mountExitCue(surface, store, enabled = () => true) {
  const canvas = document.createElement('canvas');
  canvas.className = 'exit-layer';
  canvas.setAttribute('aria-hidden', 'true');
  surface.canvas.parentElement.append(canvas);
  const ctx = canvas.getContext('2d');
  const reducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)');
  let state = store.getSnapshot(), frame = null, disposed = false;
  function cancel() {
    if (frame !== null) cancelAnimationFrame(frame);
    frame = null;
  }
  function paint(time) {
    frame = null;
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    const game = state.game;
    if (disposed || document.hidden || !enabled() || state.screen?.id !== 'gameplay' ||
        !game?.portal.active || game.nextLevel !== game.level ||
        (state.playerAnimation && state.playerAnimation !== 'TeclasOcultas')) return;
    if (canvas.width !== surface.canvas.width) canvas.width = surface.canvas.width;
    if (canvas.height !== surface.canvas.height) canvas.height = surface.canvas.height;
    drawExitCue(ctx, game.portal.x * surface.tileSize, game.portal.y * surface.tileSize, time, {
      size: game.grid.objectSize * surface.tileSize, motion: !reducedMotion.matches,
    });
    if (!reducedMotion.matches) frame = requestAnimationFrame(paint);
  }
  function refresh() { cancel(); paint(performance.now()); }
  const stop = store.subscribe(next => { state = next; refresh(); });
  reducedMotion.addEventListener('change', refresh);
  document.addEventListener('visibilitychange', refresh);
  return {
    refresh,
    dispose() {
      disposed = true; stop(); cancel(); canvas.remove();
      reducedMotion.removeEventListener('change', refresh);
      document.removeEventListener('visibilitychange', refresh);
    },
  };
}
