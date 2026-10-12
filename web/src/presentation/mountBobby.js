import { BOBBY_PALETTE, drawBobby, sampleBobby } from './bobby.js';
import { drawBlockedBobby, BLOCKED_DURATION } from './blockedBobby.js';
import './bobby.css';

// One presentation owner per console/session. Named runtime scopes hand drawing
// back to the original routines before their first write, without changing timing.
export function mountBobby(surface, store, enabled = () => true) {
  const canvas = document.createElement('canvas');
  canvas.className = 'bobby-layer';
  canvas.setAttribute('aria-hidden', 'true');
  surface.canvas.parentElement.append(canvas);
  const ctx = canvas.getContext('2d');
  const reducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)');
  let state = store.getSnapshot(), active = false, frame = null, disposed = false;
  let previous = null, movement = null, blocked = null;

  function cancel() {
    if (frame !== null) cancelAnimationFrame(frame);
    frame = null;
  }
  function clear() { ctx.clearRect(0, 0, canvas.width, canvas.height); }
  function paint(time) {
    frame = null;
    clear();
    if (!active || disposed || document.hidden) return;
    if (canvas.width !== surface.canvas.width) canvas.width = surface.canvas.width;
    if (canvas.height !== surface.canvas.height) canvas.height = surface.canvas.height;
    const drawing = state.playerDrawing;
    const cellSize = surface.tileSize, size = cellSize * 2;
    const troll = state.trollActive || state.playerAnimation === 'TeclasOcultas';
    const pose = sampleBobby(time, { size, strength: 0.4,
      movement: movement && { ...movement, elapsed: time - movement.startedAt },
      trolling: troll, reducedMotion: reducedMotion.matches });
    let x = drawing.x * cellSize, y = drawing.y * cellSize;
    if (movement && !reducedMotion.matches) {
      x = (movement.from.x + movement.dx * pose.travel) * cellSize;
      y = (movement.from.y + movement.dy * pose.travel) * cellSize;
    }
    const options = { ...pose, cellSize, background: BOBBY_PALETTE[drawing.background],
      foreground: troll ? pose.foreground : BOBBY_PALETTE[drawing.foreground] };
    if (blocked && time - blocked.startedAt < BLOCKED_DURATION) {
      drawBlockedBobby(ctx, drawing.x * cellSize, drawing.y * cellSize, time - blocked.startedAt, blocked.direction, options, !reducedMotion.matches);
    } else drawBobby(ctx, x - Math.round((pose.width - size) / 2), y + size - pose.height, options);
    if (!reducedMotion.matches) frame = requestAnimationFrame(paint);
  }
  function refresh() {
    const drawing = state.playerDrawing;
    const nextActive = enabled() && state.screen?.id === 'gameplay' && !!state.game && !!drawing &&
      state.game.nextLevel === state.game.level &&
      (!state.playerAnimation || state.playerAnimation === 'TeclasOcultas');
    const now = performance.now();
    if (nextActive && active && previous && drawing.level === previous.level &&
        (drawing.x !== previous.x || drawing.y !== previous.y)) {
      blocked = null;
      movement = { from: previous, dx: drawing.x - previous.x, dy: drawing.y - previous.y, startedAt: now };
    } else if (!nextActive || !active) { movement = null; blocked = null; }
    previous = drawing;
    active = nextActive;
    surface.setPlayerHidden(active);
    cancel();
    paint(now);
  }
  const stop = store.subscribe(next => { state = next; refresh(); });
  const stopBlocked = store.on('movementBlocked', event => {
    if (!active || state.playerAnimation || document.hidden || event.level !== state.game.level) return;
    blocked = { direction: event.direction, startedAt: performance.now() };
    movement = null; cancel(); paint(blocked.startedAt);
  });
  document.addEventListener('visibilitychange', refresh);
  reducedMotion.addEventListener('change', refresh);
  return {
    refresh,
    dispose() {
      disposed = true; stop(); stopBlocked(); cancel(); surface.setPlayerHidden(false); canvas.remove();
      document.removeEventListener('visibilitychange', refresh);
      reducedMotion.removeEventListener('change', refresh);
    },
  };
}
