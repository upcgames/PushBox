import { preloadAudioAssets, createPreloadedAudio, isAudioPreloaded as assetsPreloaded, getAudioCacheSize as audioCacheSize } from '../audio/preloadAudio.js';
import { GameState, runtimeState } from '../state/gameState.js';
import { createAudioChannel } from '../audio/audioChannel.js';

// Win32 Multimedia API Shims (1-Channel Audio Architecture)
window.TEXT = (str) => str;
window.SND_SYNC = 0;
window.SND_ASYNC = 1;
window.SND_NODEFAULT = 2;
window.SND_MEMORY = 4;
window.SND_LOOP = 8;
window.SND_NOSTOP = 16;


export const preloadAudio = onProgress => preloadAudioAssets(import.meta.env.BASE_URL, onProgress);
export const isAudioPreloaded = () => assetsPreloaded(import.meta.env.BASE_URL);
export const getAudioCacheSize = () => audioCacheSize(import.meta.env.BASE_URL);

const channel = createAudioChannel({ api: GameState, ...runtimeState }, {
  baseUrl: import.meta.env.BASE_URL,
  createAudio: createPreloadedAudio,
  onMutedChange(muted) {
    window.dispatchEvent(new window.CustomEvent('webMuteChanged', { detail: muted }));
  },
});
export const setWebMuted = channel.setWebMuted;
export const isWebMuted = channel.isWebMuted;
export const getCurrentAudio = channel.getCurrentAudio;
export const playTrollSound = channel.playTrollSound;
export const PlaySound = channel.play;
export const StopSound = channel.stop;
if (import.meta.hot) import.meta.hot.dispose(() => channel.dispose());

window.PlaySound = PlaySound;
window.StopSound = StopSound;
window.preloadAudio = preloadAudio;
