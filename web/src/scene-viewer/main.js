import { GALLERY_GEN_FUNCTIONS as GALLERY_GEN } from '../generated_anim/gallery_registry.js';
import { ConsoleColor } from '../shims/consoleColor.js';
import { preloadAudio } from '../shims/audio_shim.js';
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
  await gameConsoleRef.loadFonts();
  try { await preloadAudio(); } catch (e) { console.warn('[scene-viewer] preloadAudio failed:', e); }
  gameConsoleRef.Clear();
  window.Console = gameConsoleRef;

  const matriz = Array.from({ length: 136 }, () => Array(80).fill(0));
  const start = performance.now();
  // Gallery functions have varying arities — InterfazCongratulations needs Cantidades
  const fnName = generatorFn.name || '';
  let args = [matriz];
  if (fnName === 'InterfazCongratulations' || generatorFn.length >= 2) {
    const Cantidades = Array.from({ length: 9 }, () => Array(8).fill(0));
    // Mirror main's default PLAYER stub (else branch) so the gallery doesn't crash on Cantidades[8]
    Cantidades[8][0] = '1';
    Cantidades[8][1] = 6;
    Cantidades[6][0] = 'P'; Cantidades[6][1] = 'L'; Cantidades[6][2] = 'A'; Cantidades[6][3] = 'Y'; Cantidades[6][4] = 'E'; Cantidades[6][5] = 'R';
    // Provide char codes like C++ int(n1[i]) — keep as strings so '1'/'2' checks work, gallery only needs first display
    args = [matriz, Cantidades];
  }
  await runAnim(generatorFn, ...args);
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
  await gameConsoleRef.loadFonts();
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
