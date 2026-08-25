import { mount } from 'svelte';
import Dpad from '../controllers/Dpad.svelte';
import Continue from '../controllers/Continue.svelte';
import NoneCtrl from '../controllers/None.svelte';
import Paused from '../controllers/Paused.svelte';
import Qwerty from '../controllers/Qwerty.svelte';
import OneTwo from '../controllers/OneTwo.svelte';
import Congrats from '../controllers/Congrats.svelte';

const COMPONENTS = {
  none: NoneCtrl,
  dpad: Dpad,
  continue: Continue,
  paused: Paused,
  qwerty: Qwerty,
  '1v2': OneTwo,
  congrats: Congrats,
};

let currentInstance = null;

const mobileMQ = window.matchMedia('(pointer: coarse)');
const landscapeMQ = window.matchMedia('(orientation: landscape)');

function syncShellAttrs() {
  document.documentElement.dataset.shell = mobileMQ.matches ? 'mobile' : 'desktop';
  document.documentElement.dataset.orientation = landscapeMQ.matches ? 'landscape' : 'portrait';
}

export function isMobile() {
  return mobileMQ.matches;
}

export function mountController(container, mode) {
  if (currentInstance) {
    try { currentInstance.$destroy?.(); } catch {}
    container.innerHTML = '';
    currentInstance = null;
  }
  const Comp = COMPONENTS[mode];
  if (!Comp) return;
  try {
    currentInstance = mount(Comp, { target: container });
  } catch {
    currentInstance = new Comp({ target: container });
  }
}

export function setupMobileShell() {
  const controllerArea = document.getElementById('controllerArea');
  if (!controllerArea) return;

  syncShellAttrs();
  mobileMQ.addEventListener('change', syncShellAttrs);
  landscapeMQ.addEventListener('change', syncShellAttrs);

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

  mobileMQ.addEventListener('change', () => {
    if (lastMode) applyMode(lastMode);
  });
}
