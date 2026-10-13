import { createPreloadedAudio } from '../audio/preloadAudio.js';

// A session-local companion to the canonical channel: typing and its pauses
// cannot interrupt the alarm or replace the canonical playback observation.
export function mountWarningAlarm(flow, store, { baseUrl = '/', enabled = () => true,
  hidden = () => document.hidden, visibilityTarget = document, createAudio = createPreloadedAudio } = {}) {
  let track = null, playing = false;
  const stopMute = store.select(state => state.audio.muted, muted => {
    if (track) track.volume = muted ? 0 : 1;
  });
  function refresh() {
    const phase = flow.getSnapshot().phase;
    const visible = enabled() && !hidden() && (phase === 'typing' || phase === 'warning');
    if (visible === playing) return;
    playing = visible;
    if (visible) {
      try {
        track ||= createAudio(`${baseUrl}audio/alert.mp3`);
        track.loop = true; track.currentTime = 0;
        track.volume = store.getSnapshot().audio.muted ? 0 : 1;
        track.play()?.catch(error => console.warn('[Warning alarm] Playback rejected:', error));
      } catch (error) { console.warn('[Warning alarm] Playback failed:', error); }
    } else track?.pause();
  }
  const stop = flow.subscribe(refresh);
  visibilityTarget.addEventListener('visibilitychange', refresh);
  return { refresh, dispose() {
    stop(); stopMute(); visibilityTarget.removeEventListener('visibilitychange', refresh);
    track?.pause(); track = null; playing = false;
  } };
}
