import { mount, unmount } from 'svelte';
import GameController from '../controllers/GameController.svelte';
import Continue from '../controllers/Continue.svelte';
import NoneCtrl from '../controllers/None.svelte';
import GamePaused from '../controllers/GamePaused.svelte';
import Qwerty from '../controllers/Qwerty.svelte';
import OneTwo from '../controllers/OneTwo.svelte';
import Congrats from '../controllers/Congrats.svelte';
import { SESSION_CONTEXT } from '../controllers/services.js';
import { selectControlMode } from './controlPolicy.js';

const COMPONENTS = { none: NoneCtrl, dpad: GameController, continue: Continue,
  paused: GamePaused, qwerty: Qwerty, '1v2': OneTwo, congrats: Congrats };

export function setupSessionControls(container, services, changed = () => {}) {
  let instance;
  const stop = services.store.select(selectControlMode, mode => {
    if (instance) unmount(instance);
    instance = mount(COMPONENTS[mode] || NoneCtrl, {
      target: container, context: new Map([[SESSION_CONTEXT, services]]),
    });
    requestAnimationFrame(changed);
  });
  return () => { stop(); if (instance) unmount(instance); };
}
