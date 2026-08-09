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
        nextYield = await gen.next();
        if (++it > 10000) { console.warn('catch-up capped'); break; }
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


