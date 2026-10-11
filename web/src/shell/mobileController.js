import { mount, unmount } from 'svelte';
import GameController from '../controllers/GameController.svelte';
import Continue from '../controllers/Continue.svelte';
import NoneCtrl from '../controllers/None.svelte';
import GamePaused from '../controllers/GamePaused.svelte';
import Qwerty from '../controllers/Qwerty.svelte';
import OneTwo from '../controllers/OneTwo.svelte';
import Congrats from '../controllers/Congrats.svelte';
import { GameState } from '../state/gameState.js';
import { selectControlMode } from './controlPolicy.js';
import { setupMobileBoardView } from '../presentation/mobileBoardView.js';

const COMPONENTS = {
  none: NoneCtrl,
  dpad: GameController,
  continue: Continue,
  paused: GamePaused,
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
    unmount(currentInstance);
    currentInstance = null;
  }
  const Comp = COMPONENTS[mode];
  if (!Comp) return;
  currentInstance = mount(Comp, { target: container });
}


function measureTitleSpace() {
  if (!isMobile()) {
    document.documentElement.removeAttribute('data-title');
    return;
  }
  const frame = document.querySelector('.console-frame');
  const ctrl = document.getElementById('controllerArea');
  const vh = window.visualViewport ? window.visualViewport.height : window.innerHeight;
  const gameH = frame ? frame.getBoundingClientRect().height : 0;
  const ctrlH = ctrl && ctrl.style.display !== 'none' ? ctrl.getBoundingClientRect().height : 0;
  const available = vh - gameH - ctrlH;
  document.documentElement.dataset.title = available > 80 ? 'show' : 'hide';
}

export function setupMobileShell() {
  const controllerArea = document.getElementById('controllerArea');
  if (!controllerArea) return;

  syncShellAttrs();
  const boardView = setupMobileBoardView(document.body, GameState, isMobile);
  mobileMQ.addEventListener('change', boardView.refresh);
  if (import.meta.hot) import.meta.hot.dispose(() => {
    mobileMQ.removeEventListener('change', boardView.refresh);
    boardView.dispose();
  });
  measureTitleSpace();
  mobileMQ.addEventListener('change', syncShellAttrs);
  mobileMQ.addEventListener('change', measureTitleSpace);
  landscapeMQ.addEventListener('change', syncShellAttrs);
  landscapeMQ.addEventListener('change', measureTitleSpace);
  window.addEventListener('resize', measureTitleSpace);
  if (window.visualViewport) window.visualViewport.addEventListener('resize', measureTitleSpace);
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
    requestAnimationFrame(measureTitleSpace);
  };

  GameState.select(selectControlMode, applyMode);

  mobileMQ.addEventListener('change', () => {
    if (lastMode) applyMode(lastMode);
  });
}
