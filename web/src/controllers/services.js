import { getContext } from 'svelte';
import { GameState, sendInput } from '../state/gameState.js';

export const SESSION_CONTEXT = 'pushbox-session';
// Keep the original page's defaults, without importing its global audio shim
// when controllers are mounted for an independent session.
const legacyAudio = {
  setWebMuted: value => import('../shims/audio_shim.js').then(audio => audio.setWebMuted(value)),
  playTrollSound: () => import('../shims/audio_shim.js').then(audio => audio.playTrollSound()),
  getCurrentAudio: () => import('../shims/audio_shim.js').then(audio => audio.getCurrentAudio()),
};
export function controllerServices() {
  return getContext(SESSION_CONTEXT) || { store: GameState, sendInput, audio: legacyAudio };
}
