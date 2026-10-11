import test from 'node:test';
import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { mkdtemp, writeFile, readFile, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { pathToFileURL } from 'node:url';
import { compileSessionRuntime } from '../plugins/session-runtime.js';
import { createGameSession } from '../src/runtime/createGameSession.js';
import { GameState } from '../src/state/gameState.js';
import { createInputRouter } from '../src/inspector/inputRouter.js';
import { wallBounds, reachableBounds, fitBoard } from '../src/presentation/boardFraming.js';

const { parse } = createRequire(import.meta.resolve('eslint'))('espree');
const directory = await mkdtemp(join(tmpdir(), 'pushbox-sessions-'));
const compiled = await compileSessionRuntime(new URL('../', import.meta.url).pathname,
  source => parse(source, { ecmaVersion: 'latest', sourceType: 'module' }));
const file = join(directory, 'runtime.mjs');
await writeFile(file, compiled.code);
const { createRuntime } = await import(pathToFileURL(file));
await rm(directory, { recursive: true });

function session() {
  const writes = [];
  const context = { fillRect() {}, clearRect() {}, save() {}, restore() {}, beginPath() {},
    rect() {}, clip() {}, fillText(char) { writes.push(char); } };
  const canvas = { getContext: () => context };
  let time = 0;
  const audioFactory = store => {
    let muted = true;
    store.publish({ audio: { muted } }, 'audioChanged');
    return { play() {}, stop() {}, setWebMuted(value) { muted = value; store.publish({ audio: { muted } }, 'audioChanged'); } };
  };
  const game = createGameSession(canvas, createRuntime, {
    audioFactory, scheduleTranscript: callback => queueMicrotask(callback),
    clock: { requestFrame: callback => setTimeout(() => { time += 1000; callback(time); }, 0),
      cancelFrame: clearTimeout, now: () => time },
  });
  return { game, writes, canvas };
}
async function waitFor(condition) {
  for (let attempts = 0; attempts < 400; attempts++) {
    if (condition()) return;
    await new Promise(resolve => setTimeout(resolve, 5));
  }
  assert.fail('Runtime did not reach the expected state');
}
const waiting = game => game.state.getSnapshot().inputRequest?.consumer === 'ControlDeMovimiento'
  && game.state.getSnapshot().input?.stage === 'waiting';

test('all five original levels produce finite, visible mobile framing', async () => {
  for (const startLevel of [1, 2, 3, 4, 5]) {
    const { game } = session();
    const completed = game.start({ startLevel, skipIntro: true, skipLore: true });
    try {
      await waitFor(() => waiting(game));
      const bounds = wallBounds(game.state.getSnapshot().game);
      assert.ok(bounds, `Level ${startLevel} has wall bounds`);
      assert.ok(Object.values(bounds).every(Number.isFinite));
      const fitted = fitBoard(bounds, 352, 406);
      assert.ok(fitted.width > 0 && fitted.height > 0);
      const snapshot = game.state.getSnapshot().game;
      const { matrix } = JSON.parse(await readFile(new URL(`../pushbox_modules/maps_json/mapa0${startLevel}.json`, import.meta.url)));
      const reachable = reachableBounds(snapshot, matrix);
      assert.ok(reachable && Object.values(reachable).every(Number.isFinite));
      if (startLevel === 3) {
        assert.equal(snapshot.board.gaps.length, 117);
        const withoutPaving = reachableBounds({ ...snapshot, board: { ...snapshot.board, boxes: [] } }, matrix);
        assert.ok(withoutPaving.width > 0 && withoutPaving.height > 0);
        assert.ok(reachable.width >= withoutPaving.width && reachable.height >= withoutPaving.height);
      }
    } finally {
      game.dispose(); await completed;
    }
  }
});

test('three original runtimes isolate input, console, board state, audio and pause scopes', async t => {
  const defaultBefore = GameState.getSnapshot();
  const previews = [session(), session(), session()];
  const completed = previews.map(({ game }) => game.start());
  t.after(async () => { previews.forEach(({ game }) => game.dispose()); await Promise.all(completed); });
  await waitFor(() => previews.every(({ game }) => waiting(game)));
  const [first, second, third] = previews.map(preview => preview.game);
  assert.ok(previews.every(preview => preview.writes.includes('╔')), 'Original player glyph was rendered');
  assert.notEqual(first.console.canvas, second.console.canvas);
  const secondBefore = second.state.getSnapshot(), thirdBefore = third.state.getSnapshot();
  first.sendInput('w');
  await waitFor(() => first.state.getSnapshot().game?.steps === 1 && waiting(first));
  assert.deepEqual(first.state.getSnapshot().game.player, { x: 36, y: 32 });
  assert.deepEqual(second.state.getSnapshot().game, secondBefore.game);
  assert.deepEqual(third.state.getSnapshot().game, thirdBefore.game);
  const firstLine = first.state.getSnapshot().console.lines[0];
  second.console.SetCursorPosition(0, 0); second.console.Write('TEST');
  await waitFor(() => second.state.getSnapshot().console.lines[0].startsWith('TEST'));
  assert.equal(first.state.getSnapshot().console.lines[0], firstLine);
  first.audio.setWebMuted(false);
  assert.equal(second.state.getSnapshot().audio.muted, true);
  first.sendInput('p');
  await waitFor(() => first.state.getSnapshot().inputRequest?.consumer === 'InterfazPausa');
  assert.equal(second.state.getSnapshot().inputRequest.consumer, 'ControlDeMovimiento');
  second.sendInput('w');
  await waitFor(() => second.state.getSnapshot().game?.steps === 1 && waiting(second));
  assert.equal(first.state.getSnapshot().game.steps, 1);
  assert.equal(GameState.getSnapshot(), defaultBefore, 'Legacy singleton must not be modified');
});

test('linked inputs fan out exactly once; unlinking preserves independent progression', async t => {
  const previews = [session(), session(), session()];
  const done = previews.map(({ game }) => game.start());
  t.after(async () => { previews.forEach(({ game }) => game.dispose()); await Promise.all(done); });
  await waitFor(() => previews.every(({ game }) => waiting(game)));
  const router = createInputRouter();
  previews.forEach(({ game }, i) => router.register(i, key => game.sendInput(key)));
  router.setLinked(true); router.send(1, 'w');
  await waitFor(() => previews.every(({ game }) => game.state.getSnapshot().game.steps === 1 && waiting(game)));
  router.setLinked(false); router.send(2, 's');
  await waitFor(() => previews[2].game.state.getSnapshot().game.steps === 2 && waiting(previews[2].game));
  assert.deepEqual(previews.map(({ game }) => game.state.getSnapshot().game.steps), [1, 1, 2]);
  const old = previews[2].game;
  old.dispose(); await done[2];
  assert.equal(old.state.getSnapshot().game, null);
  assert.throws(() => old.sendInput('w'), /stopped/);
  const replacement = session();
  const replacementDone = replacement.game.start();
  t.after(async () => { replacement.game.dispose(); await replacementDone; });
  await waitFor(() => waiting(replacement.game));
  assert.equal(replacement.game.state.getSnapshot().game.steps, 0);
  assert.equal(previews[0].game.state.getSnapshot().game.steps, 1);
});
