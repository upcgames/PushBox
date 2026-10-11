import { CELL_PAINT_COST } from '../animationDriver.js';

// Same generator timing/paint budget as the canonical animation driver, using
// an abortable session clock so reset/disposal cannot leave an old loop alive.
export function createSessionAnimation(clock) {
  return async (generatorFn, ...args) => {
    const generator = generatorFn(...args);
    let virtualTime = 0, startTime = null;
    try {
      let next = await generator.next();
      while (!next.done) {
        const timestamp = await clock.frame();
        clock.check();
        if (startTime === null) startTime = timestamp;
        const elapsed = timestamp - startTime;
        let iterations = 0;
        while (!next.done && virtualTime + (next.value ?? 0) + CELL_PAINT_COST <= elapsed) {
          virtualTime += (next.value ?? 0) + CELL_PAINT_COST;
          const before = clock.now();
          next = await generator.next();
          startTime += clock.now() - before;
          if (++iterations > 10000) break;
          clock.check();
        }
      }
    } finally { await generator.return(); }
  };
}
