import { continueButton } from './buttons.js';
import { mount, unmount } from 'svelte';
import GameplayControlsPreview from './GameplayControlsPreview.svelte';
import WinnerControls from '../presentation/WinnerControls.svelte';
import MenuControls from '../presentation/MenuControls.svelte';
import { mountSharedPreviews } from './sharedPreviews.js';

export function mountControlStudies(root) {
  root.innerHTML = `<section class="studies controls-studies">
    <article><h2>Gameplay · Reserved button spaces</h2><div class="gameplay-controls-preview"></div><p>Toggle rewind and carita independently. Empty slots keep the D-pad, button positions, and deck height fixed. Uses the same deck as gameplay; presses preview active states only.</p></article>
    <article><h2>Pause / Main-menu navigation</h2><div class="control-study">
      <div class="runtime-menu-controls"></div>
      <p class="control-readout" aria-live="polite">Tap a control</p>
    </div><p>Up/down and Select, matching the existing pause and main-menu input. This previews controls, not a replacement pause scene.</p></article>
    <article><h2>Continue</h2><div class="control-study simple-controls">${continueButton({ action: 'Continue' })}<p class="control-readout" aria-live="polite">Tap a control</p></div><p>For confirmations and scenes that still use a separate control area. Full-screen instructions keep their in-screen Continue.</p></article>
    <article><h2>Winner actions</h2><div class="control-study simple-controls"><div class="runtime-winner-controls"></div><p class="control-readout" aria-live="polite">Tap a control</p></div><p>Actions around the original ending: native name entry or Exit. No winner-screen redesign.</p></article>
  </section>`;
  const readout = (host, action) => {
    host.closest('.control-study').querySelector('.control-readout').textContent = action;
  };
  const stopButtons = mountSharedPreviews(root, readout);
  const winnerHost = root.querySelector('.runtime-winner-controls');
  const winner = mount(WinnerControls, { target: winnerHost, props: { onInput: key => readout(winnerHost, key === 'k' ? 'Change name' : 'Exit') } });
  const gameplay = mount(GameplayControlsPreview, { target: root.querySelector('.gameplay-controls-preview') });
  const menuHost = root.querySelector('.runtime-menu-controls');
  const menu = mount(MenuControls, { target: menuHost, props: {
    onInput: key => readout(menuHost, { w: 'Up', s: 'Down', e: 'Select' }[key]),
  } });
  root.querySelectorAll('button[data-action]').forEach(button => button.addEventListener('click', () => {
    readout(button, button.dataset.action);
  }));
  return () => { stopButtons(); unmount(gameplay); unmount(menu); unmount(winner); };
}
