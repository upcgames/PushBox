import { createSeenProgress } from '../state/seenProgress.js';

export function canEarnTroll({ game, screen, inputRequest, playerAnimation }) {
  return screen?.id === 'gameplay' && inputRequest?.consumer === 'ControlDeMovimiento' &&
    game?.level === 4 && game.nextLevel === 4 && !playerAnimation &&
    game.board.boxes.filter(box => box.onTarget).length >= 3;
}

// Read canonical placement facts. Seeing the illustration in lore is not earning
// the gameplay button; mark it seen only when mobile gameplay can reveal it.
export function mountTrollReward(store, { progress = createSeenProgress(), enabled = () => true } = {}) {
  let previousGame = null, lastPlaced = null, earning = false;
  function sync() {
    store.setTrollReward({ unlocked: progress.has('carita'),
      hinted: progress.has('carita') && !progress.has('caritaUsed') });
  }
  function refresh() {
    const state = store.getSnapshot(), previous = previousGame;
    previousGame = state.game;
    if (state.game?.level !== 4) lastPlaced = null;
    else if (previous !== state.game) {
      const placed = state.game.board.boxes.find(box => box.onTarget && previous?.level === 4 &&
        !previous.board.boxes.find(old => old.index === box.index)?.onTarget);
      if (placed) lastPlaced = placed;
    }
    if (!earning && enabled() && !progress.has('carita') && canEarnTroll(state)) {
      earning = true;
      const boxes = state.game.board.boxes;
      const placed = boxes.find(box => box.index === lastPlaced?.index && box.onTarget) || boxes.find(box => box.onTarget);
      // Capture the canonical caja that earned the reward, before saving unlock.
      // Saved rewards show immediately on later visits; no repeated entrance.
      if (placed && Number.isFinite(placed.x) && Number.isFinite(placed.y)) {
        store.setTrollEntrance({ source: { level: 4, x: placed.x, y: placed.y }, pending: true, active: false });
      }
      progress.mark('carita');
      earning = false;
    }
    sync();
  }
  const stopProgress = progress.subscribe(sync);
  const stopUsed = store.on('trollRewardUsed', () => progress.mark('caritaUsed'));
  const stopState = store.subscribe(refresh);
  return { refresh, dispose() { stopState(); stopUsed(); stopProgress(); } };
}
