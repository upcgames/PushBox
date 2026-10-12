import { writePlayerIdentity } from '../presentation/playerIdentity.js';
import { bindSoundReference, handleAudioInput as handleAudioKey } from '../audio/audioState.js';
import { runtimeState, GameState } from './gameState.js';

export function createRuntimeBridge(store) {
const GameState = store.api, runtimeState = store;
let readGame = null;
const screens = [];
const inputScopes = [];
const playerAnimations = [];

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

async function withInput(request, read, target) {
  const native = request.kind === 'text' && target ? GameState.readNativeText(request, target) : undefined;
  const leave = enterInput(native === undefined ? request : { ...request, native: true });
  try { return await (native === undefined ? read() : native); } finally { leave(); }
}

async function readPauseKey(read, option) {
  const key = await read();
  if (key === 'Resume') {
    // One explicit UI command selects the original Resume action, including
    // linked Inspector sessions; no W/S navigation sequence is synthesized.
    option.v = 1;
    return 'E';
  }
  return key;
}

// Native input replaces these prompts. Preserve their console writes without
// running an invisible typewriter or its audio; other contexts keep original timing.
async function presentPrompt(consumer, type, write) {
  return GameState.hasNativeTextReader(consumer) ? write() : type();
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
  runtimeState.publish({ playerAnimation: null }, 'playerAnimationChanged');
  refreshGame('gameStarted');
  return () => {
    refreshGame('gameEnded');
    if (readGame === reader) {
      readGame = null;
      runtimeState.publish({ game: null, playerDrawing: null, playerAnimation: null, trollActive: false }, 'gameExited');
    }
  };
}

function enterScreen(id, context = {}) {
  refreshGame();
  const level = typeof context.level === 'object' && context.level !== null ? context.level.v : context.level;
  const screen = { id, ...(Number.isInteger(level) ? { level } : {}) };
  screens.push(screen);
  publishContext('screenChanged');
  return () => {
    const index = screens.indexOf(screen);
    if (index === -1) return;
    runtimeState.event('screenExited', { screen, ...context.exit?.() });
    screens.splice(index, 1);
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
  const locked = game.level === 5 && box.index >= 10 && game.portal.active;
  const event = { level: game.level, player: game.player, box, direction,
    obstacle: wall || otherBox ? { x, y, kind: wall ? 'wall' : 'box' }
      : locked ? { x: box.x, y: box.y, kind: 'locked' } : null };
  if (wall || otherBox) runtimeState.event('pushBlocked', event);
  runtimeState.event('movementBlocked', event);
}

// This runs only after the original runtime rejects a walk, regardless of mute.
function reportBlockedMove(movement) {
  refreshGame();
  const { game, screen } = GameState.getSnapshot();
  if (!game || screen?.id !== 'gameplay') return;
  const direction = ({ 1: { x: 0, y: -1 }, 2: { x: 0, y: 1 },
    3: { x: 1, y: 0 }, 4: { x: -1, y: 0 } })[movement];
  if (!direction) return;
  const x = game.player.x + direction.x * game.grid.objectSize;
  const y = game.player.y + direction.y * game.grid.objectSize;
  const wall = game.board.walls.find(item => item.x === x && item.y === y);
  runtimeState.event('movementBlocked', { level: game.level, player: game.player, direction,
    obstacle: wall ? { x, y, kind: 'wall' } : null });
}

// Observe original routine boundaries, including the complete undo restoration.
// Terminal effects keep ownership until a fresh attempt draws Bobby again.
function enterPlayerAnimation(name) {
  const scope = { name };
  playerAnimations.push(scope);
  runtimeState.publish({ playerAnimation: name }, 'playerAnimationChanged');
  return () => {
    const index = playerAnimations.indexOf(scope);
    if (index === -1) return;
    playerAnimations.splice(index, 1);
    const terminal = name === 'PintarMuerte' || name === 'Teletransporte';
    runtimeState.publish({ playerAnimation: playerAnimations.at(-1)?.name || (terminal ? name : null) }, 'playerAnimationChanged');
  };
}

function reportPlayerDraw(level, x, y, background, foreground) {
  const playerDrawing = { level, x, y, background, foreground };
  const previous = GameState.getSnapshot().playerDrawing;
  const playerAnimation = playerAnimations.at(-1)?.name || null;
  if (JSON.stringify(playerDrawing) !== JSON.stringify(previous) || GameState.getSnapshot().playerAnimation !== playerAnimation) {
    runtimeState.publish({ playerDrawing, playerAnimation }, 'playerDrawn');
  }
}

function bindPlayerIdentity(counts) { writePlayerIdentity(counts, GameState.getSnapshot().playerNames); }

function bindSound(reference) { bindSoundReference(store, reference); }
function handleAudioInput(key) { return handleAudioKey(store, key); }
return { enterInput, withInput, readPauseKey, presentPrompt, refreshGame, observeGame, enterScreen, observeAwait, recordInput, reportBlockedPush, reportBlockedMove, reportPlayerDraw, enterPlayerAnimation, bindPlayerIdentity, bindSound, handleAudioInput, inputBlocked: () => GameState.getSnapshot().winnerContinueBlocked, inputConsumer: () => GameState.getSnapshot().inputRequest?.consumer };
}

const defaultBridge = createRuntimeBridge({ api: GameState, ...runtimeState });
export const { enterInput, withInput, readPauseKey, presentPrompt, refreshGame, observeGame, enterScreen, observeAwait, recordInput, reportBlockedPush, reportBlockedMove, reportPlayerDraw, enterPlayerAnimation, bindPlayerIdentity, bindSound, handleAudioInput, inputBlocked, inputConsumer } = defaultBridge;

export function boardSnapshot(level, player, steps, lives, sound, arrays, portal, nextLevel, undoPosition) {
  const { Cajas, Paredes, Vacios, Huecos, Cantidades } = arrays;
  const coordinates = (data, count) => data[level].slice(0, count).map(([x, y]) => ({ x, y }));
  const counts = Cantidades[level];
  const targets = coordinates(Huecos, counts[3]);
  const boxes = coordinates(Cajas, counts[0]).map((box, index) => ({ ...box, index,
    onTarget: targets.some(target => target.x === box.x && target.y === box.y) }));
  return { level, nextLevel, player, steps, lives, sound: !!sound, undoAvailable: undoPosition > 1, undoDepth: undoPosition - 1,
    grid: { cols: 80, rows: 63, cellSize: 14, objectSize: 2,
      walkBounds: { minX: 0, maxX: 79, minY: 0, maxY: 59 } },
    board: { boxes, targets: targets.map(target => ({ ...target,
      covered: boxes.some(box => box.x === target.x && box.y === target.y) })),
    walls: coordinates(Paredes, counts[1]), gaps: coordinates(Vacios, counts[2]) }, portal };
}
