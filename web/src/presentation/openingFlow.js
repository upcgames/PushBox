import { WARNING_COPY } from './warningCopy.js';
import { parsePlayerNames } from './playerIdentity.js';
import { availableDestinations, destinationSettings } from './seenDestinations.js';

export function createOpeningFlow({ progress, profile, audio, onEnter = () => {},
  schedule = setTimeout, cancel = clearTimeout, message = WARNING_COPY }) {
  let state = { phase: 'hidden', position: 0, percent: 0, ready: false, seen: false, name: '', message,
    destinations: availableDestinations(progress), destinationOpen: false };
  const listeners = new Set();
  let timer = null, resolveName = null, rejectName = null, disposed = false, playing = false, paused = false;
  let selectedDestination = null;
  function update(patch) { state = { ...state, ...patch }; for (const listener of listeners) listener(state); }
  function stopAudio() { if (playing) audio.stop(); playing = false; }
  function stopTyping() { cancel(timer); timer = null; stopAudio(); }
  const stopProgress = progress.subscribe(() => {
    const destinations = availableDestinations(progress);
    update({ destinations, destinationOpen: state.destinationOpen && destinations.length > 0 });
  });
  function type() {
    timer = null;
    if (disposed || paused || state.phase !== 'typing') return;
    if (!playing) { audio.play('TypeWriter1.wav', null, 9); playing = true; }
    const position = state.position + 1;
    update({ position });
    if (position >= message.length) { stopTyping(); update({ phase: 'warning' }); return; }
    const beat = message.slice(position - 3, position) === '...';
    if (beat) stopAudio();
    timer = schedule(type, beat ? 1000 : 45);
  }
  function begin() {
    if (disposed) return Promise.reject(new DOMException('Opening stopped', 'AbortError'));
    stopTyping();
    update({ phase: 'typing', position: 0, seen: progress.has('warning'), name: profile.getNames().join(' ') });
    const promise = new Promise((resolve, reject) => { resolveName = resolve; rejectName = reject; });
    type(); return promise;
  }
  return {
    getSnapshot: () => state,
    subscribe(listener) { listeners.add(listener); listener(state); return () => listeners.delete(listener); },
    setLoading(percent, ready = false) {
      stopTyping(); rejectName?.(new DOMException('Opening replayed', 'AbortError')); resolveName = rejectName = null;
      selectedDestination = null;
      update({ phase: 'loading', percent, ready, destinationOpen: false });
    },
    begin,
    hideLoading() { if (state.phase === 'loading') update({ phase: 'hidden', destinationOpen: false }); },
    openDestinations() {
      if (!disposed && state.phase === 'loading' && state.ready && state.destinations.length) update({ destinationOpen: true });
    },
    closeDestinations() { update({ destinationOpen: false }); },
    chooseDestination(id) {
      if (disposed || !state.destinationOpen || !state.ready || !destinationSettings(progress, id, false)) return false;
      selectedDestination = id; update({ destinationOpen: false }); onEnter(id); return true;
    },
    takeDestination(skipLore) {
      const selected = selectedDestination; selectedDestination = null;
      return selected ? destinationSettings(progress, selected, skipLore) : null;
    },
    continue() {
      if (state.phase === 'loading') { if (state.ready && !state.destinationOpen) { selectedDestination = null; onEnter(); } }
      else if (state.phase === 'typing' && state.seen) { stopTyping(); update({ position: message.length, phase: 'warning' }); }
      else if (state.phase === 'warning') {
        progress.mark('warning'); update({ phase: 'name' });
      }
    },
    submit(value) {
      if (state.phase !== 'name') return false;
      const names = parsePlayerNames(value);
      if (!names.length) return false;
      profile.save(names); update({ name: names.join(' '), phase: 'complete' });
      const resolve = resolveName; resolveName = rejectName = null; resolve?.(names); return true;
    },
    pause(hidden) {
      paused = hidden;
      if (hidden) stopTyping();
      else if (state.phase === 'typing') timer = schedule(type, 45);
    },
    dispose() {
      disposed = true; stopTyping();
      rejectName?.(new DOMException('Opening stopped', 'AbortError'));
      resolveName = rejectName = null; stopProgress(); selectedDestination = null; listeners.clear();
    },
  };
}
