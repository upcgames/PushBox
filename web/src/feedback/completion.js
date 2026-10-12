// Shared placement artwork, consumed by gameplay and UI/lab illustrations.
function rect(ctx, color, x, y, width, height) {
  ctx.fillStyle = color;
  ctx.fillRect(Math.round(x), Math.round(y), width, height);
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

