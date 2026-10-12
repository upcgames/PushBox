export function instructionConfirmation(state) {
  const request = state.inputRequest;
  return state.screen?.id === 'InterfazInstructions'
    && request?.consumer === 'InterfazInstructions'
    && request.kind === 'confirmation' ? request : null;
}
