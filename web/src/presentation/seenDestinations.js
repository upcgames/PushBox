import { startPointSettings } from '../shell/startPoints.js';

export const DESTINATIONS = [
  { id: 'warning', flag: 'warning', label: 'Advertencia', point: '0' },
  { id: 'menu', flag: 'scene:MenuPrincipal', label: 'Menú', point: 'menu' },
  { id: 'instructions', flag: 'scene:InterfazInstructions', label: 'Instrucciones', point: 'instructions' },
  ...[1, 2, 3, 4, 5].map(level => ({ id: `level-${level}`, flag: `level:${level}`, label: `Nivel ${level}`, point: String(level) })),
  { id: 'congratulations', flag: 'scene:InterfazCongratulations', label: 'Felicitaciones', point: '6' },
  { id: 'game-over', flag: 'scene:InterfazGameOver', label: 'Fin del juego', point: '7' },
  { id: 'credits', flag: 'scene:InterfazCreditos', label: 'Créditos', point: '8' },
];

export function availableDestinations(progress) {
  return progress.has('level:1') ? DESTINATIONS.filter(destination => progress.has(destination.flag)) : [];
}

export function destinationSettings(progress, id, skipLore) {
  const destination = availableDestinations(progress).find(destination => destination.id === id);
  return destination ? startPointSettings(destination.point, skipLore) : null;
}

// Record original runtime visits, never guessed progression or illustration frames.
export function mountSeenDestinations(store, progress, enabled = () => true) {
  return store.subscribe(state => {
    if (!enabled()) return;
    const scene = DESTINATIONS.find(destination => destination.flag === `scene:${state.screen?.id}`);
    if (scene) progress.mark(scene.flag);
    const level = state.game?.level;
    if (state.screen?.id === 'gameplay' && state.inputRequest?.consumer === 'ControlDeMovimiento' &&
        state.inputRequest.kind === 'key' && Number.isInteger(level) && level >= 1 && level <= 5) {
      progress.mark(`level:${level}`);
    }
  });
}
