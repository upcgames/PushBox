// Coordinates are console cells. Wall entries cover objectSize × objectSize cells.
// Read only walls: moving objects and the portal cannot change the camera bounds.
export function wallBounds(game, margin = 1) {
  // Canonical counts for levels 3/4 include reserved, unfilled wall slots.
  // Those are not coordinates and must not participate in the camera bounds.
  const walls = game?.board.walls.filter(wall => Number.isFinite(wall.x) && Number.isFinite(wall.y));
  if (!walls?.length) return null;
  const { cols, rows, objectSize } = game.grid;
  const left = Math.max(0, Math.min(...walls.map(wall => wall.x)) - margin);
  const top = Math.max(0, Math.min(...walls.map(wall => wall.y)) - margin);
  const right = Math.min(cols, Math.max(...walls.map(wall => wall.x)) + objectSize + margin);
  const bottom = Math.min(rows, Math.max(...walls.map(wall => wall.y)) + objectSize + margin);
  if (right <= left || bottom <= top) return null;
  return { x: left, y: top, width: right - left, height: bottom - top };
}

// Camera heuristic on the two-cell movement lattice: a gap adjacent to an
// initial box is potentially paved. Other gaps are included as danger context
// but stop the flood. This does not simulate legal pushes or box consumption.
export function reachableBounds(game, matrix, margin = 1) {
  const { cols, rows, objectSize: size } = game.grid;
  const walls = new Set(game.board.walls.filter(wall => Number.isFinite(wall.x) && Number.isFinite(wall.y))
    .map(wall => `${wall.x},${wall.y}`));
  const gaps = new Set((game.board.gaps || []).map(gap => `${gap.x},${gap.y}`));
  const potentiallyPaved = new Set();
  for (const { x, y } of game.board.boxes || []) {
    for (const [dx, dy] of [[-size, 0], [size, 0], [0, -size], [0, size]]) {
      const key = `${x + dx},${y + dy}`;
      if (gaps.has(key)) potentiallyPaved.add(key);
    }
  }
  const visited = new Set(), queue = [game.player], included = [];
  for (let index = 0; index < queue.length; index++) {
    const tile = queue[index], { x, y } = tile, key = `${x},${y}`;
    if (visited.has(key)) continue;
    visited.add(key);
    if (x < 0 || y < 0 || x + size > cols || y + size > Math.min(rows, matrix.length)) continue;
    if (walls.has(key)) continue;
    const color = matrix[y]?.[x];
    if (!Number.isFinite(color) || color === 0) continue;
    included.push(tile);
    if (gaps.has(key) && !potentiallyPaved.has(key)) continue;
    queue.push({ x: x - size, y }, { x: x + size, y }, { x, y: y - size }, { x, y: y + size });
  }
  if (!included.length) return null;
  return wallBounds({ grid: game.grid, board: { walls: included } }, margin);
}

export function fitBoard(bounds, width, height) {
  const scale = Math.max(0, Math.min(width / bounds.width, height / bounds.height));
  return { width: bounds.width * scale, height: bounds.height * scale };
}

export function usesBoardFraming(state) {
  return state.screen?.id === 'gameplay' && !!state.game;
}
