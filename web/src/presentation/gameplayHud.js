// The original CuadroDeVidas draws its HUD on console row 60. Read its
// displayed remaining moves; game.steps is moves SPENT, including undo cost.
// This view never supplies budgets, changes rules, or publishes game state.
export function showsGameplayHud(state) {
  return !!state.game && ['gameplay', 'InterfazPausa'].includes(state.screen?.id);
}

export function gameplayHudSnapshot(state, previous = null) {
  const game = state.game;
  if (!showsGameplayHud(state)) return null;
  const paused = state.screen.id === 'InterfazPausa';
  const line = state.console?.lines?.[60] || '';
  const match = line.match(/NIVEl:\s*(\d+)\s+MOVIMIENTOS:\s*(\d+)/);
  const remaining = match && Number(match[1]) === game.level ? Number(match[2])
    : paused && previous?.level === game.level && previous.spent === game.steps ? previous.remaining : null;
  return { level: game.level, lives: game.lives, spent: game.steps, remaining, paused };
}
