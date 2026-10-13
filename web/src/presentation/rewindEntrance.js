// Shared by production and portal-lab. Coordinates are CSS pixels in the
// caller's overlay; scale accounts for Inspector device-frame transforms.
export function rewindEntranceGeometry(source, game, surface, { canvas, slot, viewport, board }) {
  if (!game || source.level !== game.level || !canvas.width || !slot.width) return null;
  const sx = canvas.width / surface.canvas.width, sy = canvas.height / surface.canvas.height;
  const tile = surface.tileSize, scale = slot.width / 76;
  const sourceBox = { x: canvas.left + source.x * tile * sx, y: canvas.top + source.y * tile * sy,
    width: game.grid.objectSize * tile * sx, height: game.grid.objectSize * tile * sy };
  return { x: sourceBox.x + sourceBox.width / 2, y: sourceBox.y + sourceBox.height / 2,
    top: board.top, right: viewport.right - 36 * scale,
    endX: slot.left + slot.width / 2, endY: slot.top + slot.height / 2, scale, sourceBox };
}

export function sampleRewindEntrance(elapsed, { x, y, top, right, endX, endY, scale = 1 }) {
  const hold = 900, flight = 1650;
  const progress = Math.max(0, Math.min(1, (elapsed - hold) / flight));
  const glowOpacity = Math.max(0, Math.min(1, (hold + 600 - elapsed) / 200));
  if (elapsed < hold) {
    const pop = 1 - (1 - Math.max(0, Math.min(1, elapsed / 400))) ** 3;
    return { x, y: y - 40 * scale * pop, size: (12 + 36 * pop) * scale, rotation: 0,
      glowOpacity, complete: false, flying: false };
  }
  const travel = 1 - (1 - progress) ** 2, remaining = 1 - travel;
  const controlX = Math.min(right, endX + 50 * scale);
  return {
    x: remaining ** 3 * x + 3 * remaining ** 2 * travel * right +
      3 * remaining * travel ** 2 * controlX + travel ** 3 * endX,
    y: remaining ** 3 * (y - 40 * scale) + 3 * remaining ** 2 * travel * (top - 60 * scale) +
      3 * remaining * travel ** 2 * (endY - 110 * scale) + travel ** 3 * endY,
    size: (48 - 8 * travel) * scale, rotation: -720 * travel || 0,
    glowOpacity, complete: progress >= 1, flying: true,
  };
}

// Presentation lifecycle only: never sends input, pauses the original routine,
// writes to its canvas, or infers gameplay from pixels.
export function createRewindEntranceDriver(store, { enabled = () => true, measure, render, clear,
  reducedMotion = () => false, hidden = () => document.hidden,
  requestFrame = requestAnimationFrame, cancelFrame = cancelAnimationFrame }) {
  let frame = null, started = null, source = null, disposed = false, failed = false;
  const eligible = state => !failed && enabled() && !hidden() && state.screen?.id === 'gameplay' &&
    !!state.game && state.game.level === state.game.nextLevel && !state.playerAnimation;
  function finish() {
    if (frame !== null) cancelFrame(frame);
    frame = null; started = null; source = null; clear(); store.setRewindEntranceActive(false);
  }
  function tick(time) {
    frame = null;
    const state = store.getSnapshot();
    if (disposed || !eligible(state) || !state.undoHint) { finish(); return; }
    const geometry = measure(source);
    if (!geometry) { finish(); return; }
    if (started === null) {
      started = time;
      store.acknowledgeRewindEntrance();
    }
    const pose = sampleRewindEntrance(time - started, geometry);
    if (pose.complete || reducedMotion()) { finish(); return; }
    render(pose, geometry, time - started);
    frame = requestFrame(tick);
  }
  function refresh() {
    const state = store.getSnapshot();
    if (state.screen?.id !== 'gameplay') failed = false;
    if (!eligible(state) || !state.undoHint) { if (frame !== null || source) finish(); return; }
    if (source && state.undoHintSource && ['level', 'x', 'y'].some(key => source[key] !== state.undoHintSource[key])) {
      finish(); return;
    }
    if (source || !state.rewindDiscovery.entrancePending || !state.undoHintSource) return;
    source = { ...state.undoHintSource };
    store.setRewindEntranceActive(true);
    frame = requestFrame(tick); // Let the shared control slot mount first.
  }
  const stop = store.subscribe(refresh);
  const stopError = store.on('runtimeError', () => { failed = true; finish(); });
  return { refresh, dispose() { disposed = true; stop(); stopError(); finish(); } };
}
