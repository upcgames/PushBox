import { continueButton } from './buttons.js';
import './style.css';
import { drawFeedback } from '../feedback/draw.js';
import { drawLava } from '../feedback/lava.js';
import { sampleSlugMotion } from './slugMotion.js';
import { mountOpeningSimulation } from './openingSimulation.js';
import { mountControlStudies } from './controlStudies.js';

import { INSPECTOR_DEVICES, deviceViewportMarkup, sizeDevicePreview } from '../inspector/deviceViewport.js';


mountControlStudies(document.querySelector('#control-studies'));

const instructionContainer = document.querySelector('#instruction-devices');
const lessons = `<div class="scene-card instruction-sheet"><h3>Instrucciones</h3>
  <div class="lesson"><span>01</span><div class="lesson-content"><canvas data-kind="lessonPushBurst" width="224" height="112" aria-label="Push boxes onto their targets"></canvas><h4>Empuja las cajas a su sitio</h4></div></div>
  <div class="lesson"><span>02</span><div class="lesson-content"><canvas data-kind="lessonDangerSink" width="224" height="112" aria-label="Death animation then sinking into lava"></canvas><h4>No te caigas.</h4></div></div>
  <div class="lesson"><span>03</span><div class="lesson-content"><canvas data-kind="lessonExit" width="224" height="112" aria-label="Climb to the next level"></canvas><h4>Pasa al siguiente nivel</h4></div></div>
${continueButton({ className: 'instruction-continue' })}</div>`;
for (const device of INSPECTOR_DEVICES) {
  const card = document.createElement('article');
  card.className = 'instruction-device';
  card.innerHTML = `<h2>${device[0]} × ${device[1]}</h2>${deviceViewportMarkup(`<div class="instruction-view">${lessons}</div>`)}<div class="viewport-size"></div>`;
  instructionContainer.append(card);
  sizeDevicePreview(card, device);
}

// Static map assets and isolated drawing only: no runtime, controls, or audio.
const palette = ['#000000', '#ffffff', '#ef4444', '#22c55e', '#3b82f6', '#06b6d4', '#d946ef', '#eab308', '#94a3b8', '#000000', '#991b1b', '#166534', '#1e3a8a', '#155e75', '#701a75', '#854d0e', '#334155'];
mountOpeningSimulation(document.querySelector('#opening-simulation'), palette);
const canvases = [...document.querySelectorAll('canvas[data-kind]')];
const reducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)');
let matrix, maps, collisions, reviewLevel = 1;
const portals = [[36, 34], [42, 18], [36, 28], [38, 12], [40, 6]];
const floorColors = [6, 7, 5, 8, 2];
const boxColors = [14, 2, 16, 4, 5];

function rect(ctx, color, x, y, width, height) {
  ctx.fillStyle = color;
  ctx.fillRect(Math.round(x), Math.round(y), width, height);
}

function base(ctx, px = 36, py = 34, source = matrix) {
  // Small local crop; subject at cell (5,4).
  for (let y = 0; y < 10; y++) {
    for (let x = 0; x < 12; x++) {
      rect(ctx, palette[source[py - 4 + y]?.[px - 5 + x] ?? 0], x * 14, y * 14, 14, 14);
    }
  }
}

function opening(ctx, x, y) {
  rect(ctx, '#080914', x, y, 28, 28);
  rect(ctx, '#334155', x + 2, y + 2, 24, 2);
  rect(ctx, '#334155', x + 2, y + 4, 2, 22);
}

function ladder(ctx, x, y, t) {
  opening(ctx, x, y);
  rect(ctx, '#fff0ba', x + 4, y - 4, 3, 30);
  rect(ctx, '#fff0ba', x + 21, y - 4, 3, 30);
  const active = 3 - Math.floor(t / 220) % 4;
  for (let rung = 0; rung < 4; rung++) {
    rect(ctx, rung === active ? '#ffffff' : '#eab308', x + 7, y + 3 + rung * 6, 14, rung === active ? 3 : 2);
  }
  rect(ctx, '#080914', x + 6, y - 10, 16, 6);
  rect(ctx, '#eab308', x + 8, y - 8, 12, 2);
}

function chevron(ctx, x, y, size) {
  const marks = [];
  for (let step = -2; step <= 2; step++) marks.push([x - Math.abs(step) * size, y + step * size]);
  for (const [cx, cy] of marks) rect(ctx, '#080914', cx - 1, cy - 1, size + 2, size + 2);
  for (const [cx, cy] of marks) rect(ctx, '#fff0ba', cx, cy, size, size);
}

function boxCue(ctx, x, y, t, traveling) {
  // Original level-1 caja color and the player's four corner glyphs.
  rect(ctx, palette[boxColors[reviewLevel - 1]], x, y, 28, 28);
  rect(ctx, palette[floorColors[reviewLevel - 1]], x - 28, y, 28, 28);
  player(ctx, x - 28, y);
  if (traveling) {
    for (let i = 0; i < 2; i++) {
      const progress = (t / 1000 + i * 0.5) % 1;
      chevron(ctx, x + 10 + Math.floor(progress * 14), y + 12, 3);
    }
  } else {
    drawFeedback(ctx, { grid: { cellSize: 14, objectSize: 2 }, portalActive: false,
      cues: [{ kind: 'box', x: x / 14, y: y / 14, nearby: true, direction: { x: 1, y: 0 } }] }, t);

  }
}

function current(ctx, x, y, t) {
  rect(ctx, palette[floorColors[reviewLevel - 1]], x, y, 28, 28);
  ctx.font = '14px Px437'; ctx.textBaseline = 'top'; ctx.fillStyle = palette[4];
  for (const dx of [0, 14]) for (const dy of [0, 14]) ctx.fillText('▓', x + dx, y + dy);
  drawFeedback(ctx, { grid: { cellSize: 14, objectSize: 2 }, portalActive: true,
    cues: [{ kind: 'portal', x: x / 14, y: y / 14 }] }, t);
}

function board(ctx, t) {
  for (let y = 0; y < 32; y++) for (let x = 0; x < 34; x++) {
    rect(ctx, palette[matrix[y + 9]?.[x + 21] ?? 0], x * 14, y * 14, 14, 14);
  }
  for (const [x, y] of [[30, 24], [32, 24], [40, 24], [42, 24]]) {
    rect(ctx, palette[14], (x - 21) * 14, (y - 9) * 14, 28, 28);
    drawFeedback(ctx, { grid: { cellSize: 14, objectSize: 2 }, portalActive: true,
      cues: [{ kind: 'complete', x: x - 21, y: y - 9 }] }, t);
  }
  player(ctx, (36 - 21) * 14, (32 - 9) * 14);
  ladder(ctx, (36 - 21) * 14, (34 - 9) * 14, t);
}

const playerSprite = document.createElement('canvas');
playerSprite.width = playerSprite.height = 28;
function player(ctx, x, y, color = '#ffffff', width = 28, height = 28) {
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

function bobby(ctx, t) {
  const wave = Math.sin(t / 320);
  const height = 28 + Math.round(wave * 4), width = 28 - Math.round(wave);
  player(ctx, 70 - Math.round((width - 28) / 2), 84 - height, '#ffffff', width, height);
}

function boxStrong(ctx, x, y, t, conveyor) {
  boxCue(ctx, x, y, t, false);
  rect(ctx, palette[boxColors[reviewLevel - 1]], x, y, 28, 28);
  ctx.save(); ctx.beginPath(); ctx.rect(x, y, 28, 28); ctx.clip();
  if (conveyor) {
    for (let i = 0; i < 3; i++) chevron(ctx, x - 2 + ((t / 45 + i * 14) % 42), y + 12, 4);
  } else {
    const ax = x + 7 + Math.floor(t / 100) % 6;
    rect(ctx, '#080914', ax - 10, y + 10, 13, 7);
    rect(ctx, '#fff0ba', ax - 9, y + 12, 11, 3);
    chevron(ctx, ax + 5, y + 12, 3);
  }
  ctx.restore();
  if (!conveyor) rect(ctx, '#fff0ba', x + 26, y + 5, 2, 18);
}

// Illustrations deliberately use short eased moves and stronger effects than gameplay.
function travel(t) {
  const elapsed = Math.max(0, t - 600), step = Math.min(3, Math.floor(elapsed / 600));
  const fraction = step === 3 ? 0 : Math.min(1, (elapsed % 600) / 140);
  return (step + fraction * fraction * (3 - 2 * fraction)) * 28;
}

function sparks(ctx, cx, cy, progress, color) {
  if (progress < 0 || progress > 1) return;
  for (let i = 0; i < 8; i++) {
    const angle = i * Math.PI / 4;
    ctx.globalAlpha = 1 - progress;
    rect(ctx, color, cx + Math.cos(angle) * (12 + progress * 25), cy + Math.sin(angle) * (12 + progress * 25), 3, 3);
  }
  ctx.globalAlpha = 1;
}

function completion(ctx, x, y, age, burst) {
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

function deadPlayer(ctx, x, y, age, width = 28, height = 28, tint = null) {
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

function destruction(ctx, x, y, age) {
  // Canonical 200ms death frames first, then the selected UI-only sink.
  if (age < 1400) { deadPlayer(ctx, x, y, age); return; }
  const p = Math.min(1, (age - 1400) / 700);
  if (p < 1) {
    const height = Math.max(1, Math.round(28 * (1 - p)));
    deadPlayer(ctx, x, y + 28 - height, 1400, 28, height, '#ef4444');
  }
}

function target(ctx, x, y) {
  rect(ctx, palette[6], x, y, 28, 28);
  ctx.fillStyle = palette[14]; ctx.font = '14px Px437'; ctx.textBaseline = 'top';
  for (const [glyph, dx, dy] of [['┌', 0, 0], ['┐', 14, 0], ['└', 0, 14], ['┘', 14, 14]]) ctx.fillText(glyph, x + dx, y + dy);
  drawFeedback(ctx, { grid: { cellSize: 14, objectSize: 2 }, portalActive: false,
    cues: [{ kind: 'target', x: x / 14, y: y / 14 }] }, 0, { motion: false });
}

function lesson(ctx, t, kind, variant = false) {
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
    rect(ctx, '#40214f', 112, 42, 28, 28);
    drawLava(ctx, 112, 42, 28, t / 1000, 0, 'light');
    if (!arrived) player(ctx, 28 + offset, 42);
    else destruction(ctx, 112, 42, cycle - 1940);
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

function moveStudy(ctx, t, mode) {
  rect(ctx, '#080914', 0, 0, 392, 280);
  const elapsed = (t % 900) - 120;
  const { travel: eased, longitudinal, transverse } = sampleSlugMotion(elapsed, { strength: mode === 'subtle' ? 0.4 : 1 });
  for (const [i, dx, dy, label] of [[0, 1, 0, 'RIGHT'], [1, -1, 0, 'LEFT'], [2, 0, 1, 'DOWN'], [3, 0, -1, 'UP']]) {
    ctx.save(); ctx.translate(i % 2 * 196, Math.floor(i / 2) * 140);
    rect(ctx, palette[6], 14, 28, 168, 98);
    const sx = dx < 0 ? 98 : dx > 0 ? 56 : 84;
    const sy = dy > 0 ? 28 : dy < 0 ? 84 : 56;
    const bx = sx + dx * (28 + eased * 28), by = sy + dy * (28 + eased * 28);
    rect(ctx, palette[14], bx, by, 28, 28);
    const width = dx ? longitudinal : transverse, height = dy ? longitudinal : transverse;
    const px = dx > 0 ? bx - width : dx < 0 ? bx + 28 : sx + (28 - width) / 2;
    const py = dy > 0 ? by - height : dy < 0 ? by + 28 : sy + 28 - height;
    player(ctx, px, py, '#ffffff', width, height);
    ctx.font = '10px Px437'; ctx.fillStyle = '#b7b3c9'; ctx.textBaseline = 'top'; ctx.fillText(label, 14, 8);
    ctx.restore();
  }
}

function blockedStudy(ctx, t) {
  rect(ctx, '#080914', 0, 0, 224, 140);
  rect(ctx, palette[6], 14, 56, 196, 28);
  rect(ctx, '#000000', 98, 56, 28, 28);
  const p = (t % 1200) / 1200;
  const offset = p < 0.4 ? Math.round(Math.sin(p * 70) * 2) : 0;
  player(ctx, 70, 56);
  // Keep the outer tile and frame intact; shake only the interior sprite.
  ctx.save(); ctx.beginPath(); ctx.rect(76, 62, 16, 16); ctx.clip();
  rect(ctx, '#000000', 76, 62, 16, 16);
  ctx.drawImage(playerSprite, 70 + offset, 56);
  ctx.restore();
  ctx.font = '11px Px437'; ctx.fillStyle = '#b7b3c9'; ctx.textBaseline = 'top';
  ctx.fillText('BLOCKED', 14, 16);
}

function rewardScene(ctx, t, style = 'heart') {
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

function lore(ctx, t, level) {
  rect(ctx, '#080914', 0, 0, 224, 112);
  rect(ctx, palette[floorColors[level - 1]], 28, 42, 168, 28);
  const pulse = (Math.sin(t / 500) + 1) / 2;
  if (level === 1) {
    player(ctx, 42 + Math.min(3, Math.floor(t / 850) % 5) * 28, 42);
    const age = t % 850;
    const shake = age < 420 ? [-3, 3, -3, 3, -1, 0][Math.min(5, Math.floor(age / 70))] : 0;
    ctx.fillStyle = age < 140 || (age >= 280 && age < 350) ? '#fff0ba' : '#ef4444';
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
    const source = maps[4].matrix, originX = 30, originY = 16;
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

const painters = { ladder, current,
  bobbyBreathe: (ctx, x, y, t) => bobby(ctx, t),
  lessonPush: (ctx, x, y, t) => lesson(ctx, t, 'push'),
  lessonDanger: (ctx, x, y, t) => lesson(ctx, t, 'danger'),
  lessonExit: (ctx, x, y, t) => lesson(ctx, t, 'exit'),
  lessonPushBurst: (ctx, x, y, t) => lesson(ctx, t, 'push', true),
  lessonDangerSink: (ctx, x, y, t) => lesson(ctx, t, 'danger', true),
  moveSlug: (ctx, x, y, t) => moveStudy(ctx, t, 'slug'),
  moveSubtle: (ctx, x, y, t) => moveStudy(ctx, t, 'subtle'),
  blockContained: (ctx, x, y, t) => blockedStudy(ctx, t),
  boxCurrent: (ctx, x, y, t) => boxCue(ctx, x, y, t, false),
  boxArrow: (ctx, x, y, t) => boxStrong(ctx, x, y, t, false),
  boxConveyor: (ctx, x, y, t) => boxStrong(ctx, x, y, t, true),
  boxTravel: (ctx, x, y, t) => boxCue(ctx, x, y, t, true),
};
function paint(time) {
  for (const canvas of canvases) {
    if (canvas.closest('[role=tabpanel]')?.hidden) continue;
    const ctx = canvas.getContext('2d');
    if (canvas.dataset.kind === 'board') { board(ctx, time); continue; }
    if (canvas.dataset.kind.startsWith('reward')) { rewardScene(ctx, time, canvas.dataset.kind.slice(6).toLowerCase()); continue; }
    if (canvas.dataset.kind.startsWith('lore')) { lore(ctx, time, Number(canvas.dataset.kind.slice(4))); continue; }
    const kind = canvas.dataset.kind;
    if (kind.startsWith('bobby') || kind.startsWith('lesson') || kind.startsWith('move') || kind.startsWith('block')) base(ctx);
    else {
      const [px, py] = kind.startsWith('box') ? (reviewLevel === 1 ? [36, 30] : collisions[reviewLevel].boxes[0]) : portals[reviewLevel - 1];
      base(ctx, px, py, maps[reviewLevel - 1].matrix);
    }
    painters[canvas.dataset.kind](ctx, 70, 56, time);
  }
}

async function load() {
  try {
    await document.fonts.load('14px Px437');
    const assets = await Promise.all(['mapa01', 'mapa02', 'mapa03', 'mapa04', 'mapa05', 'collision_data'].map(async name => {
      const response = await fetch(`${import.meta.env.BASE_URL}pushbox_modules/maps_json/${name}.json`);
      if (!response.ok) throw new Error(`${name}: ${response.status}`);
      return response.json();
    }));
    maps = assets.slice(0, 5); collisions = assets[5]; matrix = maps[0].matrix;
    document.querySelector('#status').hidden = true;
    const tick = time => {
      paint(reducedMotion.matches ? 0 : time);
      requestAnimationFrame(tick);
    };
    requestAnimationFrame(tick);
  } catch (error) {
    document.querySelector('#status').textContent = `Could not load previews: ${error.message}`;
  }
}
load();

// Local sample interactions only; never send commands to the game.
let steps = 8;
function takeStep() {
  steps = steps <= 1 ? 8 : steps - 1;
  document.querySelector('#critical-count').textContent = String(steps).padStart(3, '0');
  for (const hud of document.querySelectorAll('.critical')) {
    hud.classList.remove('jolt');
    void hud.offsetWidth;
    hud.classList.add('jolt');
  }
}
document.querySelector('#take-step').addEventListener('click', takeStep);

document.querySelector('#review-level').addEventListener('change', event => { reviewLevel = Number(event.target.value); });

const tabs = [...document.querySelectorAll('[role=tab]')];
function selectTab(tab) {
  for (const item of tabs) {
    const selected = item === tab;
    item.setAttribute('aria-selected', String(selected));
    item.tabIndex = selected ? 0 : -1;
    document.getElementById(item.dataset.panel).hidden = !selected;
  }
}
for (const tab of tabs) {
  tab.addEventListener('click', () => selectTab(tab));
  tab.addEventListener('keydown', event => {
    if (!['ArrowLeft', 'ArrowRight', 'Home', 'End'].includes(event.key)) return;
    event.preventDefault();
    const next = event.key === 'Home' ? tabs[0] : event.key === 'End' ? tabs[tabs.length - 1] : tabs[(tabs.indexOf(tab) + 1) % tabs.length];
    selectTab(next); next.focus();
  });
}
