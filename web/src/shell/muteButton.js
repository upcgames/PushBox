import { GameState } from '../state/gameState.js';
import { setWebMuted } from '../shims/audio_shim.js';

let hideTimer = null;
let cleanup = null;
function scheduleFade(btn) {
  clearTimeout(hideTimer);
  btn.style.opacity = '1';
  hideTimer = setTimeout(() => {
    if (!GameState.getSnapshot().audio.muted) btn.style.opacity = '0.55';
  }, 2500);
}
export function setupMuteButton() {
  cleanup?.();
  const btn = document.getElementById('muteBtn');
  if (!btn) return;
  const stop = GameState.select(state => state.audio.muted, muted => {
    btn.textContent = muted ? '🔇' : '🔊';
    btn.classList.toggle('muted', muted);
    btn.setAttribute('aria-label', muted ? 'Unmute' : 'Mute');
    scheduleFade(btn);
  });
  const toggle = () => setWebMuted(!GameState.getSnapshot().audio.muted);
  btn.addEventListener('click', toggle);
  const frame = document.querySelector('.console-frame');
  const bump = () => scheduleFade(btn);
  for (const event of ['touchstart', 'mousemove']) frame?.addEventListener(event, bump, { passive: true });
  cleanup = () => {
    stop(); clearTimeout(hideTimer); btn.removeEventListener('click', toggle);
    for (const event of ['touchstart', 'mousemove']) frame?.removeEventListener(event, bump);
  };
}
export function showMuteButton() {
  const btn = document.getElementById('muteBtn');
  if (!btn) return;
  btn.classList.add('visible'); scheduleFade(btn);
}
if (import.meta.hot) import.meta.hot.dispose(() => cleanup?.());
