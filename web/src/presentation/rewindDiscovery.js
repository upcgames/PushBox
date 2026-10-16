import { createSeenProgress } from '../state/seenProgress.js';

export const REWIND_UNLOCKED = 'rewind:unlocked';
export const REWIND_RECOVERED = 'rewind:recovered';

export function mountRewindDiscovery(store, { progress = createSeenProgress(), enabled = () => true } = {}) {
  let entrancePending = false;
  function refresh() {
    const hinted = enabled() && store.getSnapshot().undoHint;
    if (!progress.has(REWIND_UNLOCKED)) {
      entrancePending = false;
      if (hinted) {
        entrancePending = true;
        progress.mark(REWIND_UNLOCKED);
        return;
      }
    }
    store.setRewindDiscovery({ visible: progress.has(REWIND_UNLOCKED), entrancePending });
  }
  const stopRecovery = store.on('rewindRecovered', () => {
    if (enabled() && progress.has(REWIND_UNLOCKED)) {
      entrancePending = false;
      progress.mark(REWIND_RECOVERED);
      refresh();
    }
  });
  // Acknowledge the pending reveal when it plays (or reveals with reduced
  // motion). The saved unlock prevents entrances on later visits.
  const stopEntrance = store.on('rewindEntrancePlayed', () => {
    if (!store.getSnapshot().rewindDiscovery.entrancePending) return;
    entrancePending = false; refresh();
  });
  const stopProgress = progress.subscribe(refresh);
  const stopState = store.select(state => state.undoHint, refresh);
  return { refresh, dispose() { stopRecovery(); stopEntrance(); stopProgress(); stopState(); } };
}
