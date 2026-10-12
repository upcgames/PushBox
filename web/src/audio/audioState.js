// The shared store is the only mute state. Gameplay's sound flag is an adapter.
export function setAudioMuted(store, value) {
  const muted = !!value, state = store.api.getSnapshot();
  if (state.audio.muted === muted && (!state.game || state.game.sound === !muted)) return;
  store.publish({ audio: { ...state.audio, muted },
    ...(state.game ? { game: { ...state.game, sound: !muted } } : {}) }, 'audioChanged');
}

export function bindSoundReference(store, reference) {
  Object.defineProperty(reference, 'v', { configurable: true,
    get: () => !store.api.getSnapshot().audio.muted,
    set: enabled => { setAudioMuted(store, !enabled); } });
}

export function handleAudioInput(store, key) {
  if (typeof key !== 'string' || key.toLowerCase() !== 'f' || store.api.getSnapshot().inputRequest?.kind === 'text') return false;
  setAudioMuted(store, !store.api.getSnapshot().audio.muted);
  return true;
}
