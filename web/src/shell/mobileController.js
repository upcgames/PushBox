import { mountTrollReward } from '../presentation/trollReward.js';
import { mountExitCue } from '../presentation/mountExitCue.js';
import { mountBobby } from '../presentation/mountBobby.js';
import { gameConsole } from '../shims/gameConsole.js';
import { mountMobileLore } from '../presentation/mountMobileLore.js';
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
import { mountMobileInstructions } from '../presentation/mountMobileInstructions.js';
import { mountGameplayHud } from '../presentation/mountGameplayHud.js';
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


export function setupMobileShell({ progress } = {}) {
  const controllerArea = document.getElementById('controllerArea');
  if (!controllerArea) return;

  syncShellAttrs();
  const trollReward = mountTrollReward(GameState, { enabled: isMobile, progress });
  mobileMQ.addEventListener('change', trollReward.refresh);
  const exitCue = mountExitCue(gameConsole, GameState, isMobile);
  mobileMQ.addEventListener('change', exitCue.refresh);
  const bobby = mountBobby(gameConsole, GameState, isMobile);
  mobileMQ.addEventListener('change', bobby.refresh);
  const stopHud = mountGameplayHud(document.body, GameState);
  const instructions = mountMobileInstructions(document.body, GameState, GameState.sendInput, isMobile);
  const loreView = mountMobileLore(document.body, GameState, GameState.sendInput, isMobile);
  mobileMQ.addEventListener('change', loreView.refresh);
  mobileMQ.addEventListener('change', instructions.refresh);
  const boardView = setupMobileBoardView(document.body, GameState, isMobile);
  mobileMQ.addEventListener('change', boardView.refresh);
  if (import.meta.hot) import.meta.hot.dispose(() => {
    mobileMQ.removeEventListener('change', trollReward.refresh);
    trollReward.dispose();
    mobileMQ.removeEventListener('change', exitCue.refresh);
    exitCue.dispose();
    mobileMQ.removeEventListener('change', bobby.refresh);
    bobby.dispose();
    mobileMQ.removeEventListener('change', boardView.refresh);
    boardView.dispose();
    stopHud();
    mobileMQ.removeEventListener('change', instructions.refresh);
    instructions.dispose();
    mobileMQ.removeEventListener('change', loreView.refresh);
    loreView.dispose();
  });
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

  GameState.select(selectControlMode, applyMode);

  mobileMQ.addEventListener('change', () => {
    if (lastMode) applyMode(lastMode);
  });
}
