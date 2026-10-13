import { GameState } from '../state/gameState.js';
import { setWebMuted } from '../shims/audio_shim.js';
import { mountSoundButton } from '../presentation/mountSoundButton.js';

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
  const stopButton = mountSoundButton(btn, GameState, { setWebMuted });
  const stop = GameState.select(state => state.audio.muted, muted => {
    btn.classList.toggle('muted', muted);
    scheduleFade(btn);
  });
  const frame = document.querySelector('.console-frame');
  const bump = () => scheduleFade(btn);
  for (const event of ['touchstart', 'mousemove']) frame?.addEventListener(event, bump, { passive: true });
  cleanup = () => {
    stop(); stopButton(); clearTimeout(hideTimer);
    for (const event of ['touchstart', 'mousemove']) frame?.removeEventListener(event, bump);
  };
}
export function showMuteButton() {
  const btn = document.getElementById('muteBtn');
  if (!btn) return;
  btn.classList.add('visible'); scheduleFade(btn);
}
if (import.meta.hot) import.meta.hot.dispose(() => cleanup?.());
