import { mount } from 'svelte';
import Dpad from '../controllers/Dpad.svelte';
import Continue from '../controllers/Continue.svelte';
import NoneCtrl from '../controllers/None.svelte';
import Paused from '../controllers/Paused.svelte';
import Qwerty from '../controllers/Qwerty.svelte';
import OneTwo from '../controllers/OneTwo.svelte';

const COMPONENTS = {
  none: NoneCtrl,
  dpad: Dpad,
  continue: Continue,
  paused: Paused,
  qwerty: Qwerty,
  '1v2': OneTwo,
};

let currentInstance = null;

export function isMobile() {
  return window.matchMedia('(max-width: 768px)').matches;
}

export function mountController(container, mode) {
  if (currentInstance) {
    try { currentInstance.$destroy?.(); } catch {}
    // Svelte 5 mount returns object with unmount, fallback to innerHTML clear
    container.innerHTML = '';
    currentInstance = null;
  }
  const Comp = COMPONENTS[mode];
  if (!Comp) return;
  // Svelte 5: mount(Component, {target})
  try {
    currentInstance = mount(Comp, { target: container });
  } catch {
    // fallback for Svelte 4 style
    currentInstance = new Comp({ target: container });
  }
}

export function setupMobileShell() {
  const controllerArea = document.getElementById('controllerArea');
  if (!controllerArea) return;

  let lastMode = null;
  const applyMode = (mode) => {
    if (!mode) return;
    lastMode = mode;
    if (!isMobile()) {
      controllerArea.style.display = 'none';
      return;
    }
    controllerArea.style.display = 'block';
    mountController(controllerArea, mode);
  };

  import('../shims/gameState.js').then(({ on }) => {
    on('inputMode', applyMode);
  }).catch(() => {});

  window.matchMedia('(max-width: 768px)').addEventListener('change', () => {
    if (lastMode) applyMode(lastMode);
  });
}
