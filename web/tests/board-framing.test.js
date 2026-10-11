import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { reachableBounds, wallBounds, fitBoard, usesBoardFraming } from '../src/presentation/boardFraming.js';
const game = { grid: { cols: 80, rows: 63, objectSize: 2 },
  board: { walls: [{ x: 20, y: 10 }, { x: 40, y: 30 }] }, player: { x: 22, y: 12 } };
test('framing includes full wall tiles and margin, independently of player and portal', () => {
  assert.deepEqual(wallBounds(game), { x: 19, y: 9, width: 24, height: 24 });
  assert.deepEqual(wallBounds({ ...game, player: { x: 30, y: 24 }, portal: { x: 0, y: 0 } }), wallBounds(game));
  assert.deepEqual(wallBounds({ ...game, board: { walls: [{ x: 0, y: 0 }, { x: 78, y: 61 }] } }),
    { x: 0, y: 0, width: 80, height: 63 });
  assert.equal(wallBounds(null), null);
});
test('the whole board fits narrow and short viewports without stretching', () => {
  const bounds = { width: 24, height: 36 };
  for (const [width, height] of [[352, 420], [385, 472], [422, 552], [430, 100]]) {
    const fit = fitBoard(bounds, width, height);
    assert.ok(fit.width <= width && fit.height <= height);
    assert.ok(Math.abs(fit.width / fit.height - bounds.width / bounds.height) < 1e-12);
  }
});
test('reserved wall slots cannot collapse framing or produce invalid CSS dimensions', () => {
  const reserved = [{}, { x: undefined, y: undefined }, { x: NaN, y: 20 }, { x: 20, y: Infinity }];
  assert.deepEqual(wallBounds({ ...game, board: { walls: [...game.board.walls, ...reserved] } }), wallBounds(game));
  assert.equal(wallBounds({ ...game, board: { walls: reserved } }), null);
});
test('mobile framing leaves pause, lore and full-screen scenes uncropped', () => {
  assert.equal(usesBoardFraming({ game, screen: { id: 'gameplay' } }), true);
  for (const id of ['InterfazPausa', 'Lore', 'InterfazYouWin', 'InterfazYouLose', 'main', 'launcher']) {
    assert.equal(usesBoardFraming({ game, screen: { id } }), false);
  }
  assert.equal(usesBoardFraming({ game: null, screen: { id: 'gameplay' } }), false);
});

test('reachable framing excludes disconnected artwork, distant walls and diagonal islands', () => {
  const matrix = Array.from({ length: 10 }, () => Array(12).fill(0));
  for (const [x, y] of [[2, 2], [4, 2], [2, 4], [4, 4], [8, 2], [10, 2], [6, 6]]) matrix[y][x] = 5;
  const session = { grid: { cols: 12, rows: 10, objectSize: 2 }, player: { x: 2, y: 2 },
    board: { walls: [{ x: 6, y: 2 }, { x: 6, y: 4 }, { x: 10, y: 8 }, {}],
      boxes: [{ x: 4, y: 2 }], gaps: [{ x: 2, y: 4 }] } };
  assert.deepEqual(reachableBounds(session, matrix), { x: 1, y: 1, width: 6, height: 6 });
});

test('gaps stop the flood at the first danger tile; bridges unlock one layer at a time', () => {
  const matrix = Array.from({ length: 6 }, () => Array(14).fill(0));
  for (const x of [2, 4, 6, 8, 10]) matrix[2][x] = 5;
  const session = { grid: { cols: 14, rows: 6, objectSize: 2 }, player: { x: 2, y: 2 },
    board: { walls: [], gaps: [{ x: 6, y: 2 }, { x: 8, y: 2 }] } };
  assert.deepEqual(reachableBounds(session, matrix, 0), { x: 2, y: 2, width: 6, height: 2 });
  const firstBridge = { ...session, board: { ...session.board, gaps: [{ x: 8, y: 2 }] } };
  assert.deepEqual(reachableBounds(firstBridge, matrix, 0), { x: 2, y: 2, width: 8, height: 2 });
  const secondBridge = { ...session, board: { ...session.board, gaps: [] } };
  assert.deepEqual(reachableBounds(secondBridge, matrix, 0), { x: 2, y: 2, width: 10, height: 2 });
});

test('only cardinally adjacent boxes allow the camera flood through gaps ahead of time', () => {
  const matrix = Array.from({ length: 6 }, () => Array(14).fill(0));
  for (const x of [2, 4, 6, 8, 10]) matrix[2][x] = 5;
  const session = { grid: { cols: 14, rows: 6, objectSize: 2 }, player: { x: 2, y: 2 },
    board: { walls: [], gaps: [{ x: 6, y: 2 }, { x: 8, y: 2 }], boxes: [{ x: 4, y: 2 }] } };
  assert.deepEqual(reachableBounds(session, matrix, 0), { x: 2, y: 2, width: 8, height: 2 });
  const diagonal = { ...session, board: { ...session.board, boxes: [{ x: 4, y: 4 }] } };
  assert.deepEqual(reachableBounds(diagonal, matrix, 0), { x: 2, y: 2, width: 6, height: 2 });
});

test('reachable framing derives finite bounds for every static level and narrows level five', () => {
  const collision = JSON.parse(readFileSync(new URL('../pushbox_modules/maps_json/collision_data.json', import.meta.url)));
  const spawns = [null, [36, 34], [42, 40], [48, 22], [38, 12], [40, 40]];
  for (const level of [1, 2, 3, 4, 5]) {
    const { matrix } = JSON.parse(readFileSync(new URL(`../pushbox_modules/maps_json/mapa0${level}.json`, import.meta.url)));
    const session = { grid: game.grid, player: { x: spawns[level][0], y: spawns[level][1] },
      board: { walls: collision[level].walls.map(([x, y]) => ({ x, y })) } };
    const bounds = reachableBounds(session, matrix);
    assert.ok(bounds && Object.values(bounds).every(Number.isFinite));
    assert.ok(bounds.x <= session.player.x && session.player.x + 2 <= bounds.x + bounds.width);
    assert.ok(bounds.y <= session.player.y && session.player.y + 2 <= bounds.y + bounds.height);
    if (level === 5) {
      assert.deepEqual(bounds, { x: 17, y: 3, width: 48, height: 52 });
      assert.ok(bounds.width < wallBounds(session).width);
    }
  }
});
