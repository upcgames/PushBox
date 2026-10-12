import { continueButton } from './buttons.js';
const arrow = '<svg viewBox="0 0 24 24" aria-hidden="true"><path d="M10 3h4v3h3v3h3v3H4V9h3V6h3V3ZM9 12h6v9H9Z"/></svg>';

export function mountControlStudies(root) {
  // Reuse the chosen icons, including their established hinted/active styling.
  const undo = document.querySelector('#agreed-panel .candidate.rewind-cue:not(.hinted):not(.activated)').outerHTML;
  const troll = document.querySelector('#agreed-panel .candidate.face:not(.hinted):not(.activated)').outerHTML;
  const direction = (name, position) => `<button class="pixel-button ${position}" aria-label="${name}" data-action="${name}">${arrow}</button>`;
  root.innerHTML = `<section class="studies controls-studies">
    <article><h2>Gameplay</h2><div class="control-study">
      <div class="control-topbar"><span>PUSHBOX</span><button class="pixel-button utility sound-control" aria-label="Mute" aria-pressed="false" data-action="Mute"><svg viewBox="0 0 24 24" aria-hidden="true"><path d="M3 9h5l6-5v16l-6-5H3V9Zm14-2h3v10h-3V7Z"/></svg></button><button class="pixel-button utility" aria-label="Pause" data-action="Pause"><span class="pause-icon" aria-hidden="true"></span></button></div>
      <div class="control-deck"><div class="sample-dpad" aria-label="Movement">
        ${direction('Up', 'up')}${direction('Left', 'left')}<span class="dpad-center"></span>${direction('Right', 'right')}${direction('Down', 'down')}
      </div><div class="secondary-actions">${undo}${troll}</div></div>
      <p class="control-readout" aria-live="polite">Tap a control</p>
    </div><p>Restored 62px directions. Approved undo/troll icons; pause and mute are separate utility controls. Undo/troll presses preview their active states.</p></article>
    <article><h2>Pause / Main-menu navigation</h2><div class="control-study">
      <div class="menu-controls"><div class="sample-menu-pad" aria-label="Menu navigation">${direction('Up', 'up')}<span class="dpad-center"></span>${direction('Down', 'down')}</div><button class="pixel-button control-action" data-action="Select"><svg viewBox="0 0 24 24" aria-hidden="true"><path d="m3 12 4-4 4 4 7-7 4 4-11 11-8-8Z"/></svg><span>Seleccionar</span></button></div>
      <p class="control-readout" aria-live="polite">Tap a control</p>
    </div><p>Up/down and Select, matching the existing pause and main-menu input. This previews controls, not a replacement pause scene.</p></article>
    <article><h2>Continue</h2><div class="control-study simple-controls">${continueButton({ action: 'Continue' })}<p class="control-readout" aria-live="polite">Tap a control</p></div><p>For confirmations and scenes that still use a separate control area. Full-screen instructions keep their in-screen Continue.</p></article>
    <article><h2>Winner actions</h2><div class="control-study simple-controls"><div class="winner-actions"><button class="pixel-button control-action" data-action="Change name"><svg viewBox="0 0 24 24" aria-hidden="true"><path d="m15 3 6 6-11 11H4v-6L15 3Zm-9 12v3h3l8-8-3-3-8 8Z"/></svg><span>Cambiar nombre</span></button><button class="pixel-button control-action" data-action="Exit"><svg viewBox="0 0 24 24" aria-hidden="true"><path d="M3 3h10v3H6v12h7v3H3V3Zm12 4h3l5 5-5 5h-3l3-3H9v-4h9l-3-3Z"/></svg><span>Salir</span></button></div><p class="control-readout" aria-live="polite">Tap a control</p></div><p>Actions around the original ending: native name entry or Exit. No winner-screen redesign.</p></article>
  </section>`;
  const timers = new Set();
  root.querySelectorAll('button').forEach(button => button.addEventListener('click', () => {
    const study = button.closest('.control-study');
    let action = button.dataset.action;
    if (button.classList.contains('rewind-cue') || button.classList.contains('face')) {
      action = button.classList.contains('face') ? 'Troll sound · active preview' : 'Undo · active preview';
      button.classList.add('activated');
      const timer = setTimeout(() => { button.classList.remove('activated'); timers.delete(timer); }, 1800);
      timers.add(timer);
    }
    if (button.classList.contains('sound-control')) {
      const muted = button.getAttribute('aria-pressed') !== 'true';
      button.setAttribute('aria-pressed', String(muted)); button.setAttribute('aria-label', muted ? 'Unmute' : 'Mute');
      button.classList.toggle('muted', muted); action = muted ? 'Muted preview' : 'Unmuted preview';
    }
    study.querySelector('.control-readout').textContent = action;
  }));
  if (import.meta.hot) import.meta.hot.dispose(() => timers.forEach(timer => clearTimeout(timer)));
}
