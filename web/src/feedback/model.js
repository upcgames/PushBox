// Presentation only. Coordinates and completion come from the shared store.
export function feedbackScene({ game, screen }) {
  if (!game || screen?.id !== 'gameplay' || game.nextLevel !== game.level) return null;

  const { board, portal, player, grid, level } = game;
  const cues = [];
  for (const gap of board.gaps) cues.push({ ...gap, kind: 'danger' });
  for (const target of board.targets) {
    if (!target.covered) cues.push({ ...target, kind: 'target',
      showCenter: target.x !== player.x || target.y !== player.y });
  }
  for (const box of board.boxes) {
    // Final-level boxes 10–16 blend into the background until they harden.
    const hidden = level === 5 && box.index >= 10;
    const locked = hidden && portal.active;
    const nearby = (box.x === player.x && Math.abs(box.y - player.y) === grid.objectSize) ||
      (box.y === player.y && Math.abs(box.x - player.x) === grid.objectSize);
    if (hidden && !locked && (box.onTarget || !nearby)) continue;
    cues.push({ x: box.x, y: box.y, nearby, idle: !hidden,
      direction: nearby ? { x: Math.sign(box.x - player.x), y: Math.sign(box.y - player.y) } : null,
      kind: locked ? 'locked' : box.onTarget ? 'complete' : 'box' });
  }
  if (portal.active) cues.push({ x: portal.x, y: portal.y, kind: 'portal' });
  return { level, grid, cues, portalActive: portal.active };
}

export function feedbackInputs(state) {
  return { game: state.game, screen: state.screen };
}

export function sameFeedbackInputs(a, b) {
  return a.game === b.game && a.screen?.id === b.screen?.id;
}
