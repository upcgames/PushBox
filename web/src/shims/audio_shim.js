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


// All wav assets in public/audio (copied via scripts/copy_resources.py)
const AUDIO_FILES = [
  'alert.wav',
  'CajayVacio.wav',
  'Coin02.wav',
  'DesaparecePortal.wav',
  'Despierta.wav',
  'DigDugCoin.wav',
  'DigDugmuerte.wav',
  'DuckHunt1.wav',
  'DuckHunt2.wav',
  'Endurecimiento.wav',
  'Gameboy.wav',
  'GameOver.wav',
  'Guason01.wav',
  'Guason02.wav',
  'HurryUp.wav',
  'intro.wav',
  'LoreMusic.wav',
  'MarioCoin.wav',
  'MarioDead.wav',
  'MarioWin.wav',
  'mov2.wav',
  'mov3.wav',
  'movf.wav',
  'muerte.wav',
  'NoPuedeRe.wav',
  'outro.wav',
  'PausaSound.wav',
  'Pixelmen.wav',
  'PuedeRe.wav',
  'Rbr.wav',
  'Sabe.wav',
  'SonicJump.wav',
  'Teletransporte.wav',
  'Terroristas.wav',
  'Thwip.wav',
  'TypeWriter1.wav',
  'TypeWriter2.wav',
  'WakaWaka.wav',
  'YouWInMetal.wav',
];

const audioCache = new Map();
let preloadPromise = null;

function getAudioPath(filename) {
  return `${import.meta.env.BASE_URL}audio/${filename}`;
}

function loadSingleAudio(filename) {
  return new Promise((resolve) => {
    try {
      const audio = new Audio();
      audio.preload = 'auto';
      audio.src = getAudioPath(filename);
      // Resolve on canplaythrough or error/timeout — never blocks forever
      let settled = false;
      const done = () => {
        if (settled) return;
        settled = true;
        clearTimeout(timer);
        audio.removeEventListener('canplaythrough', done);
        audio.removeEventListener('error', done);
        // Keep usable even on error — still cache to avoid retry churn (case-insensitive key for Win/Linux FS)
        audioCache.set(filename.toLowerCase(), audio);
        resolve();
      };
      const timer = setTimeout(done, 4000);
      audio.addEventListener('canplaythrough', done, { once: true });
      audio.addEventListener('error', done, { once: true });
      audio.load();
    } catch (e) {
      console.warn(`[Audio] loadSingleAudio failed for ${filename}:`, e);
      resolve();
    }
  });
}

export async function preloadAudio(onProgress) {
  if (preloadPromise) return preloadPromise;
  preloadPromise = (async () => {
    let loaded = 0;
    const total = AUDIO_FILES.length;
    const notify = () => {
      if (typeof onProgress === 'function') {
        try { onProgress(loaded, total); } catch (e) { console.warn('[Audio] onProgress callback failed:', e); }
      }
    };
    notify();
    // Load in parallel batches of 6 to avoid flooding network but stay fast
    const batchSize = 6;
    for (let i = 0; i < AUDIO_FILES.length; i += batchSize) {
      const batch = AUDIO_FILES.slice(i, i + batchSize);
      await Promise.all(batch.map(async (f) => {
        await loadSingleAudio(f);
        loaded++;
        notify();
      }));
    }
  })();
  return preloadPromise;
}

export function isAudioPreloaded() {
  return audioCache.size === AUDIO_FILES.length;
}

export function getAudioCacheSize() {
  return audioCache.size;
}

const channel = createAudioChannel({ api: GameState, ...runtimeState }, {
  baseUrl: import.meta.env.BASE_URL,
  createAudio(path) {
    const filename = path.split('/').pop();
    const cached = audioCache.get(filename.toLowerCase());
    if (!cached) return new Audio(path);
    const audio = cached.cloneNode();
    if (!audio.src) audio.src = cached.src;
    return audio;
  },
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
