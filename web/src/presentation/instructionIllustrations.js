import { drawExitCue } from './exitCue.js';
import { drawFeedback } from '../feedback/draw.js';
import { drawLava } from '../feedback/lava.js';

// UI illustrations only. These draw the lab and mobile instructions; they do
// not replace gameplay rendering, simulate game rules, or drive the runtime.
export const palette = ['#000000', '#ffffff', '#ef4444', '#22c55e', '#3b82f6', '#06b6d4', '#d946ef', '#eab308', '#94a3b8', '#000000', '#991b1b', '#166534', '#1e3a8a', '#155e75', '#701a75', '#854d0e', '#334155'];
export const playerSprite = document.createElement('canvas');
playerSprite.width = playerSprite.height = 28;

export function rect(ctx, color, x, y, width, height) {
  ctx.fillStyle = color;
  ctx.fillRect(Math.round(x), Math.round(y), width, height);
}

export function opening(ctx, x, y) {
  rect(ctx, '#080914', x, y, 28, 28);
  rect(ctx, '#334155', x + 2, y + 2, 24, 2);
  rect(ctx, '#334155', x + 2, y + 4, 2, 22);
}

export function ladder(ctx, x, y, t) {
  drawExitCue(ctx, x, y, t);
}

export function player(ctx, x, y, color = '#ffffff', width = 28, height = 28) {
  const sprite = playerSprite.getContext('2d');
  sprite.fillStyle = '#000000'; sprite.fillRect(0, 0, 28, 28);
  sprite.fillStyle = color; sprite.font = '14px Px437'; sprite.textBaseline = 'top';
  for (const [glyph, dx, dy] of [['╔', 0, 0], ['╗', 14, 0], ['╚', 0, 14], ['╝', 14, 14]]) {
    sprite.save(); sprite.beginPath(); sprite.rect(dx, dy, 14, 14); sprite.clip();
    sprite.fillText(glyph, dx, dy); sprite.restore();
  }
  ctx.imageSmoothingEnabled = false;
  ctx.drawImage(playerSprite, Math.round(x), Math.round(y), width, height);
}

export function travel(t, tiles = 3) {
  const elapsed = Math.max(0, t - 600), step = Math.min(tiles, Math.floor(elapsed / 600));
  const fraction = step === tiles ? 0 : Math.min(1, (elapsed % 600) / 140);
  return (step + fraction * fraction * (3 - 2 * fraction)) * 28;
}

export function sparks(ctx, cx, cy, progress, color) {
  if (progress < 0 || progress > 1) return;
  for (let i = 0; i < 8; i++) {
    const angle = i * Math.PI / 4;
    ctx.globalAlpha = 1 - progress;
    rect(ctx, color, cx + Math.cos(angle) * (12 + progress * 25), cy + Math.sin(angle) * (12 + progress * 25), 3, 3);
  }
  ctx.globalAlpha = 1;
}

export function completion(ctx, x, y, age, burst) {
  const p = Math.min(1, Math.max(0, age / 650));
  const size = burst ? 2 + Math.round(Math.sin(p * Math.PI) * 2) : 2 + Math.round(Math.sin(p * Math.PI) * 1);
  if (burst) sparks(ctx, x + 14, y + 14, age / 850, '#eab308');
  else {
    ctx.globalAlpha = 0.8 * (1 - p);
    const radius = 2 + Math.round(p * 10);
    ctx.strokeStyle = '#fff0ba'; ctx.lineWidth = 2;
    ctx.strokeRect(x - radius, y - radius, 28 + radius * 2, 28 + radius * 2);
    ctx.globalAlpha = 1;
  }
  for (const [dx, dy] of [[-2, 0], [-1, 1], [0, 0], [1, -1], [2, -2]]) {
    rect(ctx, '#080914', x + 14 + dx * size - 1, y + 14 + dy * size - 1, size + 2, size + 2);
    rect(ctx, '#a4f0bf', x + 14 + dx * size, y + 14 + dy * size, size, size);
  }
}

export function deadPlayer(ctx, x, y, age, width = 28, height = 28, tint = null) {
  const sprite = playerSprite.getContext('2d');
  sprite.fillStyle = tint ? '#b83c32' : '#ffffff'; sprite.fillRect(0, 0, 28, 28);
  const frame = Math.min(6, Math.floor(age / 200));
  sprite.fillStyle = tint ? '#ffb085' : palette[[2, 2, 10, 1, 8, 16, 9][frame]];
  sprite.font = '14px Px437'; sprite.textBaseline = 'top';
  const glyphs = frame === 0 ? ['■', '■', '■', '■'] : ['\\', '/', '/', '\\'];
  for (let i = 0; i < 4; i++) {
    const dx = i % 2 * 14, dy = Math.floor(i / 2) * 14;
    sprite.save(); sprite.beginPath(); sprite.rect(dx, dy, 14, 14); sprite.clip();
    sprite.fillText(glyphs[i], dx, dy); sprite.restore();
  }
  ctx.imageSmoothingEnabled = false;
  ctx.drawImage(playerSprite, x, y, width, height);
}

export function destruction(ctx, x, y, age) {
  // Canonical 200ms death frames first, then the selected UI-only sink.
  if (age < 1400) { deadPlayer(ctx, x, y, age); return; }
  const p = Math.min(1, (age - 1400) / 700);
  if (p < 1) {
    const height = Math.max(1, Math.round(28 * (1 - p)));
    deadPlayer(ctx, x, y + 28 - height, 1400, 28, height, '#ef4444');
  }
}

export function target(ctx, x, y) {
  rect(ctx, palette[6], x, y, 28, 28);
  ctx.fillStyle = palette[14]; ctx.font = '14px Px437'; ctx.textBaseline = 'top';
  for (const [glyph, dx, dy] of [['┌', 0, 0], ['┐', 14, 0], ['└', 0, 14], ['┘', 14, 14]]) ctx.fillText(glyph, x + dx, y + dy);
  drawFeedback(ctx, { grid: { cellSize: 14, objectSize: 2 }, portalActive: false,
    cues: [{ kind: 'target', x: x / 14, y: y / 14 }] }, 0, { motion: false });
}

export function lesson(ctx, t, kind, variant = false) {
  rect(ctx, '#080914', 0, 0, ctx.canvas.width, ctx.canvas.height);
  rect(ctx, palette[6], 14, 42, 196, 28);
  const cycle = t % 5000, offset = travel(cycle), arrived = cycle >= 1940;
  if (kind === 'push') {
    target(ctx, 140, 42);
    rect(ctx, palette[14], 56 + offset, 42, 28, 28);
    player(ctx, 28 + offset, 42);
    if (!arrived) drawFeedback(ctx, { grid: { cellSize: 14, objectSize: 2 }, portalActive: false,
      cues: [{ kind: 'box', x: (56 + offset) / 14, y: 3, nearby: true, direction: { x: 1, y: 0 } }] }, t);
    else completion(ctx, 140, 42, cycle - 1940, true);
  } else if (kind === 'danger') {
    const gapX = 140, arrival = 2540;
    for (const y of [14, 42, 70]) {
      rect(ctx, palette[6], 14, y, ctx.canvas.width - 14, 28);
      for (let x = gapX; x < ctx.canvas.width; x += 28) {
        rect(ctx, '#40214f', x, y, 28, 28);
        drawLava(ctx, x, y, 28, t / 1000, (x + y) / 112, 'light');
      }
      // The outer strips are blocked one tile before the gaps.
      if (y !== 42) rect(ctx, '#000000', gapX - 28, y, 28, 28);
    }
    if (cycle < arrival) player(ctx, 28 + travel(cycle, 4), 42);
    else destruction(ctx, gapX, 42, cycle - arrival);
  } else {
    ladder(ctx, 112, 42, t);
    if (!arrived) player(ctx, 28 + offset, 42);
    else {
      const p = Math.min(1, (cycle - 1940) / 1000);
      if (p < 1) {
        const size = Math.max(4, Math.round(28 * (1 - p * 0.6)));
        player(ctx, 112 + (28 - size) / 2, 42 - Math.round(p * 28), '#ffffff', size, size);
      }
    }
  }
}
