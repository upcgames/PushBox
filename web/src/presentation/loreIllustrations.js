import map5 from '../../pushbox_modules/maps_json/mapa05.json';
import collisions from '../../pushbox_modules/maps_json/collision_data.json';
import { rect, player, travel, sparks, palette } from './instructionIllustrations.js';
import { drawFeedback } from '../feedback/draw.js';
import { drawLava } from '../feedback/lava.js';
const floorColors = [6, 7, 5, 8, 2];

// The accepted UI illustrations, shared with the lab. This is not a game engine.
export function rewardScene(ctx, t, style = 'heart') {
  rect(ctx, '#080914', 0, 0, 224, 112);
  rect(ctx, palette[7], 28, 42, 168, 28);
  rect(ctx, '#ffffff', 112, 42, 28, 28);
  drawLava(ctx, 112, 42, 28, t / 1000, 0, 'dark');
  const cycle = t % 5000, age = cycle - 1940;
  player(ctx, 28 + travel(cycle), 42);
  if (age < 0) return;
  const p = Math.min(1, age / 1000);
  if (style === 'sparkles') {
    sparks(ctx, 126, 56, age / 900, '#fff0ba');
    if (age < 1000) {
      ctx.globalAlpha = 1 - p;
      ctx.strokeStyle = '#eab308'; ctx.lineWidth = 2;
      ctx.strokeRect(112 - p * 10, 42 - p * 10, 28 + p * 20, 28 + p * 20);
      ctx.globalAlpha = 1;
    }
  } else if (style === 'heart' && age < 1500) {
    const y = 32 - Math.round(Math.min(1, age / 1000) * 18);
    const pixels = ['.##.##.', '#######', '#######', '.#####.', '..###..', '...#...'];
    ctx.globalAlpha = Math.min(1, (1500 - age) / 400);
    for (let row = 0; row < pixels.length; row++) for (let col = 0; col < 7; col++) {
      if (pixels[row][col] === '#') rect(ctx, '#fff0ba', 119 + col * 2, y + row * 2, 2, 2);
    }
    ctx.globalAlpha = 1;
    sparks(ctx, 126, 56, age / 600, '#eab308');

  }
}

export function lore(ctx, t, level) {
  // RAF timestamps precede callback execution; a freshly mounted illustration
  // can receive a frame timestamp earlier than its performance.now() start.
  // Elapsed animation time starts at zero, never at a negative path index.
  t = Math.max(0, t);
  rect(ctx, '#080914', 0, 0, 224, 112);
  rect(ctx, palette[floorColors[level - 1]], 28, 42, 168, 28);
  const pulse = (Math.sin(t / 500) + 1) / 2;
  if (level === 1) {
    player(ctx, 42 + Math.min(3, Math.floor(t / 850) % 5) * 28, 42);
    const age = t % 850;
    const shake = age < 420 ? [-3, 3, -3, 3, -1, 0][Math.min(5, Math.floor(age / 70))] : 0;
    ctx.fillStyle = '#ef4444';
    ctx.font = '20px Px437'; ctx.textBaseline = 'top';
    ctx.fillText(String(5 - Math.floor(t / 850) % 5).padStart(3, '0'), 145 + shake, 12 + (shake ? (shake < 0 ? 2 : -2) : 0));
  } else if (level === 2) {
    rewardScene(ctx, t);
  } else if (level === 3) {
    const cycle = t % 5000, offset = travel(cycle), arrived = cycle >= 1940;
    rect(ctx, palette[12], 140, 42, 28, 28);
    drawLava(ctx, 140, 42, 28, t / 1000, 0, 'light');
    player(ctx, 28 + offset, 42);
    rect(ctx, palette[16], 56 + offset, 42, 28, 28);
    if (!arrived) drawFeedback(ctx, { grid: { cellSize: 14, objectSize: 2 }, portalActive: false,
      cues: [{ kind: 'box', x: (56 + offset) / 14, y: 3, nearby: true, direction: { x: 1, y: 0 } }] }, t);
    else {
      const age = cycle - 1940;
      const rise = Math.min(18, Math.round(age / 75));
      ctx.fillStyle = '#fff0ba'; ctx.font = '20px Px437'; ctx.textBaseline = 'top';
      ctx.fillText('?', 145, 45 - rise);
    }
  } else if (level === 4) {
    rect(ctx, '#080914', 28, 42, 168, 28);
    const y = 34 - Math.round(pulse * 2);
    for (const side of [-1, 1]) {
      const x = 112 + side * (38 + Math.round(pulse * 4));
      rect(ctx, '#eab308', x, y + 14, 2, 10); rect(ctx, '#eab308', x - 4, y + 18, 10, 2);
    }
  } else {
    // Actual level-5 center crop: walls, colored terrain, cajas and huecos.
    const source = map5.matrix, originX = 30, originY = 16;
    for (let y = 0; y < 16; y++) for (let x = 0; x < 20; x++) {
      rect(ctx, palette[source[originY + y]?.[originX + x] ?? 0], x * 14, y * 14, 14, 14);
    }
    const inCrop = (x, y) => x >= originX && x < originX + 20 && y >= originY && y < originY + 16;
    for (const [x, y] of collisions[5].holes) {
      if (!inCrop(x, y)) continue;
      const lx = (x - originX) * 14, ly = (y - originY) * 14;
      rect(ctx, palette[y === 14 ? 7 : 2], lx, ly, 28, 28);
      ctx.fillStyle = '#000000'; ctx.font = '14px Px437'; ctx.textBaseline = 'top';
      for (const [glyph, dx, dy] of [['┌', 0, 0], ['┐', 14, 0], ['└', 0, 14], ['┘', 14, 14]]) ctx.fillText(glyph, lx + dx, ly + dy);
    }
    collisions[5].boxes.forEach(([x, y], index) => {
      if (inCrop(x, y)) rect(ctx, palette[index < 10 ? 5 : 9], (x - originX) * 14, (y - originY) * 14, 28, 28);
    });
    // Six positions around a 3-column, 2-row rectangle beside the wall.
    const path = [[38, 24], [40, 24], [42, 24], [42, 26], [40, 26], [38, 26]];
    const stepDuration = 300;
    const cycle = t % (path.length * stepDuration);
    const step = Math.floor(cycle / stepDuration);
    const [px, py] = path[step];
    player(ctx, (px - originX) * 14, (py - originY) * 14);
    const age = cycle - stepDuration;
    if (age >= 0 && age < 1600) {
      const rise = Math.round(Math.min(1, age / 1200) * 18);
      const x = (40 - originX) * 14 + 12, y = (24 - originY) * 14 - 24 - rise;
      ctx.globalAlpha = Math.min(1, (1600 - age) / 350);
      rect(ctx, '#000000', x - 2, y - 1, 8, 21);
      rect(ctx, '#eab308', x, y + 1, 4, 11);
      rect(ctx, '#eab308', x, y + 16, 4, 3);
      ctx.globalAlpha = 1;
    }

  }
}
