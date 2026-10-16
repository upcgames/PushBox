// Accepted ladder and upward climbing light, shared by instructions, lab and game.
export function drawExitCue(ctx, x, y, time, { size = 28, motion = true } = {}) {
  ctx.save();
  ctx.translate(Math.round(x), Math.round(y));
  ctx.scale(size / 28, size / 28);
  const rect = (color, px, py, width, height) => {
    ctx.fillStyle = color;
    ctx.fillRect(px, py, width, height);
  };
  rect('#000', 0, 0, 28, 28);
  rect('#334155', 2, 2, 24, 2);
  rect('#334155', 2, 4, 2, 22);
  rect('#fff0ba', 4, -4, 3, 30);
  rect('#fff0ba', 21, -4, 3, 30);
  const active = motion ? 3 - Math.floor(time / 220) % 4 : 3;
  for (let rung = 0; rung < 4; rung++) {
    rect(rung === active ? '#ffffff' : '#eab308', 7, 3 + rung * 6, 14, rung === active ? 3 : 2);
  }
  rect('#000', 6, -10, 16, 6);
  rect('#eab308', 8, -8, 12, 2);
  ctx.restore();
}
