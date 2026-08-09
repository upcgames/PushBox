import { GALLERY_GEN_FUNCTIONS as GALLERY_GEN } from '../generated_anim/gallery_registry.js';
import { VirtualConsole } from '../shims/virtual_console.js';
import { ConsoleColor } from '../shims/consoleColor.js';
import '../shims/audio_shim.js';
import { runAnim } from '../animationDriver.js';

// Canonical gallery - lazy consoles after DOM
let baseConsole, animConsole;
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

  if (!baseConsole) baseConsole = new VirtualConsole('baseCanvas', 80, 63, 14);
  if (!animConsole) animConsole = new VirtualConsole('animCanvas', 80, 63, 14, true);
  baseConsole.Clear();
  animConsole.Clear();
  window.Console = animConsole;

  const matriz = Array.from({ length: 136 }, () => Array(80).fill(0));
  const start = performance.now();
  await runAnim(generatorFn, matriz);
  const total = (performance.now() - start).toFixed(0);

  isPlaying = false;
  if (btn) { btn.disabled = false; btn.textContent = 'Play Animation'; }
  if (sel) { sel.disabled = false; }
  if (status) status.textContent = `Finished in ${total}ms`;
}

async function initGallery() {
  await document.fonts.ready;
  if (!baseConsole) baseConsole = new VirtualConsole('baseCanvas', 80, 63, 14);
  if (!animConsole) animConsole = new VirtualConsole('animCanvas', 80, 63, 14, true);
  window.Console = animConsole;

  const select = document.getElementById('animSelect');
  const btn = document.getElementById('playBtn');
  if (!select || !btn) return;
  for (const name of Object.keys(GALLERY_GEN)) {
    const opt = document.createElement('option');
    opt.value = name; opt.textContent = name;
    select.appendChild(opt);
  }
  btn.addEventListener('click', () => {
    const name = select.value;
    if (GALLERY_GEN[name]) playGenerator(GALLERY_GEN[name]);
  });
}

document.addEventListener('DOMContentLoaded', initGallery);

// Keep legacy export
export function startGeneratorOrchestrator(generatorFn) {
  playGenerator(generatorFn);
}
