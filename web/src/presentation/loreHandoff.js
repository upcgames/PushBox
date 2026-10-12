// Scene metadata is captured from the original Lore(nivel) argument by the
// web runtime observer. No text parsing or guessed progression.
export function loreLevel(state) {
  const level = state.screen?.level;
  return state.screen?.id === 'Lore' && Number.isInteger(level) && level >= 1 && level <= 5 ? level : null;
}
export function loreConfirmation(state) {
  const request = state.inputRequest;
  return state.screen?.id === 'Lore' && request?.consumer === 'Lore'
    && request.kind === 'confirmation' ? request : null;
}
