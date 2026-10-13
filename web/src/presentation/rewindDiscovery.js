import { createSeenProgress } from '../state/seenProgress.js';

export const REWIND_RECOVERED = 'rewind:recovered';
// Shared by mounts using the same progression owner for this page visit.
// Pause, new playthroughs, and Inspector runtime resets do not erase it.
const visits = new WeakMap();

export function mountRewindDiscovery(store, { progress = createSeenProgress(), enabled = () => true } = {}) {
  let visit = visits.get(progress);
  if (!visit) { visit = { entrancePlayed: false }; visits.set(progress, visit); }
  function refresh() {
    const learned = progress.has(REWIND_RECOVERED);
    const hinted = enabled() && store.getSnapshot().undoHint;
    store.setRewindDiscovery({ visible: learned || hinted,
      entrancePending: !learned && hinted && !visit.entrancePlayed });
  }
  const stopRecovery = store.on('rewindRecovered', () => {
    if (enabled()) progress.mark(REWIND_RECOVERED);
  });
  // The entrance acknowledges this when it actually plays (or reveals with reduced motion),
  // rather than consuming the opportunity on a hint or component mount alone.
  const stopEntrance = store.on('rewindEntrancePlayed', () => {
    if (!store.getSnapshot().rewindDiscovery.entrancePending) return;
    visit.entrancePlayed = true; refresh();
  });
  const stopProgress = progress.subscribe(refresh);
  const stopState = store.select(state => state.undoHint, refresh);
  return { refresh, dispose() { stopRecovery(); stopEntrance(); stopProgress(); stopState(); } };
}
