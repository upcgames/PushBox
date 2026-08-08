import { VirtualConsole } from './shims/virtual_console.js';
import './shims/audio_shim.js';
import { GALLERY_FUNCTIONS } from './dsl/gallery_registry.js';

let isPlaying = false;

function loadGallery() {
  const select = document.getElementById('animationSelect');
  for (const funcName of Object.keys(GALLERY_FUNCTIONS)) {
    const option = document.createElement('option');
    option.value = funcName;
    option.textContent = funcName;
    select.appendChild(option);
  }
}

async function playAnimation() {
  if (isPlaying) return;
  
  const funcName = document.getElementById('animationSelect').value;
  if (!funcName || !GALLERY_FUNCTIONS[funcName]) return;

  const btn = document.getElementById('playBtn');
  const select = document.getElementById('animationSelect');
  
  try {
    isPlaying = true;
    btn.disabled = true;
    select.disabled = true;
    btn.textContent = "Playing...";

    // Wait for fonts to load before drawing
    await document.fonts.ready;

    // Re-initialize the virtual console so we start with a clean screen
    window.Console = new VirtualConsole('gameCanvas', 80, 60, 14);
    
    // Clear screen explicitly
    window.Console.Clear();

    // Allocate a blank 63x80 matrix just like the real game does
    const matriz = Array.from({ length: 63 }, () => new Array(80).fill(0));

    // Execute the animation directly using the statically imported function!
    await GALLERY_FUNCTIONS[funcName](matriz);

  } catch (e) {
    console.error("Error playing animation:", e);
    window.alert("Error playing animation. Check console.");
  } finally {
    isPlaying = false;
    btn.disabled = false;
    select.disabled = false;
    btn.textContent = "Play Animation";
  }
}

// Initialization
document.addEventListener('DOMContentLoaded', async () => {
  await loadGallery();
  
  // Set up blank console initially just so it's not a white square
  window.Console = new VirtualConsole('gameCanvas', 80, 60, 14);
  
  document.getElementById('playBtn').addEventListener('click', playAnimation);
});
