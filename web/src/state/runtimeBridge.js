import { runtimeState, GameState } from './gameState.js';

export function createRuntimeBridge(store) {
const GameState = store.api, runtimeState = store;
let readGame = null;
const screens = [];
const inputScopes = [];

function currentRequest() {
  const owner = screens.at(-1) || null;
  return inputScopes.findLast(scope => scope.owner === owner)?.request || null;
}

function publishContext(reason) {
  runtimeState.publish({ screen: screens.at(-1) || null, inputRequest: currentRequest() }, reason);
}

function enterInput(request) {
  const scope = { owner: screens.at(-1) || null, request };
  inputScopes.push(scope);
  publishContext('inputRequestChanged');
  return () => {
    const index = inputScopes.indexOf(scope);
    if (index === -1) return;
    inputScopes.splice(index, 1);
    publishContext('inputRequestChanged');
  };
}

async function withInput(request, read) {
  const leave = enterInput(request);
  try { return await read(); } finally { leave(); }
}

function refreshGame(reason = 'gameChanged') {
  if (!readGame) return;
  const next = readGame();
  if (JSON.stringify(next) !== JSON.stringify(GameState.getSnapshot().game)) {
    runtimeState.publish({ game: next }, reason);
  }
}

function observeGame(reader) {
  readGame = reader;
  refreshGame('gameStarted');
  return () => {
    refreshGame('gameEnded');
    if (readGame === reader) {
      readGame = null;
      runtimeState.publish({ game: null }, 'gameExited');
    }
  };
}

function enterScreen(id) {
  refreshGame();
  const screen = { id };
  screens.push(screen);
  publishContext('screenChanged');
  return () => {
    const index = screens.indexOf(screen);
    if (index !== -1) screens.splice(index, 1);
    publishContext('screenChanged');
  };
}

async function observeAwait(value) {
  refreshGame();
  try { return await value; } finally { refreshGame(); }
}

function recordInput(key, stage) {
  refreshGame();
  const input = { key, stage, request: GameState.getSnapshot().inputRequest };
  runtimeState.publish({ input }, 'inputChanged');
  runtimeState.event(`input:${stage}`, input);
}

// Called only from the runtime's rejected-push branch, independently of audio.
function reportBlockedPush(movement, boxIndex) {
  refreshGame();
  const { game, screen } = GameState.getSnapshot();
  if (!game || screen?.id !== 'gameplay') return;
  const direction = ({ 1: { x: 0, y: -1 }, 2: { x: 0, y: 1 },
    3: { x: 1, y: 0 }, 4: { x: -1, y: 0 } })[movement];
  const box = game.board.boxes.find(item => item.index === boxIndex);
  if (!direction || !box) return;
  const x = box.x + direction.x * game.grid.objectSize;
  const y = box.y + direction.y * game.grid.objectSize;
  const wall = game.board.walls.find(item => item.x === x && item.y === y);
  const otherBox = game.board.boxes.find(item => item.index !== boxIndex && item.x === x && item.y === y);
  if (!wall && !otherBox) return;
  runtimeState.event('pushBlocked', { level: game.level, box, direction,
    obstacle: { x, y, kind: wall ? 'wall' : 'box' } });
}

return { enterInput, withInput, refreshGame, observeGame, enterScreen, observeAwait, recordInput, reportBlockedPush };
}

const defaultBridge = createRuntimeBridge({ api: GameState, ...runtimeState });
export const { enterInput, withInput, refreshGame, observeGame, enterScreen, observeAwait, recordInput, reportBlockedPush } = defaultBridge;

export function boardSnapshot(level, player, steps, lives, sound, arrays, portal, nextLevel, undoPosition) {
  const { Cajas, Paredes, Vacios, Huecos, Cantidades } = arrays;
  const coordinates = (data, count) => data[level].slice(0, count).map(([x, y]) => ({ x, y }));
  const counts = Cantidades[level];
  const targets = coordinates(Huecos, counts[3]);
  const boxes = coordinates(Cajas, counts[0]).map((box, index) => ({ ...box, index,
    onTarget: targets.some(target => target.x === box.x && target.y === box.y) }));
  return { level, nextLevel, player, steps, lives, sound: !!sound, undoAvailable: undoPosition > 1,
    grid: { cols: 80, rows: 63, cellSize: 14, objectSize: 2 },
    board: { boxes, targets: targets.map(target => ({ ...target,
      covered: boxes.some(box => box.x === target.x && box.y === target.y) })),
    walls: coordinates(Paredes, counts[1]), gaps: coordinates(Vacios, counts[2]) }, portal };
}
