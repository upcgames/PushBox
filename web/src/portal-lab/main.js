import { completion, sparks } from '../feedback/completion.js';
import { mount, unmount } from 'svelte';
import LorePreview from './LorePreview.svelte';
import { rewardScene } from '../presentation/loreIllustrations.js';
import InstructionPreview from './InstructionPreview.svelte';
import { rect, ladder, player, travel, lesson, palette, playerSprite } from '../presentation/instructionIllustrations.js';
import { mountSharedPreviews } from './sharedPreviews.js';
import './style.css';
import { drawPushCue } from '../feedback/pushCue.js';
import { drawWallImpact } from '../feedback/wallImpact.js';
import { drawBlockedBobby } from '../presentation/blockedBobby.js';
import { drawFeedback } from '../feedback/draw.js';
import { drawLava } from '../feedback/lava.js';
import { drawBobby, sampleBobby } from '../presentation/bobby.js';
import { mountOpeningSimulation } from './openingSimulation.js';
import { mountControlStudies } from './controlStudies.js';
import RewindEntrancePreview from './RewindEntrancePreview.svelte';
import StepsWarningPreview from './StepsWarningPreview.svelte';

import { INSPECTOR_DEVICES, deviceViewportMarkup, sizeDevicePreview } from '../inspector/deviceViewport.js';


const stopSharedPreviews = mountSharedPreviews(document.querySelector('#agreed-panel'));
const stopControlStudies = mountControlStudies(document.querySelector('#control-studies'));
const stepsWarning = mount(StepsWarningPreview, { target: document.querySelector('#steps-warning-preview') });
if (import.meta.hot) import.meta.hot.dispose(() => unmount(stepsWarning));
if (import.meta.hot) import.meta.hot.dispose(() => { stopSharedPreviews(); stopControlStudies(); });
const rewindEntrances = [...document.querySelectorAll('[data-rewind-entrance]')].map(host =>
  mount(RewindEntrancePreview, { target: host }));
const trollEntrance = mount(RewindEntrancePreview, { target: document.querySelector('[data-troll-entrance]'), props: { kind: 'troll' } });
if (import.meta.hot) import.meta.hot.dispose(() => unmount(trollEntrance));
if (import.meta.hot) import.meta.hot.dispose(() => rewindEntrances.forEach(instance => unmount(instance)));

const lorePreviews = [];
for (const host of document.querySelectorAll('[data-lore-preview]')) {
  const preview = mount(LorePreview, { target: host, props: { level: Number(host.dataset.lorePreview) } });
  lorePreviews.push(preview);
  const replay = document.createElement('button');
  replay.className = 'sample-action'; replay.textContent = 'Replay';
  replay.addEventListener('click', () => preview.replay());
  host.after(replay);
}
if (import.meta.hot) import.meta.hot.dispose(() => lorePreviews.forEach(instance => unmount(instance)));

const instructionContainer = document.querySelector('#instruction-devices');
const instructionSheets = [];
for (const device of INSPECTOR_DEVICES) {
  const card = document.createElement('article');
  card.className = 'instruction-device';
  card.innerHTML = `<h2>${device[0]} × ${device[1]}</h2>${deviceViewportMarkup('<div class="instruction-view"></div>')}<div class="viewport-size"></div><button class="sample-action instruction-replay">Replay</button>`;
  instructionContainer.append(card);
  sizeDevicePreview(card, device);
  const preview = mount(InstructionPreview, { target: card.querySelector('.instruction-view') });
  instructionSheets.push(preview);
  card.querySelector('.instruction-replay').addEventListener('click', () => preview.replay());
}
if (import.meta.hot) import.meta.hot.dispose(() => {
  instructionSheets.forEach(instance => unmount(instance));
  instructionContainer.replaceChildren();
});

// Static map assets and isolated drawing only: no runtime, controls, or audio.
mountOpeningSimulation(document.querySelector('#opening-simulation'), palette);
const canvases = [...document.querySelectorAll('canvas[data-kind]')];
const reducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)');
let matrix, maps, collisions, reviewLevel = 1;
const portals = [[36, 34], [42, 18], [36, 28], [38, 12], [40, 6]];
const floorColors = [6, 7, 5, 8, 2];
const boxColors = [14, 2, 16, 4, 5];


function base(ctx, px = 36, py = 34, source = matrix) {
  // Small local crop; subject at cell (5,4).
  for (let y = 0; y < 10; y++) {
    for (let x = 0; x < 12; x++) {
      rect(ctx, palette[source[py - 4 + y]?.[px - 5 + x] ?? 0], x * 14, y * 14, 14, 14);
    }
  }
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
    drawPushCue(ctx, x, y, 28, { x: 1, y: 0 }, t);
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


function bobby(ctx, t, trolling = false) {
  const pose = sampleBobby(t, { trolling });
  drawBobby(ctx, 70 - Math.round((pose.width - 28) / 2), 84 - pose.height, pose);
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







function blockedStudy(ctx, t) {
  rect(ctx, '#080914', 0, 0, 224, 140);
  rect(ctx, palette[6], 14, 56, 196, 28);
  rect(ctx, '#000000', 98, 56, 28, 28);
  const elapsed = t % 1200;
  drawBlockedBobby(ctx, 70, 56, elapsed, { x: 1, y: 0 });
  drawWallImpact(ctx, { cellSize: 14, objectSize: 2 }, {
    x: 7, y: 4, direction: { x: 1, y: 0 }, contrast: 'light', startedAt: 0,
  }, elapsed);
  ctx.font = '11px Px437'; ctx.fillStyle = '#b7b3c9'; ctx.textBaseline = 'top';
  ctx.fillText('BLOCKED', 14, 16);
}


const painters = { ladder, current,
  bobbyBreathe: (ctx, x, y, t) => bobby(ctx, t),
  bobbyTroll: (ctx, x, y, t) => bobby(ctx, t, true),
  lessonPush: (ctx, x, y, t) => lesson(ctx, t, 'push'),
  lessonDanger: (ctx, x, y, t) => lesson(ctx, t, 'danger'),
  lessonExit: (ctx, x, y, t) => lesson(ctx, t, 'exit'),
  lessonPushBurst: (ctx, x, y, t) => lesson(ctx, t, 'push', true),
  lessonDangerSink: (ctx, x, y, t) => lesson(ctx, t, 'danger', true),
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
