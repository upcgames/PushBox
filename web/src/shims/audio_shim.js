import { GameState, runtimeState } from '../state/gameState.js';

// Win32 Multimedia API Shims (1-Channel Audio Architecture)
window.TEXT = (str) => str;
window.SND_SYNC = 0;
window.SND_ASYNC = 1;
window.SND_NODEFAULT = 2;
window.SND_MEMORY = 4;
window.SND_LOOP = 8;
window.SND_NOSTOP = 16;

let currentAudio = null;
let webMuted = false;

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

export function setWebMuted(v) {
  webMuted = !!v;
  if (GameState.getSnapshot().audio.muted !== webMuted) {
    runtimeState.publish({ audio: { muted: webMuted } }, 'audioChanged');
  }
  if (currentAudio) {
    try { currentAudio.volume = webMuted ? 0 : 1; } catch {}
    // Keep loop playing at volume 0 so unmute resumes seamlessly (no restart)
  }
  try { window.dispatchEvent(new window.CustomEvent('webMuteChanged', { detail: webMuted })); } catch {}
}
export function isWebMuted() { return webMuted; }
export function getCurrentAudio() { return currentAudio; }

let lastTrollMode = null;
const TROLL_MAP = { 1: 'Sabe.wav', 2: 'Terroristas.wav', 3: 'Despierta.wav', 4: 'Rbr.wav' };
const TROLL_FILES = new Set(Object.values(TROLL_MAP));

function isTrollPlaying() {
  if (!currentAudio) return false;
  try {
    if (currentAudio.paused || currentAudio.ended) return false;
    const file = currentAudio.src.split('/').pop();
    return TROLL_FILES.has(file);
  } catch { return false; }
}

export function playTrollSound() {
  // If a troll sound is already playing, stutter restart same
  if (isTrollPlaying()) {
    try { currentAudio.currentTime = 0; } catch {}
    return;
  }
  // Otherwise pick random among remaining 3 (or 4 if first)
  let candidates = [1,2,3,4];
  if (lastTrollMode !== null) candidates = candidates.filter(m => m !== lastTrollMode);
  const mode = candidates[Math.floor(Math.random() * candidates.length)];
  lastTrollMode = mode;
  PlaySound(TROLL_MAP[mode], null, window.SND_ASYNC);
}

export function PlaySound(soundFile, reserved, flags) {
  // Stop any currently playing 1-channel audio track immediately
  if (currentAudio) {
    try { currentAudio.pause(); } catch (e) { console.warn('[Audio] pause failed:', e); }
    currentAudio = null;
  }

  // PlaySound(null) or null filename stops audio playback
  if (!soundFile) return;

  try {
    const filename = (typeof soundFile === 'string') ? soundFile.split('/').pop() : '';
    if (!filename) return;

    let audio = null;
    const cached = audioCache.get(filename.toLowerCase());
    if (cached) {
      // Clone cached element so SND_LOOP flag can be set per-play without mutating cache
      audio = cached.cloneNode();
      // cloneNode loses src in some browsers if not set explicitly
      if (!audio.src) audio.src = cached.src;
      audio.currentTime = 0;
    } else {
      audio = new Audio(getAudioPath(filename));
    }
    
    if ((flags & window.SND_LOOP) !== 0) {
      audio.loop = true;
    }
    try { audio.volume = webMuted ? 0 : 1; } catch {}

    currentAudio = audio;
    const playPromise = audio.play();
    if (playPromise && typeof playPromise.catch === 'function') {
      playPromise.catch((err) => {
        console.warn(`[Audio] PlaySound play() rejected for ${filename}:`, err);
      });
    }
  } catch (err) {
    console.warn(`[Audio] Audio playback warning for ${soundFile}:`, err);
  }
}

export function StopSound() {
  if (currentAudio) {
    try { currentAudio.pause(); } catch (e) { console.warn('[Audio] pause failed:', e); }
    currentAudio = null;
  }
}

window.PlaySound = PlaySound;
window.StopSound = StopSound;
window.preloadAudio = preloadAudio;
