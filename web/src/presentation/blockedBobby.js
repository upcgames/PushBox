import { drawBobby } from './bobby.js';

export const BLOCKED_DURATION = 480;

// Keep the tile and its four outer corners fixed. Only the clipped interior
// trembles, following the accepted portal preview; no floor gaps or overflow.
export function drawBlockedBobby(ctx, x, y, elapsed, direction, options = {}, motion = true) {
  const size = (options.cellSize || 14) * 2;
  drawBobby(ctx, x, y, { ...options, width: size, height: size });
  if (!motion || elapsed < 0 || elapsed >= BLOCKED_DURATION) return;
  const offset = Math.round(Math.sin(elapsed / 1200 * 70) * 2);
  const inset = Math.round(size * 6 / 28);
  ctx.save(); ctx.beginPath(); ctx.rect(x + inset, y + inset, size - inset * 2, size - inset * 2); ctx.clip();
  drawBobby(ctx, x + offset * direction.x, y + offset * direction.y, { ...options, width: size, height: size });
  ctx.restore();
}
