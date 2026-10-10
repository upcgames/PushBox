// Transparent boiling bubbles keep the original gap color visible underneath.
export function drawLava(ctx, x, y, size, time, phase, contrast = 'light') {
  const ink = contrast === 'dark' ? '0, 0, 0' : '255, 255, 255';
  ctx.save();
  ctx.beginPath(); ctx.rect(x + 1, y + 1, size - 2, size - 2); ctx.clip();
  for (let bubble = 0; bubble < 3; bubble++) {
    const age = (time / 3.2 + phase + bubble / 3) % 1;
    const bx = x + 6 + bubble * 7 + Math.sin(time * 0.7 + bubble) * 0.8;
    const by = y + 7 + ((bubble * 7 + phase * 3) % 14);
    if (age < 0.75) {
      const radius = 0.6 + age * 3;
      ctx.globalAlpha = 1;
      ctx.fillStyle = 'rgba(0, 0, 0, 0.25)';
      ctx.strokeStyle = `rgba(${ink}, 0.75)`;
      ctx.lineWidth = 0.7;
      ctx.beginPath(); ctx.arc(bx, by, radius, 0, Math.PI * 2); ctx.fill(); ctx.stroke();
      ctx.fillStyle = `rgba(${ink}, 0.85)`;
      ctx.beginPath(); ctx.arc(bx - radius * 0.3, by - radius * 0.4, 0.45, 0, Math.PI * 2); ctx.fill();
    } else {
      const burst = (age - 0.75) / 0.25;
      ctx.globalAlpha = 1 - burst;
      ctx.fillStyle = `rgba(${ink}, 0.8)`;
      for (let ember = 0; ember < 5; ember++) {
        const angle = ember * Math.PI * 2 / 5;
        const reach = 2 + burst * 4;
        ctx.beginPath();
        ctx.arc(bx + Math.cos(angle) * reach,
          by + Math.sin(angle) * reach - Math.sin(burst * Math.PI) * 2,
          0.7, 0, Math.PI * 2);
        ctx.fill();
      }
    }
  }
  ctx.restore();
}
