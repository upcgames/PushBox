// Animation readiness is the original confirmation request, never a timer.
// This gate is mounted only by mobile presentation (including Inspector).
export function mountWinnerContinue(store, { enabled = () => true } = {}) {
  let failed = false;
  function refresh() {
    const state = store.getSnapshot(), request = state.inputRequest;
    if (state.screen?.id !== 'InterfazCongratulations') failed = false;
    const winner = !failed && enabled() && state.screen?.id === 'InterfazCongratulations';
    const musicPlaying = !state.audio.muted && state.audio.playback?.file === 'YouWinMetal.wav' &&
      state.audio.playback.status === 'playing';
    store.setWinnerContinueBlocked(winner && (!request ||
      (request.consumer === 'InterfazCongratulations' && request.kind === 'confirmation' && musicPlaying)));
  }
  const stop = store.subscribe(refresh);
  const stopError = store.on('runtimeError', () => { failed = true; refresh(); });
  return { refresh, dispose() { stop(); stopError(); store.setWinnerContinueBlocked(false); } };
}
