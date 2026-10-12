import { sampleSlugMotion } from './slugMotion.js';

// The original four CP437 corners, scaled as one sprite. No gameplay state here.
export const BOBBY_COLORS = ['#ffffff', '#ef4444', '#22c55e', '#3b82f6', '#06b6d4', '#d946ef', '#eab308'];
export const BOBBY_PALETTE = ['#000000', ...BOBBY_COLORS, '#94a3b8', '#000000', '#991b1b', '#166534', '#1e3a8a', '#155e75', '#701a75', '#854d0e', '#334155'];

export function sampleBobby(time, { size = 28, strength = 1, movement = null, trolling = false, reducedMotion = false } = {}) {
  let width = size, height = size, travel = 1;
  if (!reducedMotion) {
    if (movement && movement.elapsed < 320) {
      const motion = sampleSlugMotion(movement.elapsed, { size, strength });
      width = movement.dx ? motion.longitudinal : motion.transverse;
      height = movement.dy ? motion.longitudinal : motion.transverse;
      travel = motion.travel;
    } else {
      // Preserve the accepted portal idle exactly; strength applies to movement.
      const wave = Math.sin(time / 320);
      height += Math.round(wave * 4);
      width -= Math.round(wave);
    }
  }
  const foreground = trolling ? BOBBY_COLORS[reducedMotion ? 5 : Math.floor(time / 125) % BOBBY_COLORS.length] : '#ffffff';
  return { width, height, travel, foreground };
}

const sprites = new WeakMap();

export function drawBobby(ctx, x, y, { width = 28, height = 28, foreground = '#ffffff', background = '#000000', cellSize = 14 } = {}) {
  let canvas = sprites.get(ctx);
  if (!canvas) {
    canvas = ctx.canvas.ownerDocument.createElement('canvas');
    sprites.set(ctx, canvas);
  }
  const size = cellSize * 2;
  if (canvas.width !== size || canvas.height !== size) canvas.width = canvas.height = size;
  const sprite = canvas.getContext('2d');
  sprite.fillStyle = background;
  sprite.fillRect(0, 0, size, size);
  sprite.fillStyle = foreground;
  sprite.font = `${cellSize}px "Px437", monospace`;
  sprite.textBaseline = 'top';
  for (const [glyph, dx, dy] of [['╔', 0, 0], ['╗', cellSize, 0], ['╚', 0, cellSize], ['╝', cellSize, cellSize]]) {
    sprite.save(); sprite.beginPath(); sprite.rect(dx, dy, cellSize, cellSize); sprite.clip();
    sprite.fillText(glyph, dx, dy); sprite.restore();
  }
  ctx.imageSmoothingEnabled = false;
  ctx.drawImage(canvas, Math.round(x), Math.round(y), width, height);
}
