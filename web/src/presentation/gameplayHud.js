// The original CuadroDeVidas draws its HUD on console row 60. Read its
// displayed remaining moves; game.steps is moves SPENT, including undo cost.
// This view never supplies budgets, changes rules, or publishes game state.
export function gameplayHudSnapshot(state) {
  const game = state.game;
  if (state.screen?.id !== 'gameplay' || !game) return null;
  const line = state.console?.lines?.[60] || '';
  const match = line.match(/NIVEl:\s*(\d+)\s+MOVIMIENTOS:\s*(\d+)/);
  const remaining = match && Number(match[1]) === game.level ? Number(match[2]) : null;
  return { level: game.level, lives: game.lives, spent: game.steps, remaining };
}
