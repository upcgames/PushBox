// Level-one rules only. No DOM, Phaser, console shim, timers, or shared state.
const DIRECTIONS = Object.freeze({ up: [0, -1], down: [0, 1], left: [-1, 0], right: [1, 0] });
const same = (a, b) => a.x === b.x && a.y === b.y;
function freeze(value) {
  if (value && typeof value === 'object') {
    Object.values(value).forEach(freeze);
    Object.freeze(value);
  }
  return value;
}

export function createSession(definition) {
  const level = freeze(structuredClone(definition));
  const subscribers = new Set(), listeners = new Set();
  let history = [], version = 0, state, disposed = false, dispatching = false;
  const initial = lives => ({ level: 1, phase: 'playing', player: { ...level.player },
    boxes: level.boxes.map((box, id) => ({ ...box, id })), steps: 0, lives });
  function snapshot(next) {
    const targets = level.targets.map(target => ({ ...target, covered: next.boxes.some(box => same(box, target)) }));
    return freeze({ ...next, version: ++version, walls: level.walls, targets,
      portal: { ...level.portal, active: targets.every(target => target.covered) },
      moveLimit: level.moveLimit, undoAvailable: history.length });
  }
  state = snapshot(initial(level.initialLives));
  function safely(callback, value) {
    try { callback(value); } catch (error) { console.error('[Level 1 session] observer failed', error); }
  }
  function publish(next, events) {
    state = snapshot(next);
    for (const callback of [...subscribers]) safely(callback, state);
    for (const event of events) {
      const envelope = freeze({ ...event, version: state.version });
      for (const callback of [...listeners]) safely(callback, envelope);
    }
  }
  function apply(command) {
    if (disposed) throw new Error('Session is disposed');
    if (command.type === 'restart') {
      history = [];
      publish(initial(level.initialLives), [{ type: 'restarted' }]);
      return true;
    }
    if (command.type === 'retry' && state.phase === 'lifeLost') {
      history = [];
      publish(initial(state.lives), [{ type: 'retried' }]);
      return true;
    }
    if (command.type === 'pause' && ['playing', 'paused'].includes(state.phase)) {
      publish({ ...state, phase: state.phase === 'playing' ? 'paused' : 'playing' }, [{ type: 'pauseChanged' }]);
      return true;
    }
    if (state.phase !== 'playing') return false;
    if (command.type === 'undo') {
      const previous = history.pop();
      if (!previous) return false;
      // Canonical undo adds three steps and does not run the death check.
      publish({ ...state, ...previous, steps: state.steps + level.undoCost }, [{ type: 'undone' }]);
      return true;
    }
    if (command.type !== 'move' || !DIRECTIONS[command.direction]) return false;
    const [dx, dy] = DIRECTIONS[command.direction];
    const advance = point => ({ x: point.x + dx * level.stepSize, y: point.y + dy * level.stepSize });
    const player = advance(state.player);
    const box = state.boxes.find(item => same(item, player));
    const destination = box ? advance(box) : player;
    const obstacle = level.walls.some(wall => same(wall, destination)) ? 'wall'
      : box && state.boxes.some(item => item.id !== box.id && same(item, destination)) ? 'box'
        : !box && (player.x < 0 || player.y < 0 || player.x >= level.width || player.y >= level.height) ? 'boundary' : null;
    if (obstacle) {
      const event = freeze({ type: 'moveBlocked', obstacle, position: destination, version: state.version });
      for (const callback of [...listeners]) safely(callback, event);
      return false;
    }
    history.push({ player: state.player, boxes: state.boxes });
    if (history.length > level.undoLimit) history.shift();
    const boxes = state.boxes.map(item => item.id === box?.id ? { ...item, ...destination } : item);
    const events = [{ type: 'playerMoved', from: state.player, to: player }];
    if (box) events.push({ type: 'boxPushed', id: box.id, from: box, to: destination });
    const portalActive = level.targets.every(target => boxes.some(item => same(item, target)));
    if (portalActive !== state.portal.active) events.push({ type: 'portalChanged', active: portalActive });
    let next = { ...state, player, boxes, steps: state.steps + 1 };
    // Canonical portal completion precedes the movement-budget death check.
    if (portalActive && same(player, level.portal)) {
      next.phase = 'completed';
      events.push({ type: 'levelCompleted', level: 1 });
    } else if (next.steps >= level.moveLimit) {
      next.lives--;
      next.phase = next.lives ? 'lifeLost' : 'gameOver';
      events.push({ type: 'lifeLost', reason: 'moveLimit' });
    }
    publish(next, events);
    return true;
  }
  return Object.freeze({
    getSnapshot: () => state,
    command(command) {
      if (dispatching) throw new Error('Commands must be dispatched outside session observers');
      dispatching = true;
      try { return apply(command); } finally { dispatching = false; }
    },
    subscribe(callback) {
      if (disposed) throw new Error('Session is disposed');
      subscribers.add(callback); safely(callback, state);
      return () => subscribers.delete(callback);
    },
    onEvent(callback) {
      if (disposed) throw new Error('Session is disposed');
      listeners.add(callback);
      return () => listeners.delete(callback);
    },
    dispose() { disposed = true; subscribers.clear(); listeners.clear(); history = []; },
  });
}
