export const CELL_PAINT_COST = 0.12;

export async function runAnim(generatorFn, ...args) {
  const gen = generatorFn(...args);
  let virtualTime = 0;
  let nextYield = await gen.next();
  let startTime = null;

  return new Promise(resolve => {
    async function advance(elapsed) {
      let it = 0;
      while (nextYield && !nextYield.done && virtualTime + (nextYield.value ?? 0) + CELL_PAINT_COST <= elapsed) {
        virtualTime += (nextYield.value ?? 0) + CELL_PAINT_COST;
        const before = performance.now();
        nextYield = await gen.next();
        const wait = performance.now() - before;
        // Pause animation elapsed while generator was blocked on input (scanf/_getch).
        // No magic number — any wall time spent waiting for input is excluded.
        if (startTime !== null) startTime += wait;
        if (++it > 10000) { console.warn('catch-up capped', {virtualTime, elapsed, it, yieldVal: nextYield.value}); break; }
      }
    }
    async function tick(ts) {
      if (startTime === null) startTime = ts;
      const elapsed = ts - startTime;
      await advance(elapsed);
      if (!nextYield.done) {
        requestAnimationFrame(tick);
      } else {
        resolve();
      }
    }
    requestAnimationFrame(tick);
  });
}
