import { drawBobby } from './bobby.js';

// The lab uses the original CuadroDeVidas pause; gameplay follows its scope.
export const STEPS_WARNING_DURATION = 2500;
const JOLTS = [[-5, 2], [4, -3], [-3, -2], [6, 1], [-6, 3], [2, -4], [0, 0], [0, 0], [5, -2], [-4, 1], [3, 3], [-5, -3], [1, 0]];

export function sampleStepsWarning(elapsed, reducedMotion = false) {
  const [dx, dy] = reducedMotion ? [0, 0] : JOLTS[Math.floor(Math.max(0, elapsed) / 35) % JOLTS.length];
  return { dx, dy, foreground: reducedMotion || Math.floor(elapsed / 300) % 2 === 0 ? '#eab308' : '#ef4444' };
}

export function drawStepsWarningBobby(ctx, x, y, elapsed, options = {}, reducedMotion = false) {
  const pose = sampleStepsWarning(elapsed, reducedMotion);
  const size = (options.cellSize || 14) * 2, scale = size / 28;
  drawBobby(ctx, x + Math.round(pose.dx * scale), y + Math.round(pose.dy * scale),
    { ...options, width: size, height: size, foreground: pose.foreground });
}
