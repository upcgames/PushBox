const DIRECTIONS = [[0, -1], [0, 1], [-1, 0], [1, 0]];
const MAX_HINT_UNDOS = 3;
const key = ({ x, y }) => `${x},${y}`;
const valid = tile => Number.isFinite(tile.x) && Number.isFinite(tile.y);

// Owner-confirmed level-3 bridges, in original console coordinates:
//   caja (42, 32) -> vacío (42, 34)
//   caja (38, 38) -> vacío (36, 38)
// These open access to the isolated caja that must reach its hueco. All other
// caja sacrifices are mistakes for hints. Origins document the intended setup;
// exemption depends on the destination, since the same bridge can be built from
// another approach. This policy never changes legal pushes, walks or the camera.
export const INTENDED_BRIDGES = [
  { level: 3, caja: { x: 42, y: 32 }, vacio: { x: 42, y: 34 } },
  { level: 3, caja: { x: 38, y: 38 }, vacio: { x: 36, y: 38 } },
];

function createdBridge(before, after) {
  if (after.board.boxes.length !== before.board.boxes.length - 1 ||
      after.board.gaps.length !== before.board.gaps.length - 1) return null;
  const gaps = new Set(after.board.gaps.filter(valid).map(key));
  const removed = before.board.gaps.filter(gap => valid(gap) && !gaps.has(key(gap)));
  return removed.length === 1 ? removed[0] : null;
}

function eligibleBox(game, box) {
  return valid(box) && !box.onTarget && !(game.level === 5 && (box.index >= 10 || game.portal.active));
}

// Flood only safe walks on the original movement lattice. Never move cajas or
// search future board configurations; gaps become walkable only when canonical
// bridge creation actually removes them from the current gap list.
export function reachablePlayerPositions(game) {
  const { grid, board, player } = game, size = grid.objectSize;
  const bounds = grid.walkBounds;
  const walls = new Set(board.walls.filter(valid).map(key));
  const boxes = new Set(board.boxes.filter(valid).map(key));
  const gaps = new Set(board.gaps.filter(valid).map(key));
  const visited = new Set();
  if (!bounds || !valid(player) || size <= 0 || gaps.has(key(player))) return visited;
  const queue = [player]; visited.add(key(player));
  for (let index = 0; index < queue.length; index++) {
    const tile = queue[index];
    for (const [dx, dy] of DIRECTIONS) {
      const next = { x: tile.x + dx * size, y: tile.y + dy * size }, position = key(next);
      if (next.x < bounds.minX || next.x > bounds.maxX || next.y < bounds.minY || next.y > bounds.maxY ||
          visited.has(position) || walls.has(position) || boxes.has(position) || gaps.has(position)) continue;
      visited.add(position); queue.push(next);
    }
  }
  return visited;
}

export function boxHasLegalPush(game, box, reachable = reachablePlayerPositions(game)) {
  const size = game.grid.objectSize;
  const obstacles = new Set([...game.board.walls, ...game.board.boxes].filter(valid).map(key));
  // CajaLugarPermitido checks only walls/other cajas: destinations may be gaps
  // (bridges) or outside the walk bounds. Do not impose new push restrictions.
  return DIRECTIONS.some(([dx, dy]) => reachable.has(key({ x: box.x - dx * size, y: box.y - dy * size })) &&
    !obstacles.has(key({ x: box.x + dx * size, y: box.y + dy * size })));
}

// Optimistic reverse pushes: ignore other cajas and treat gaps as potentially
// bridged floor. Each predecessor needs space for both the caja and Bobby two
// tiles behind its destination. No player routing or future puzzle search here:
// absence of even this optimistic route proves the caja cannot be recovered.
// Still-present intended bridge destinations are useful endpoints themselves.
export function recoverableBoxPositions(game) {
  const { grid, board } = game, size = grid.objectSize, bounds = grid.walkBounds;
  if (!bounds || !(size > 0) || !Array.isArray(board.targets)) return null;
  const walls = new Set(board.walls.filter(valid).map(key));
  const free = tile => valid(tile) && tile.x >= bounds.minX && tile.x <= bounds.maxX &&
    tile.y >= bounds.minY && tile.y <= bounds.maxY && !walls.has(key(tile));
  const gaps = new Set(board.gaps.filter(valid).map(key));
  const endpoints = [...board.targets, ...INTENDED_BRIDGES
    .filter(bridge => bridge.level === game.level && gaps.has(key(bridge.vacio)))
    .map(bridge => bridge.vacio)];
  const visited = new Set(), queue = [];
  for (const tile of endpoints) if (free(tile) && !visited.has(key(tile))) {
    visited.add(key(tile)); queue.push(tile);
  }
  for (let index = 0; index < queue.length; index++) {
    const tile = queue[index];
    for (const [dx, dy] of DIRECTIONS) {
      const previous = { x: tile.x - dx * size, y: tile.y - dy * size };
      const support = { x: tile.x - 2 * dx * size, y: tile.y - 2 * dy * size };
      if (!free(previous) || !free(support) || visited.has(key(previous))) continue;
      visited.add(key(previous)); queue.push(previous);
    }
  }
  return visited;
}

// Sample only at the original movement routine's next input boundary, after all
// push/undo/bridge animations and board updates have completed. Changes in actual
// undo history identify successful undo; input characters are never guessed.
export function mountUndoHint(store, { enabled = () => true } = {}) {
  let previous = null, trapped = new Map(), sacrifices = new Map(), disposed = false;
  const shownTraps = new Set(), shownSacrifices = new Set();
  function clearTracking() {
    previous = null; trapped.clear(); sacrifices.clear(); shownTraps.clear(); shownSacrifices.clear();
  }
  const stable = state => enabled() && state.screen?.id === 'gameplay' && !!state.game &&
    state.game.nextLevel === state.game.level && !state.playerAnimation &&
    state.inputRequest?.kind === 'key' && state.inputRequest.consumer === 'ControlDeMovimiento';
  const visible = state => stable(state) && state.game.undoAvailable;
  function refresh() {
    const state = store.getSnapshot();
    let source = null;
    if (!enabled() || !state.game) clearTracking();
    if (visible(state)) {
      const affordable = state.game.undoAffordableDepth ?? state.game.undoDepth;
      for (const [position, distance] of trapped) {
        const box = state.game.board.boxes.find(box => key(box) === position);
        if (box && distance <= MAX_HINT_UNDOS && distance <= affordable) {
          shownTraps.add(box.index); source ??= { level: state.game.level, x: box.x, y: box.y };
        }
      }
      for (const [position, distance] of sacrifices) {
        if (distance <= MAX_HINT_UNDOS && distance <= affordable) {
          shownSacrifices.add(position);
          const [x, y] = position.split(',').map(Number);
          source ??= { level: state.game.level, x, y };
        }
      }
    }
    store.setUndoHint(!!source, source);
  }
  const stopWaiting = store.on('input:waiting', ({ request }) => {
    const state = store.getSnapshot(), game = state.game;
    if (disposed || !stable(state) || request?.consumer !== 'ControlDeMovimiento') return;
    if (!previous || previous.level !== game.level || game.steps < previous.steps) {
      clearTracking(); previous = game; refresh(); return;
    }
    const undo = game.undoDepth < previous.undoDepth;
    const moved = game.board.boxes.length === previous.board.boxes.length
      ? game.board.boxes.filter(box => {
        const old = previous.board.boxes.find(item => item.index === box.index);
        return old && (box.x !== old.x || box.y !== old.y);
      }) : [];
    // Original history is capped at five records. A push still changes the
    // canonical caja and spent moves when a full history drops its oldest record.
    const pushed = !undo && game.steps > previous.steps && moved.length > 0;
    const bridge = !undo && game.steps > previous.steps ? createdBridge(previous, game) : null;
    if (!trapped.size && !sacrifices.size && !pushed && !bridge) { previous = game; refresh(); return; }
    const adjustment = undo ? game.undoDepth - previous.undoDepth : Math.max(0, game.steps - previous.steps);
    const reachable = reachablePlayerPositions(game), recoverable = recoverableBoxPositions(game), nextTrapped = new Map();
    const isTrapped = box => !boxHasLegalPush(game, box, reachable) ||
      (recoverable !== null && !recoverable.has(key(box)));
    let recovered = false;
    for (const [position, previousDistance] of trapped) {
      const distance = previousDistance + adjustment;
      const old = previous.board.boxes.find(box => key(box) === position);
      const box = old ? game.board.boxes.find(box => box.index === old.index) : null;
      if (undo && old && box && shownTraps.has(old.index) &&
          (box.x !== old.x || box.y !== old.y) && (box.onTarget || !isTrapped(box))) recovered = true;
      // Keep a suppressed marker while the bad push is still in real history:
      // undoing later walks can make recovery actionable again. Forget it once
      // the original history drops that push, so unrelated undos cannot revive it.
      if (distance < 1 || distance > game.undoDepth) continue;
      if (box && eligibleBox(game, box) && isTrapped(box)) nextTrapped.set(key(box), distance);
    }
    if (pushed) {
      const previouslyRecoverable = recoverableBoxPositions(previous);
      for (const box of moved) {
        const old = previous.board.boxes.find(item => item.index === box.index);
        // Sliding an already-lost caja must not restart the recovery window,
        // including after the original offending push has left undo history.
        const alreadyLost = previouslyRecoverable !== null && old && !previouslyRecoverable.has(key(old));
        if (!alreadyLost && eligibleBox(game, box) && isTrapped(box) && !nextTrapped.has(key(box))) nextTrapped.set(key(box), 1);
      }
    }
    const gaps = new Set(game.board.gaps.filter(valid).map(key)), nextSacrifices = new Map();
    for (const [position, previousDistance] of sacrifices) {
      const distance = previousDistance + adjustment;
      if (undo && shownSacrifices.has(position) && gaps.has(position)) {
        const restored = game.board.boxes.filter(box => !previous.board.boxes.some(old => old.index === box.index));
        if (restored.some(box => box.onTarget || !isTrapped(box))) recovered = true;
      }
      if (distance >= 1 && distance <= game.undoDepth && !gaps.has(position)) nextSacrifices.set(position, distance);
    }
    if (bridge && !INTENDED_BRIDGES.some(intended => intended.level === game.level && key(intended.vacio) === key(bridge))) {
      nextSacrifices.set(key(bridge), 1);
    }
    for (const index of shownTraps) {
      if (!game.board.boxes.some(box => box.index === index && nextTrapped.has(key(box)))) shownTraps.delete(index);
    }
    for (const position of shownSacrifices) if (!nextSacrifices.has(position)) shownSacrifices.delete(position);
    previous = game; trapped = nextTrapped; sacrifices = nextSacrifices; refresh();
    if (recovered) store.reportRewindRecovery({ level: game.level });
  });
  const stopState = store.subscribe(refresh);
  const stopError = store.on('runtimeError', () => { clearTracking(); store.setUndoHint(false); });
  return { refresh, dispose() { disposed = true; stopWaiting(); stopState(); stopError(); clearTracking(); store.setUndoHint(false); } };
}
