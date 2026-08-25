let muted = false;
let hideTimer = null;

function dispatchMuteKey() {
  const key = 'f';
  const evt = new window.KeyboardEvent('keydown', { key, bubbles: true });
  window.dispatchEvent(evt);
  // Also toggle web audio shim directly so mute works even outside gameplay input loop
  import('../shims/audio_shim.js').then(m => m.setWebMuted && m.setWebMuted(muted)).catch(() => {});
}

function setMutedState(btn, isMuted) {
  muted = isMuted;
  btn.textContent = muted ? '🔇' : '🔊';
  btn.classList.toggle('muted', muted);
  btn.setAttribute('aria-label', muted ? 'Unmute' : 'Mute');
}

function scheduleFade(btn) {
  if (hideTimer) clearTimeout(hideTimer);
  btn.style.opacity = '1';
  hideTimer = setTimeout(() => {
    if (!muted) btn.style.opacity = '0.55';
  }, 2500);
}

export function setupMuteButton() {
  const btn = document.getElementById('muteBtn');
  if (!btn) return;
  // Sync initial muted state to audio shim
  import('../shims/audio_shim.js').then(m => {
    try { muted = m.isWebMuted(); setMutedState(btn, muted); } catch {}
    m.setWebMuted && m.setWebMuted(muted);
  }).catch(() => {});
  // Keep top mute in sync when Dpad unmutes via webMuteChanged
  window.addEventListener('webMuteChanged', (e) => {
    muted = !!e.detail;
    setMutedState(btn, muted);
    scheduleFade(btn);
  });

  btn.addEventListener('click', () => {
    setMutedState(btn, !muted);
    dispatchMuteKey();
    scheduleFade(btn);
  });

  btn.addEventListener('touchstart', (e) => {
    e.preventDefault();
    setMutedState(btn, !muted);
    dispatchMuteKey();
    scheduleFade(btn);
  }, { passive: false });

  // Opacity bump on any interaction with canvas
  const frame = document.querySelector('.console-frame');
  if (frame) {
    ['touchstart', 'mousemove'].forEach(ev => {
      frame.addEventListener(ev, () => scheduleFade(btn), { passive: true });
    });
  }
}

export function showMuteButton() {
  const btn = document.getElementById('muteBtn');
  if (!btn) return;
  btn.classList.add('visible');
  scheduleFade(btn);
}
