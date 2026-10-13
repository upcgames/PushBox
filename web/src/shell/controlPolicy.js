// Presentation policy, not canonical game state. Runtime reports input demands;
// this web view chooses which existing control component meets each demand.
const KEY_CONTROLS = {
  ControlDeMovimiento: 'dpad',
  MenuPrincipal: 'paused',
  InterfazPausa: 'paused',
  InterfazCongratulations: 'congrats',
  main: 'continue',
};

export function selectControlMode({ inputRequest, winnerActionsBlocked }) {
  if (!inputRequest) return 'none';
  if (inputRequest.native) return 'none';
  if (winnerActionsBlocked && inputRequest.consumer === 'InterfazCongratulations' && inputRequest.kind === 'key') return 'none';
  if (inputRequest.kind === 'confirmation') return 'continue';
  if (inputRequest.kind === 'text') {
    return inputRequest.choices?.join(',') === '1,2' ? '1v2' : 'qwerty';
  }
  return KEY_CONTROLS[inputRequest.consumer] || 'none';
}
