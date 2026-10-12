import { setAudioMuted } from './audioState.js';

const TROLL_FILES = ['Sabe.wav', 'Terroristas.wav', 'Despierta.wav', 'Rbr.wav'];

// One channel per game/session; all channels use the same implementation.
export function createAudioChannel(store, { baseUrl = '/', initialMuted = store.api.getSnapshot().audio.muted,
  createAudio = path => new Audio(path), random = Math.random, onMutedChange = () => {} } = {}) {
  let current = null, currentFile = null, lastTroll = null;
  setAudioMuted(store, initialMuted);
  const isWebMuted = () => store.api.getSnapshot().audio.muted;
  const unsubscribe = store.api.select(state => state.audio.muted, muted => {
    if (current) current.volume = muted ? 0 : 1;
    onMutedChange(muted);
  });
  function stop() {
    const previous = current;
    current = null; currentFile = null;
    if (previous) previous.pause();
  }
  function play(filename, reserved, flags = 0) {
    stop();
    if (!filename) return;
    const file = String(filename).split(/[\\/]/).pop();
    if (!file) return;
    try {
      current = createAudio(`${baseUrl}audio/${file}`);
      currentFile = file;
      current.currentTime = 0; current.loop = !!(flags & 8);
      current.volume = isWebMuted() ? 0 : 1;
      current.play()?.catch(error => console.warn(`[Audio] play() rejected for ${file}:`, error));
      return current;
    } catch (error) { console.warn(`[Audio] Playback failed for ${file}:`, error); }
  }
  function playTrollSound() {
    if (current && !current.paused && !current.ended && TROLL_FILES.includes(currentFile)) {
      current.currentTime = 0; return current;
    }
    const candidates = TROLL_FILES.filter(file => file !== lastTroll);
    lastTroll = candidates[Math.floor(random() * candidates.length)];
    return play(lastTroll, null, 1);
  }
  return { play, stop, playTrollSound, isWebMuted, getCurrentAudio: () => current,
    setWebMuted: value => setAudioMuted(store, value),
    dispose() { unsubscribe(); stop(); } };
}
