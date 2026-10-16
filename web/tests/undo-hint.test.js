import test from 'node:test';
import assert from 'node:assert/strict';
import { createGameState } from '../src/state/gameState.js';
import { reachablePlayerPositions, boxHasLegalPush, recoverableBoxPositions, mountUndoHint } from '../src/presentation/undoHint.js';
import { createSeenProgress } from '../src/state/seenProgress.js';
import { mountRewindDiscovery } from '../src/presentation/rewindDiscovery.js';

function board(patch = {}) {
  return { level: 1, nextLevel: 1, steps: 0, undoDepth: 0, undoAvailable: false,
    player: { x: 1, y: 3 }, portal: { active: false },
    grid: { objectSize: 1, walkBounds: { minX: 0, maxX: 4, minY: 0, maxY: 4 } },
    board: { boxes: [{ index: 0, x: 1, y: 2, onTarget: false }], walls: [{ x: 0, y: 1 }, { x: 1, y: 0 }], gaps: [] }, ...patch };
}
function pushed(patch = {}) {
  const original = board();
  return board({ player: { x: 1, y: 2 }, steps: 1, undoDepth: 1, undoAvailable: true,
    board: { ...original.board, boxes: [{ index: 0, x: 1, y: 1, onTarget: false }] }, ...patch });
}
function fixture() {
  const store = createGameState(() => { throw new Error('Hints never send input'); });
  let enabled = true;
  const hint = mountUndoHint(store.api, { enabled: () => enabled });
  function sample(game, patch = {}) {
    store.publish({ screen: { id: 'gameplay' }, inputRequest: { kind: 'key', consumer: 'ControlDeMovimiento' }, playerAnimation: null, game, ...patch });
    store.event('input:waiting', { request: store.api.getSnapshot().inputRequest, key: null });
  }
  return { store, hint, sample, enable: value => { enabled = value; hint.refresh(); } };
}

function wallStrip(x = 2, y = 3, steps = 0) {
  return board({ steps, undoDepth: Math.min(steps, 5), undoAvailable: steps > 0,
    player: { x: 2, y: y + 1 },
    grid: { objectSize: 1, walkBounds: { minX: 0, maxX: 6, minY: 0, maxY: 6 } },
    board: { boxes: [{ index: 0, x, y, onTarget: false }],
      walls: Array.from({ length: 7 }, (_, x) => ({ x, y: 1 })),
      targets: [{ x: 3, y: 5 }], gaps: [] } });
}

test('rewind is discovered by a hint and learned only when an actual undo recovers the hinted caja', () => {
  const saved = new Map(), storage = { getItem: key => saved.get(key), setItem: (key, value) => saved.set(key, value) };
  const progress = createSeenProgress({ storage });
  const view = fixture(), discovery = mountRewindDiscovery(view.store.api, { progress });
  try {
    view.sample(wallStrip());
    assert.equal(view.store.api.getSnapshot().rewindDiscovery.visible, false);
    view.sample(wallStrip(2, 2, 1));
    assert.equal(view.store.api.getSnapshot().rewindDiscovery.visible, true);
    assert.equal(progress.has('rewind:recovered'), false);
    view.sample(wallStrip(3, 2, 2));
    view.sample({ ...wallStrip(2, 2, 5), undoDepth: 1 });
    assert.equal(progress.has('rewind:recovered'), false, 'Undoing a sideways push has not recovered the caja');
    view.sample({ ...wallStrip(2, 3, 8), undoDepth: 0 });
    assert.equal(progress.has('rewind:recovered'), true);
    assert.equal(view.store.api.getSnapshot().undoHint, false);
    assert.equal(view.store.api.getSnapshot().rewindDiscovery.visible, true);
    assert.deepEqual(progress.getSnapshot(), { 'rewind:unlocked': true, 'rewind:recovered': true }, 'Unlock and successful use are separate milestones');
    view.sample(wallStrip(), { game: null, screen: { id: 'launcher' }, inputRequest: null });
    view.sample(wallStrip());
    assert.equal(view.store.api.getSnapshot().rewindDiscovery.visible, true, 'New playthrough retains learning');
    const reloaded = createSeenProgress({ storage });
    assert.equal(reloaded.has('rewind:recovered'), true);
  } finally { discovery.dispose(); view.hint.dispose(); }
});

test('reset, pause, failed rewind, expired history, errors and unseen traps cannot earn recovery', () => {
  for (const action of ['reset', 'pause', 'failed', 'expired', 'error', 'unseen']) {
    const progress = createSeenProgress({ storage: null });
    const view = fixture(), discovery = mountRewindDiscovery(view.store.api, { progress });
    try {
      view.sample(wallStrip());
      if (action === 'unseen') {
        view.sample({ ...wallStrip(2, 2, 1), undoAffordableDepth: 0 });
        view.sample({ ...wallStrip(2, 3, 4), undoDepth: 0 });
      } else {
        view.sample(wallStrip(2, 2, 1));
        if (action === 'reset') view.sample(wallStrip());
        if (action === 'pause') view.sample(wallStrip(2, 2, 1), { screen: { id: 'InterfazPausa' } });
        if (action === 'failed') view.sample(wallStrip(2, 2, 1));
        if (action === 'expired') {
          for (let steps = 2; steps <= 7; steps++) view.sample(wallStrip(2, 2, steps));
          view.sample({ ...wallStrip(2, 3, 10), undoDepth: 4 });
        }
        if (action === 'error') { view.store.event('runtimeError', {}); view.sample(wallStrip()); }
      }
      assert.equal(progress.has('rewind:recovered'), false, action);
    } finally { discovery.dispose(); view.hint.dispose(); }
  }
});

test('movable wall-strip caja has no recovery route; sideways pushes do not restart the undo window', () => {
  const before = wallStrip(), lost = wallStrip(2, 2, 1), view = fixture();
  assert.equal(boxHasLegalPush(lost, lost.board.boxes[0]), true);
  assert.ok(recoverableBoxPositions(before).has('2,3'));
  assert.equal(recoverableBoxPositions(lost).has('2,2'), false);
  view.sample(before); view.sample(lost);
  assert.equal(view.store.api.getSnapshot().undoHint, true);
  for (let steps = 2; steps <= 6; steps++) {
    view.sample(wallStrip(steps % 2 ? 2 : 3, 2, steps));
    assert.equal(view.store.api.getSnapshot().undoHint, steps <= 3);
  }
  view.sample({ ...wallStrip(2, 2, 9), undoDepth: 4 });
  assert.equal(view.store.api.getSnapshot().undoHint, false, 'Expired offending push cannot be revived by sliding');
  view.hint.dispose();
});

test('undoing sideways pushes preserves the warning until the original recoverable position returns', () => {
  const view = fixture(); view.sample(wallStrip()); view.sample(wallStrip(2, 2, 1));
  view.sample(wallStrip(3, 2, 2));
  view.sample({ ...wallStrip(2, 2, 5), undoDepth: 1 });
  assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample({ ...wallStrip(2, 3, 8), undoDepth: 0 });
  assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.hint.dispose();
});

test('reverse routes retain covered huecos, ignore temporary cajas and allow future bridges', () => {
  const game = wallStrip();
  game.board.targets[0].covered = true;
  game.board.boxes.push({ index: 1, x: 2, y: 4 });
  game.board.gaps.push({ x: 2, y: 4 });
  assert.ok(recoverableBoxPositions(game).has('2,3'));
  const view = fixture(); view.sample(wallStrip(2, 4)); view.sample(wallStrip(2, 3, 1));
  assert.equal(view.store.api.getSnapshot().undoHint, false, 'Recoverable push does not hint');
  view.hint.dispose();
});

test('a caja blocked by another movable caja does not hint before the lower caja frees it', () => {
  const view = fixture();
  const before = board({ player: { x: 2, y: 0 }, board: {
    walls: [{ x: 1, y: 2 }, { x: 3, y: 2 }], gaps: [],
    targets: [{ x: 2, y: 1 }, { x: 4, y: 3 }],
    boxes: [{ index: 0, x: 2, y: 1, onTarget: true }, { index: 1, x: 2, y: 3, onTarget: false }],
  } });
  const after = { ...before, player: { x: 2, y: 1 }, steps: 1, undoDepth: 1, undoAvailable: true,
    board: { ...before.board, boxes: [{ index: 0, x: 2, y: 2, onTarget: false }, before.board.boxes[1]] } };
  try {
    assert.equal(boxHasLegalPush(after, after.board.boxes[0]), false, 'Upper caja cannot be pushed yet');
    assert.equal(boxHasLegalPush(after, after.board.boxes[1]), true, 'Lower caja can move aside');
    assert.ok(recoverableBoxPositions(after).has('2,2'));
    view.sample(before); view.sample(after);
    assert.equal(view.store.api.getSnapshot().undoHint, false);
    const freed = { ...after, player: { x: 2, y: 3 }, steps: 2, undoDepth: 2,
      board: { ...after.board, boxes: [after.board.boxes[0], { ...after.board.boxes[1], x: 3 }] } };
    assert.equal(boxHasLegalPush(freed, freed.board.boxes[0]), true);
    view.sample(freed);
    assert.equal(view.store.api.getSnapshot().undoHint, false);
  } finally { view.hint.dispose(); }
});

test('both intended bridges are useful endpoints even without a route to a hueco', () => {
  for (const gap of [{ x: 42, y: 34 }, { x: 36, y: 38 }]) {
    const game = board({ level: 3,
      grid: { objectSize: 2, walkBounds: { minX: 0, maxX: 79, minY: 0, maxY: 59 } },
      board: { walls: [], boxes: [], targets: [], gaps: [gap] } });
    assert.ok(recoverableBoxPositions(game).has(`${gap.x},${gap.y - 2}`));
    game.board.gaps = [];
    assert.equal(recoverableBoxPositions(game).size, 0, 'Consumed bridge stops being a useful sacrifice endpoint');
  }
});

test('legal pushes need reachable support and destination clearance; unsafe gaps cannot be walked through', () => {
  const trapped = pushed();
  assert.equal(boxHasLegalPush(trapped, trapped.board.boxes[0]), false);
  const initial = board();
  assert.equal(boxHasLegalPush(initial, initial.board.boxes[0]), true);
  const isolated = board({ player: { x: 0, y: 0 }, board: { boxes: [{ index: 0, x: 2, y: 2 }], walls: [], gaps: [{ x: 0, y: 1 }, { x: 1, y: 0 }] } });
  assert.deepEqual([...reachablePlayerPositions(isolated)], ['0,0']);
  assert.equal(boxHasLegalPush(isolated, isolated.board.boxes[0]), false, 'Free destinations are insufficient without reachable support');
  const bridge = board({ board: { ...initial.board, gaps: [{ x: 1, y: 1 }] } });
  assert.equal(boxHasLegalPush(bridge, bridge.board.boxes[0]), true, 'Pushing into a gap is a legal bridge action');
  const outside = board({ player: { x: 1, y: 1 }, board: { walls: [], gaps: [], boxes: [{ index: 0, x: 1, y: 0 }] } });
  assert.equal(boxHasLegalPush(outside, outside.board.boxes[0]), true, 'Do not add bounds restrictions absent from canonical push rules');
  const blocked = board({ player: { x: 1, y: 2 }, board: { walls: [{ x: 2, y: 1 }, { x: 2, y: 3 }], gaps: [], boxes: [{ index: 0, x: 2, y: 2 }, { index: 1, x: 3, y: 2 }] } });
  assert.equal(boxHasLegalPush(blocked, blocked.board.boxes[0]), false, 'Other cajas block push destinations');
});

test('first push starts hint; walks/failed uses preserve it and successful undo clears it only after recovery', () => {
  const view = fixture(); view.sample(board());
  assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample(pushed()); assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample(pushed()); assert.equal(view.store.api.getSnapshot().undoHint, true, 'Failed input does not clear the hint');
  const walked = pushed({ player: { x: 2, y: 2 }, steps: 2, undoDepth: 2 });
  view.sample(walked); assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample(pushed({ steps: 5 })); assert.equal(view.store.api.getSnapshot().undoHint, true, 'Undoing a walk does not recover the caja');
  view.sample(board({ steps: 8 })); assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.hint.dispose();
});

test('targets, removals without a bridge fact and level-five hardening cases do not hint', () => {
  for (const scenario of [
    pushed({ board: { ...pushed().board, boxes: [{ index: 0, x: 1, y: 1, onTarget: true }] } }),
    pushed({ board: { ...pushed().board, boxes: [], gaps: [] } }),
    pushed({ level: 5, nextLevel: 5, portal: { active: true } }),
    pushed({ level: 5, nextLevel: 5, board: { ...pushed().board, boxes: [{ index: 10, x: 1, y: 1, onTarget: false }] } }),
  ]) {
    const view = fixture();
    const initial = board({ level: scenario.level, nextLevel: scenario.level,
      board: { ...board().board, boxes: [{ ...board().board.boxes[0], index: scenario.board.boxes[0]?.index ?? 0 }] } });
    view.sample(initial); view.sample(scenario);
    assert.equal(view.store.api.getSnapshot().undoHint, false);
    view.hint.dispose();
  }
});

test('pause hides but preserves hints; retry, scene exit, errors and disposal clear state; desktop/session scopes stay isolated', () => {
  const view = fixture(), other = fixture(); view.sample(board()); view.sample(pushed());
  view.store.publish({ screen: { id: 'InterfazPausa' } }); assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample(pushed()); assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.store.publish({ playerAnimation: 'Regresar' }); assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample(pushed()); assert.equal(view.store.api.getSnapshot().undoHint, true);
  assert.equal(other.store.api.getSnapshot().undoHint, false);
  view.sample(board()); assert.equal(view.store.api.getSnapshot().undoHint, false, 'Retry resets the attempt');
  view.sample(pushed()); view.store.event('runtimeError', {}); assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample(board()); view.sample(pushed()); view.store.publish({ game: null }); assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample(board()); view.sample(pushed()); view.hint.dispose(); assert.equal(view.store.api.getSnapshot().undoHint, false);
  other.enable(false); other.sample(board()); other.sample(pushed()); assert.equal(other.store.api.getSnapshot().undoHint, false);
  other.hint.dispose();
});


test('push hints still trigger after the original five-record undo history fills', () => {
  const view = fixture();
  view.sample(board({ steps: 10, undoDepth: 5, undoAvailable: true }));
  view.sample(pushed({ steps: 11, undoDepth: 5 }));
  assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.hint.dispose();
});

test('hint covers at most three undo presses, ignoring failed moves and pause; later undo can restore eligibility', () => {
  const view = fixture(); view.sample(board()); view.sample(pushed());
  view.sample(pushed()); assert.equal(view.store.api.getSnapshot().undoHint, true, 'Failed move does not age the hint');
  view.store.publish({ screen: { id: 'InterfazPausa' } });
  view.sample(pushed()); assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample(pushed({ steps: 2, undoDepth: 2, player: { x: 2, y: 2 } }));
  assert.equal(view.store.api.getSnapshot().undoHint, true, 'Two undo presses can recover the push');
  view.sample(pushed({ steps: 3, undoDepth: 3, player: { x: 2, y: 3 } }));
  assert.equal(view.store.api.getSnapshot().undoHint, true, 'Three undo presses can recover the push');
  view.sample(pushed({ steps: 4, undoDepth: 4, player: { x: 3, y: 3 } }));
  assert.equal(view.store.api.getSnapshot().undoHint, false, 'Four undo presses is beyond hint horizon');
  view.sample(pushed({ steps: 7, undoDepth: 3, player: { x: 2, y: 3 } }));
  assert.equal(view.store.api.getSnapshot().undoHint, true, 'Undoing a later walk brings recovery within three');
  view.hint.dispose();
});

test('expired push records cannot revive hints after the original history rolls over', () => {
  const view = fixture(); view.sample(board()); view.sample(pushed());
  for (let steps = 2; steps <= 6; steps++) view.sample(pushed({ steps, undoDepth: Math.min(steps, 5) }));
  assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample(pushed({ steps: 9, undoDepth: 4 }));
  view.sample(pushed({ steps: 12, undoDepth: 3 }));
  assert.equal(view.store.api.getSnapshot().undoHint, false, 'The offending push has left actual undo history');
  view.hint.dispose();
});

function sacrifice(level, caja, vacio) {
  const before = board({ level, nextLevel: level, player: { x: caja.x - (vacio.x - caja.x), y: caja.y - (vacio.y - caja.y) },
    board: { boxes: [{ index: 0, ...caja, onTarget: false }, { index: 1, x: 0, y: 4, onTarget: false }], walls: [], gaps: [vacio] } });
  const after = { ...before, player: caja, steps: 1, undoDepth: 1, undoAvailable: true,
    board: { ...before.board, boxes: [{ index: 0, x: 0, y: 4, onTarget: false }], gaps: [] } };
  return { before, after };
}

test('bridge sacrifices hint except for the two intended level-three destinations; created bridges still stay walkable', () => {
  for (const [level, caja, vacio, expected] of [
    [3, { x: 42, y: 32 }, { x: 42, y: 34 }, false],
    [3, { x: 38, y: 38 }, { x: 36, y: 38 }, false],
    [3, { x: 42, y: 36 }, { x: 42, y: 34 }, false],
    [3, { x: 34, y: 28 }, { x: 34, y: 26 }, true],
    [2, { x: 1, y: 2 }, { x: 1, y: 1 }, true],
    [4, { x: 1, y: 2 }, { x: 1, y: 1 }, true],
  ]) {
    const view = fixture(), { before, after } = sacrifice(level, caja, vacio);
    view.sample(before); view.sample(after);
    assert.equal(view.store.api.getSnapshot().undoHint, expected, `Level ${level}: ${vacio.x},${vacio.y}`);
    if (expected && level === 2) assert.ok(reachablePlayerPositions(after).has('1,1'), 'Bad sacrifice does not change actual bridge walkability');
    view.hint.dispose();
  }
});

test('sacrifice hints use the same three-undo horizon and clear when the original caja/gap are restored', () => {
  const view = fixture(), { before, after } = sacrifice(2, { x: 1, y: 2 }, { x: 1, y: 1 });
  const progress = createSeenProgress({ storage: null });
  const discovery = mountRewindDiscovery(view.store.api, { progress });
  view.sample(before); view.sample(after); assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample(after); assert.equal(view.store.api.getSnapshot().undoHint, true, 'Failed use does not age a sacrifice');
  view.store.publish({ screen: { id: 'InterfazPausa' } });
  view.sample(after); assert.equal(view.store.api.getSnapshot().undoHint, true, 'Pause does not age a sacrifice');
  view.sample({ ...after, steps: 2, undoDepth: 2 });
  view.sample({ ...after, steps: 3, undoDepth: 3 }); assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample({ ...after, steps: 4, undoDepth: 4 }); assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample({ ...after, steps: 7, undoDepth: 3 }); assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample({ ...after, steps: 10, undoDepth: 2 });
  view.sample({ ...after, steps: 13, undoDepth: 1 });
  view.sample({ ...before, steps: 16 }); assert.equal(view.store.api.getSnapshot().undoHint, false, 'Undo restores consumed caja and vacío');
  assert.equal(progress.has('rewind:recovered'), true, 'Undoing a hinted sacrifice also demonstrates recovery');
  discovery.dispose(); view.hint.dispose();
});

test('sacrifice markers expire with actual history and clear on reset/disposal', () => {
  const view = fixture(), { before, after } = sacrifice(4, { x: 1, y: 2 }, { x: 1, y: 1 });
  view.sample(before); view.sample(after);
  for (let steps = 2; steps <= 6; steps++) view.sample({ ...after, steps, undoDepth: Math.min(steps, 5) });
  view.sample({ ...after, steps: 9, undoDepth: 4 }); view.sample({ ...after, steps: 12, undoDepth: 3 });
  assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample(before); view.sample(after); assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.store.publish({ game: null }); assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.sample(before); view.sample(after); view.hint.dispose(); assert.equal(view.store.api.getSnapshot().undoHint, false);
});

test('recovery hints respect canonical affordability as well as the three-undo horizon', () => {
  const view = fixture(); view.sample(board());
  view.sample(pushed({ undoAffordableDepth: 1 }));
  assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample(pushed({ steps: 2, undoDepth: 2, undoAffordableDepth: 1 }));
  assert.equal(view.store.api.getSnapshot().undoHint, false, 'Two undos cannot be recovered with budget for one');
  view.sample(pushed({ steps: 2, undoDepth: 2, undoAffordableDepth: 2 }));
  assert.equal(view.store.api.getSnapshot().undoHint, true);
  view.sample(pushed({ steps: 2, undoDepth: 2, undoAvailable: false, undoAffordableDepth: 0 }));
  assert.equal(view.store.api.getSnapshot().undoHint, false);
  view.hint.dispose();
});
