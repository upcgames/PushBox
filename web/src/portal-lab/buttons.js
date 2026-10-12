// One preview markup/style for scene and control-area confirmation buttons.
export function continueButton({ className = '', label = 'Continue', disabled = false, hidden = false, action = '' } = {}) {
  return `<button class="pixel-button continue-button ${className}" type="button"${disabled ? ' disabled' : ''}${hidden ? ' hidden' : ''}${action ? ` data-action="${action}"` : ''}>${label}</button>`;
}
