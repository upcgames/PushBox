import { drawLava } from './lava.js';

export const FEEDBACK_COLORS = Object.freeze({
  box: '#fff0ba', target: '#000000',
  complete: '#a4f0bf', locked: '#b5c1c9', portal: '#d6c2ff',
});

// All strokes are rectangles on whole pixels, keeping the DOS grid crisp.
function corners(ctx, x, y, size, length, thickness = 2) {
  for (const [cx, cy, dx, dy] of [[x, y, 1, 1], [x + size, y, -1, 1],
    [x, y + size, 1, -1], [x + size, y + size, -1, -1]]) {
    ctx.fillRect(dx > 0 ? cx : cx - length, dy > 0 ? cy : cy - thickness, length, thickness);
    ctx.fillRect(dx > 0 ? cx : cx - thickness, dy > 0 ? cy : cy - length, thickness, length);
  }
}

function check(ctx, cx, cy) {
  for (const [x, y] of [[-4, 0], [-2, 2], [0, 0], [2, -2], [4, -4]]) {
    ctx.fillRect(cx + x, cy + y, 2, 2);
  }
}

function breathingCorners(ctx, x, y, size, breath, opacity) {
  const inset = 2 + Math.round(breath * 2);
  ctx.globalAlpha = opacity;
  corners(ctx, x + inset, y + inset, size - inset * 2, 6);
}

function glare(ctx, x, y, size, time, phase, secondary) {
  const inner = size - 4;
  const sweep = Math.floor(((time / 2600 + phase) % 1) * inner * 2);
  ctx.fillStyle = '#ffffff';
  ctx.globalAlpha = 0.22 * secondary;
  // A narrow diagonal sheen, clipped to the box interior using pixel rows.
  for (let row = 0; row < inner; row++) {
    const start = Math.max(0, sweep - row - 3);
    const end = Math.min(inner, sweep - row + 3);
    if (end > start) ctx.fillRect(x + 2 + start, y + 2 + row, end - start, 1);
  }
}

function pushNudges(ctx, cx, cy, size, direction, time, motion, secondary) {
  const { x: dx, y: dy } = direction;
  const travel = size - 8;
  ctx.globalAlpha = 0.9 * secondary;
  for (let mark = 0; mark < 2; mark++) {
    const progress = motion ? (time / 650 + mark * 0.5) % 1 : 0.3 + mark * 0.4;
    const distance = -(size / 2 - 5) + Math.floor(progress * travel);
    const px = cx + dx * distance, py = cy + dy * distance;
    for (const side of [-1, 0, 1]) {
      ctx.fillRect(px - Math.abs(side) * dx * 2 - side * dy * 2 - 1,
        py - Math.abs(side) * dy * 2 + side * dx * 2 - 1, 2, 2);
    }
  }
}

export function drawFeedback(ctx, scene, time = 0, { motion = true, completedAt = new Map() } = {}) {
  const { cellSize, objectSize } = scene.grid;
  const size = cellSize * objectSize;
  for (const cue of scene.cues) {
    const x = cue.x * cellSize, y = cue.y * cellSize;
    const cx = x + size / 2, cy = y + size / 2;
    const phase = (cue.x * 7 + cue.y * 11) / 30;
    const pulse = motion ? (Math.sin(time / 650 + phase) + 1) / 2 : 0.5;
    const breath = motion ? (Math.sin(time / 450 + phase) + 1) / 2 : 0.5;
    const secondary = scene.portalActive ? 0.65 : 1;
    if (FEEDBACK_COLORS[cue.kind]) ctx.fillStyle = FEEDBACK_COLORS[cue.kind];
    if (cue.kind === 'box') {
      if (cue.nearby) pushNudges(ctx, cx, cy, size, cue.direction, time, motion, secondary);
      else if (!motion && cue.idle !== false) {
        ctx.globalAlpha = 0.65 * secondary;
        corners(ctx, x + 2, y + 2, size - 4, 4);
      }
      if (motion && cue.idle !== false) glare(ctx, x, y, size, time, phase, secondary);
    } else if (cue.kind === 'target') {
      // Keep contrast constant; only the marker geometry breathes.
      breathingCorners(ctx, x, y, size, breath, 1);
      if (cue.showCenter !== false) {
        for (const [dx, dy] of [[0, -4], [4, 0], [0, 4], [-4, 0]]) {
          ctx.fillRect(cx + dx - 1, cy + dy - 1, 2, 2);
        }
      }
    } else if (cue.kind === 'danger') {
      drawLava(ctx, x, y, size, motion ? time / 1000 : 0, motion ? phase : 0, cue.contrast);
    } else if (cue.kind === 'complete' || cue.kind === 'locked') {
      ctx.globalAlpha = cue.kind === 'complete' ? 0.75 : 0.5;
      corners(ctx, x + 2, y + 2, size - 4, 4);
      if (cue.kind === 'complete') {
        check(ctx, cx, cy);
        const landed = completedAt.get(`${cue.x},${cue.y}`);
        const age = time - landed;
        if (motion && landed !== undefined && age >= 0 && age < 600) {
          ctx.globalAlpha = 0.16 * (1 - age / 600);
          ctx.fillRect(x + 2, y + 2, size - 4, size - 4);
        }
      }
    } else if (cue.kind === 'portal') {
      ctx.globalAlpha = 0.12 + pulse * 0.08;
      ctx.fillRect(x + 2, y + 2, size - 4, size - 4);
      ctx.globalAlpha = 0.8;
      corners(ctx, x + 1, y + 1, size - 2, 7);
      const inset = motion ? 5 + Math.floor((time % 1800) / 450) * 2 : 7;
      ctx.globalAlpha = motion ? 0.8 - (inset - 5) * 0.06 : 0.65;
      corners(ctx, x + inset, y + inset, size - inset * 2, 3, 1);
      ctx.fillRect(cx - 1, cy - 1, 2, 2);
    }
  }
  ctx.globalAlpha = 1;
}
