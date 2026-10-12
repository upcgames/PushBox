// Shared visual motion: UI uses strength 1; gameplay can use strength 0.4.
// This samples presentation only and never changes board coordinates or rules.
export function sampleSlugMotion(elapsed, { strength = 1, size = 28, moveDuration = 180, settleDuration = 140 } = {}) {
  const progress = Math.max(0, Math.min(1, elapsed / moveDuration));
  const travel = progress * progress * (3 - 2 * progress);
  const strain = Math.sin(progress * Math.PI);
  let longitudinal = size + Math.round(strain * 8 * strength);
  let transverse = size - Math.round(strain * 4 * strength);
  if (elapsed > moveDuration && elapsed < moveDuration + settleDuration) {
    const settle = Math.sin((elapsed - moveDuration) / settleDuration * Math.PI);
    longitudinal = size - Math.round(settle * 4 * strength);
    transverse = size + Math.round(settle * 3 * strength);
  }
  return { travel, longitudinal, transverse };
}
