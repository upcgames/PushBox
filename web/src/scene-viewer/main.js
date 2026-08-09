import { GALLERY_GEN_FUNCTIONS as GALLERY_GEN } from '../generated_anim/gallery_registry.js';
import { ConsoleColor } from '../shims/consoleColor.js';
import '../shims/audio_shim.js';
import { runAnim } from '../animationDriver.js';
import { gameConsole } from '../shims/gameConsole.js';

// Single canonical console (like src/game.js) — no dual overlay
let gameConsoleRef = null;
window.ConsoleColor = ConsoleColor;

// Driver state
let isPlaying = false;

async function playGenerator(generatorFn) {
  if (isPlaying) return;
  isPlaying = true;
  const btn = document.getElementById('playBtn');
  const sel = document.getElementById('animSelect');
  const status = document.getElementById('status');
  if (btn) { btn.disabled = true; }
  if (sel) { sel.disabled = true; }
  if (status) status.textContent = 'Playing...';

  if (!gameConsoleRef) gameConsoleRef = gameConsole;
  await gameConsoleRef.loadAssets();
  gameConsoleRef.Clear();
  window.Console = gameConsoleRef;

  const matriz = Array.from({ length: 136 }, () => Array(80).fill(0));
  const start = performance.now();
  await runAnim(generatorFn, matriz);
  const total = (performance.now() - start).toFixed(0);

  isPlaying = false;
  if (btn) { btn.disabled = false; btn.textContent = 'Play Animation'; }
  if (sel) { sel.disabled = false; }
  if (status) status.textContent = `Finished in ${total}ms`;
}

function getAnimFromUrl() {
  return new window.URLSearchParams(window.location.search).get('anim');
}

function setAnimInUrl(name) {
  const url = new window.URL(window.location.href);
  if (name) url.searchParams.set('anim', name);
  else url.searchParams.delete('anim');
  window.history.replaceState(null, '', url);
}

async function initGallery() {
  if (!gameConsoleRef) gameConsoleRef = gameConsole;
  await gameConsoleRef.loadAssets();
  window.Console = gameConsoleRef;

  const select = document.getElementById('animSelect');
  const btn = document.getElementById('playBtn');
  if (!select || !btn) return;
  for (const name of Object.keys(GALLERY_GEN)) {
    const opt = document.createElement('option');
    opt.value = name; opt.textContent = name;
    select.appendChild(opt);
  }
  const initial = getAnimFromUrl();
  if (initial && GALLERY_GEN[initial]) select.value = initial;

  select.addEventListener('change', () => {
    if (GALLERY_GEN[select.value]) setAnimInUrl(select.value);
  });

  btn.addEventListener('click', () => {
    const name = select.value;
    if (GALLERY_GEN[name]) {
      setAnimInUrl(name);
      playGenerator(GALLERY_GEN[name]);
    }
  });

  window.addEventListener('popstate', () => {
    const next = getAnimFromUrl();
    if (next && GALLERY_GEN[next] && select.value !== next) select.value = next;
  });
}

document.addEventListener('DOMContentLoaded', initGallery);

// Keep legacy export
export function startGeneratorOrchestrator(generatorFn) {
  playGenerator(generatorFn);
}
