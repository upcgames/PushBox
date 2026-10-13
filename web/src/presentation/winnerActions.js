import { CONGRATULATIONS_MUSIC } from '../generated/audioAssets.js';

// Actions become available at the original K/E input loop after the celebration.
// This gate is mounted only by mobile presentation (including Inspector).
export function mountWinnerActions(store, { enabled = () => true } = {}) {
  let failed = false;
  function refresh() {
    const state = store.getSnapshot(), request = state.inputRequest;
    if (state.screen?.id !== 'InterfazCongratulations') failed = false;
    const winner = !failed && enabled() && state.screen?.id === 'InterfazCongratulations';
    const musicPlaying = !state.audio.muted && state.audio.playback?.file === CONGRATULATIONS_MUSIC &&
      state.audio.playback.status === 'playing';
    store.setWinnerActionsBlocked(winner && (!request ||
      (request.consumer === 'InterfazCongratulations' && request.kind === 'key' && musicPlaying)));
  }
  const stop = store.subscribe(refresh);
  const stopError = store.on('runtimeError', () => { failed = true; refresh(); });
  return { refresh, dispose() { stop(); stopError(); store.setWinnerActionsBlocked(false); } };
}
