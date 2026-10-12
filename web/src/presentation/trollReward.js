import { createSeenProgress } from '../state/seenProgress.js';

export function canEarnTroll({ game, screen, inputRequest, playerAnimation }) {
  return screen?.id === 'gameplay' && inputRequest?.consumer === 'ControlDeMovimiento' &&
    game?.level === 4 && game.nextLevel === 4 && !playerAnimation &&
    game.board.boxes.filter(box => box.onTarget).length >= 3;
}

// Read canonical placement facts. Seeing the illustration in lore is not earning
// the gameplay button; mark it seen only when mobile gameplay can reveal it.
export function mountTrollReward(store, { progress = createSeenProgress(), enabled = () => true } = {}) {
  function sync() {
    store.setTrollReward({ unlocked: progress.has('carita'),
      hinted: progress.has('carita') && !progress.has('caritaUsed') });
  }
  function refresh() {
    if (enabled() && canEarnTroll(store.getSnapshot())) progress.mark('carita');
    sync();
  }
  const stopProgress = progress.subscribe(sync);
  const stopUsed = store.on('trollRewardUsed', () => progress.mark('caritaUsed'));
  const stopState = store.select(state => enabled() && canEarnTroll(state), refresh);
  return { refresh, dispose() { stopState(); stopUsed(); stopProgress(); } };
}
