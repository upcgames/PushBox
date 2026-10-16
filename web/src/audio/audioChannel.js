import { setAudioMuted } from './audioState.js';

const TROLL_FILES = ['Sabe.mp3', 'Terroristas.mp3', 'Despierta.mp3', 'Rbr.mp3'];

// Canonical playback plus a companion carita channel, owned by each session.
export function createAudioChannel(store, { baseUrl = '/', initialMuted = store.api.getSnapshot().audio.muted,
  createAudio = path => new Audio(path), random = Math.random, onMutedChange = () => {} } = {}) {
  let current = null, lastTroll = null, removePlaybackListeners = () => {};
  let troll = null;
  const publishPlayback = playback => store.publish({ audio: { ...store.api.getSnapshot().audio, playback } }, 'audioPlaybackChanged');
  setAudioMuted(store, initialMuted);
  const isWebMuted = () => store.api.getSnapshot().audio.muted;
  const unsubscribe = store.api.select(state => state.audio.muted, muted => {
    if (current) current.volume = muted ? 0 : 1;
    if (troll) troll.volume = muted ? 0 : 1;
    onMutedChange(muted);
  });
  function stopPlayback() {
    const previous = current;
    removePlaybackListeners(); removePlaybackListeners = () => {};
    current = null;
    if (previous) previous.pause();
    if (store.api.getSnapshot().audio.playback) publishPlayback(null);
  }
  function stop() {
    stopPlayback();
    troll?.pause(); troll = null;
  }
  function playTrollTrack(file, flags) {
    troll?.pause(); troll = null;
    try {
      troll = createAudio(`${baseUrl}audio/${file}`);
      troll.currentTime = 0; troll.loop = !!(flags & 8);
      troll.volume = isWebMuted() ? 0 : 1;
      troll.play()?.catch(error => console.warn(`[Audio] play() rejected for ${file}:`, error));
      return troll;
    } catch (error) { troll?.pause(); troll = null; console.warn(`[Audio] Playback failed for ${file}:`, error); }
  }
  function play(filename, reserved, flags = 0) {
    if (!filename) { stop(); return; }
    const file = String(filename).split(/[\\/]/).pop();
    if (!file) return;
    // Includes original desktop SonidoTroll calls as well as the mobile button.
    if (TROLL_FILES.includes(file)) return playTrollTrack(file, flags);
    stopPlayback();
    try {
      current = createAudio(`${baseUrl}audio/${file}`);
      const track = current;
      const settle = status => { if (current === track) publishPlayback({ file, status }); };
      const ended = () => settle('ended'), failed = () => settle('failed'), paused = () => settle('interrupted');
      track.addEventListener?.('ended', ended);
      track.addEventListener?.('error', failed);
      track.addEventListener?.('pause', paused);
      removePlaybackListeners = () => {
        track.removeEventListener?.('ended', ended);
        track.removeEventListener?.('error', failed);
        track.removeEventListener?.('pause', paused);
      };
      publishPlayback({ file, status: 'playing' });
      current.currentTime = 0; current.loop = !!(flags & 8);
      current.volume = isWebMuted() ? 0 : 1;
      current.play()?.catch(error => { settle('failed'); console.warn(`[Audio] play() rejected for ${file}:`, error); });
      return current;
    } catch (error) { stopPlayback(); console.warn(`[Audio] Playback failed for ${file}:`, error); }
  }
  function playTrollSound() {
    if (troll && !troll.paused && !troll.ended) {
      troll.currentTime = 0; return troll;
    }
    const candidates = TROLL_FILES.filter(file => file !== lastTroll);
    lastTroll = candidates[Math.floor(random() * candidates.length)];
    return play(lastTroll, null, 1);
  }
  return { play, stop, playTrollSound, isWebMuted, getCurrentAudio: () => current,
    setWebMuted: value => setAudioMuted(store, value),
    dispose() { unsubscribe(); stop(); } };
}
