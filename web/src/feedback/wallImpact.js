export const WALL_IMPACT_DURATION = 320;

export function drawWallImpact(ctx, grid, impact, time, motion = true) {
  const progress = (time - impact.startedAt) / WALL_IMPACT_DURATION;
  if (progress < 0 || progress >= 1) return;
  const { cellSize, objectSize } = grid;
  const size = cellSize * objectSize;
  const x = impact.x * cellSize, y = impact.y * cellSize;
  const { x: dx, y: dy } = impact.direction;
  const cx = x + size / 2 - dx * (size / 2 - 2);
  const cy = y + size / 2 - dy * (size / 2 - 2);
  const p = motion ? progress : 0.3;
  const ink = impact.contrast === 'dark' ? '#000000' : '#ffffff';
  ctx.save();
  ctx.beginPath(); ctx.rect(x + 1, y + 1, size - 2, size - 2); ctx.clip();
  ctx.strokeStyle = ink;
  ctx.globalAlpha = motion ? (1 - progress) * 0.9 : 0.8;
  ctx.lineWidth = 1.5;
  for (let ring = 0; ring < 2; ring++) {
    const radius = Math.max(1, p * size - ring * 5);
    ctx.beginPath(); ctx.arc(cx, cy, radius, 0, Math.PI * 2); ctx.stroke();
  }
  ctx.restore();
}
