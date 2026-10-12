// Accepted traveling chevrons, shared by mobile gameplay and portal-lab.
// A dark outline and full-opacity pale pixels stay visible on every caja color.
export function drawPushCue(ctx, x, y, size, direction, time, motion = true) {
  const { x: dx, y: dy } = direction;
  const pixel = Math.max(2, Math.round(size / 9));
  ctx.save();
  ctx.beginPath(); ctx.rect(x + 1, y + 1, size - 2, size - 2); ctx.clip();
  ctx.globalAlpha = 1;
  for (let mark = 0; mark < 2; mark++) {
    const progress = motion ? (time / 1000 + mark * 0.5) % 1 : 0.25 + mark * 0.5;
    const distance = Math.round((progress - 0.5) * size / 2);
    // Center each pixel block, and compensate for the arrow's trailing arms.
    // Travel follows the push axis; the perpendicular axis stays tile-centered.
    const cx = Math.round(x + (size - pixel) / 2 + dx * (distance + pixel));
    const cy = Math.round(y + (size - pixel) / 2 + dy * (distance + pixel));
    const pixels = [];
    for (let side = -2; side <= 2; side++) {
      pixels.push([cx - Math.abs(side) * dx * pixel - side * dy * pixel,
        cy - Math.abs(side) * dy * pixel + side * dx * pixel]);
    }
    ctx.fillStyle = '#080914';
    for (const [px, py] of pixels) ctx.fillRect(px - 1, py - 1, pixel + 2, pixel + 2);
    ctx.fillStyle = '#fff0ba';
    for (const [px, py] of pixels) ctx.fillRect(px, py, pixel, pixel);
  }
  ctx.restore();
}
