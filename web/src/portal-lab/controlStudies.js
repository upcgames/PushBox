import { continueButton } from './buttons.js';
import { mount, unmount } from 'svelte';
import Dpad from '../components/Dpad.svelte';
import MenuControls from '../presentation/MenuControls.svelte';
import { mountSharedPreviews } from './sharedPreviews.js';

export function mountControlStudies(root) {
  const undo = '<span data-pixel-icon="undo" data-variant="rewind-cue" data-label="Undo · active preview"></span>';
  const troll = '<span data-pixel-icon="troll" data-variant="face" data-label="Troll sound · active preview"></span>';
  root.innerHTML = `<section class="studies controls-studies">
    <article><h2>Gameplay</h2><div class="control-study">
      <div class="control-topbar"><span>PUSHBOX</span><span data-pixel-icon="sound" data-variant="utility" data-label="Mute"></span><span data-pixel-icon="pause" data-variant="utility" data-label="Pause"></span></div>
      <div class="control-deck"><div class="shared-dpad"></div><div class="secondary-actions">${undo}${troll}</div></div>
      <p class="control-readout" aria-live="polite">Tap a control</p>
    </div><p>Restored 62px directions. Approved undo/troll icons; pause and mute are separate utility controls. Undo/troll presses preview their active states.</p></article>
    <article><h2>Pause / Main-menu navigation</h2><div class="control-study">
      <div class="runtime-menu-controls"></div>
      <p class="control-readout" aria-live="polite">Tap a control</p>
    </div><p>Up/down and Select, matching the existing pause and main-menu input. This previews controls, not a replacement pause scene.</p></article>
    <article><h2>Continue</h2><div class="control-study simple-controls">${continueButton({ action: 'Continue' })}<p class="control-readout" aria-live="polite">Tap a control</p></div><p>For confirmations and scenes that still use a separate control area. Full-screen instructions keep their in-screen Continue.</p></article>
    <article><h2>Winner actions</h2><div class="control-study simple-controls"><div class="winner-actions"><button class="pixel-button control-action" data-action="Change name"><svg viewBox="0 0 24 24" aria-hidden="true"><path d="m15 3 6 6-11 11H4v-6L15 3Zm-9 12v3h3l8-8-3-3-8 8Z"/></svg><span>Cambiar nombre</span></button><button class="pixel-button control-action" data-action="Exit"><svg viewBox="0 0 24 24" aria-hidden="true"><path d="M3 3h10v3H6v12h7v3H3V3Zm12 4h3l5 5-5 5h-3l3-3H9v-4h9l-3-3Z"/></svg><span>Salir</span></button></div><p class="control-readout" aria-live="polite">Tap a control</p></div><p>Actions around the original ending: native name entry or Exit. No winner-screen redesign.</p></article>
  </section>`;
  const readout = (host, action) => {
    host.closest('.control-study').querySelector('.control-readout').textContent = action;
  };
  const stopButtons = mountSharedPreviews(root, readout);
  const padHost = root.querySelector('.shared-dpad');
  const menuHost = root.querySelector('.runtime-menu-controls');
  const menu = mount(MenuControls, { target: menuHost, props: {
    onInput: key => readout(menuHost, { w: 'Up', s: 'Down', e: 'Select' }[key]),
  } });
  const pad = mount(Dpad, { target: padHost, props: { facelift: true,
    onDir: key => readout(padHost, { w: 'Up', a: 'Left', s: 'Down', d: 'Right' }[key]),
  } });
  root.querySelectorAll('button[data-action]').forEach(button => button.addEventListener('click', () => {
    readout(button, button.dataset.action);
  }));
  return () => { stopButtons(); unmount(pad); unmount(menu); };
}
