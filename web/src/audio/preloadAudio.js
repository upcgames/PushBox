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

const loads = new Map(), cache = new Map();
export function createPreloadedAudio(path) {
  const cached = cache.get(path);
  return cached ? cached.cloneNode() : new Audio(path);
}
export function preloadAudioAssets(baseUrl = '/', onProgress = () => {}) {
  let load = loads.get(baseUrl);
  if (!load) {
    load = { loaded: 0, listeners: new Set(), promise: null }; loads.set(baseUrl, load);
    load.promise = (async () => {
      for (let i = 0; i < AUDIO_FILES.length; i += 6) {
        await Promise.all(AUDIO_FILES.slice(i, i + 6).map(file => new Promise(resolve => {
          const path = `${baseUrl}audio/${file}`;
          let audio, timer, settled = false;
          function done() {
            if (settled) return; settled = true; clearTimeout(timer);
            audio?.removeEventListener('canplaythrough', done); audio?.removeEventListener('error', done);
            if (audio) cache.set(path, audio);
            load.loaded++; for (const listener of load.listeners) { try { listener(load.loaded, AUDIO_FILES.length); } catch (error) { console.warn('[Audio] loading progress failed:', error); } }
            resolve();
          }
          try {
            audio = new Audio(); audio.preload = 'auto';
            audio.addEventListener('canplaythrough', done, { once: true }); audio.addEventListener('error', done, { once: true });
            timer = setTimeout(done, 4000); audio.src = path; audio.load();
          } catch { done(); }
        })));
      }
    })();
  }
  load.listeners.add(onProgress); onProgress(load.loaded, AUDIO_FILES.length);
  return load.promise.finally(() => load.listeners.delete(onProgress));
}
export const isAudioPreloaded = (baseUrl = '/') => loads.get(baseUrl)?.loaded === AUDIO_FILES.length;
export const getAudioCacheSize = (baseUrl = '/') => loads.get(baseUrl)?.loaded || 0;
