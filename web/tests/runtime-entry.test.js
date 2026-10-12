import test from 'node:test';
import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { mkdtemp, writeFile, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { pathToFileURL } from 'node:url';
import { compileSessionRuntime } from '../plugins/session-runtime.js';
import { createGameSession } from '../src/runtime/createGameSession.js';
import { loreLevel } from '../src/presentation/loreHandoff.js';
import { startPointSettings } from '../src/shell/startPoints.js';

const { parse } = createRequire(import.meta.resolve('eslint'))('espree');
const directory = await mkdtemp(join(tmpdir(), 'pushbox-entry-'));
const compiled = await compileSessionRuntime(new URL('../', import.meta.url).pathname,
  source => parse(source, { ecmaVersion: 'latest', sourceType: 'module' }));
const file = join(directory, 'runtime.mjs');
await writeFile(file, compiled.code);
const { createRuntime } = await import(pathToFileURL(file));
await rm(directory, { recursive: true });

function session(runtimeFactory = createRuntime) {
  const context = { fillRect() {}, clearRect() {}, save() {}, restore() {}, beginPath() {},
    rect() {}, clip() {}, fillText() {} };
  let time = 0;
  return createGameSession({ getContext: () => context }, runtimeFactory, {
    audioFactory: () => ({ play() {}, stop() {} }),
    scheduleTranscript: callback => setTimeout(callback, 0),
    clock: { requestFrame: callback => setTimeout(() => { time += 1000; callback(time); }, 0),
      cancelFrame: clearTimeout, now: () => time },
  });
}
async function waitFor(condition) {
  for (let i = 0; i < 2000; i++) {
    if (condition()) return;
    await new Promise(resolve => setTimeout(resolve, 5));
  }
  assert.fail('Original runtime did not reach the expected entry or continuation');
}
const waiting = (game, consumer, kind) => {
  const state = game.state.getSnapshot();
  return state.inputRequest?.consumer === consumer && state.inputRequest.kind === kind
    && state.input?.stage === 'waiting';
};

test('Menu enters the original title directly, then continues through instructions and level-one lore', async () => {
  const game = session();
  const screens = [];
  const off = game.state.select(state => state.screen, screen => screens.push(screen));
  const done = game.start(startPointSettings('menu', false));
  try {
    await waitFor(() => waiting(game, 'MenuPrincipal', 'confirmation'));
    assert.equal(screens.some(screen => screen?.id === 'main'), false, 'No startup main or simulated inputs before Menu');
    game.sendInput('E');
    await waitFor(() => waiting(game, 'MenuPrincipal', 'key'));
    game.sendInput('E');
    await waitFor(() => waiting(game, 'InterfazInstructions', 'confirmation'));
    game.sendInput('E');
    await waitFor(() => waiting(game, 'Lore', 'confirmation'));
    assert.equal(loreLevel(game.state.getSnapshot()), 1);
    game.sendInput('E');
    await waitFor(() => waiting(game, 'ControlDeMovimiento', 'key'));
    assert.equal(game.state.getSnapshot().game.level, 1);
  } finally { off(); game.dispose(); await done; }
});

test('Instructions enters directly and hands gameplay initialization back to original main', async () => {
  const game = session();
  const screens = [];
  const off = game.state.select(state => state.screen?.id, screen => screens.push(screen));
  const done = game.start(startPointSettings('instructions', true));
  try {
    await waitFor(() => waiting(game, 'InterfazInstructions', 'confirmation'));
    assert.equal(screens.includes('MenuPrincipal'), false);
    assert.equal(screens.includes('main'), false);
    game.sendInput('E');
    await waitFor(() => waiting(game, 'ControlDeMovimiento', 'key'));
    assert.equal(game.state.getSnapshot().game.level, 1);
  } finally { off(); game.dispose(); await done; }
});

test('Lore exposes its original level before its heading is painted', async () => {
  const game = session();
  let captured;
  const off = game.state.select(state => state.screen, screen => {
    if (screen?.id === 'Lore' && !captured) captured = game.state.getSnapshot();
  });
  const done = game.start(startPointSettings('5', false));
  try {
    await waitFor(() => waiting(game, 'Lore', 'confirmation'));
    assert.equal(loreLevel(captured), 5);
    assert.equal(captured.console.lines.some(line => /NIVEL\s+5/.test(line)), false);
  } finally { off(); game.dispose(); await done; }
});


test('mobile native identity reaches original congratulations initialization through the web bridge', async () => {
  let captured;
  const game = session(environment => {
    const original = environment.bridge.bindPlayerIdentity;
    environment.bridge.bindPlayerIdentity = counts => {
      original(counts); captured = counts.map(row => row?.slice());
    };
    return createRuntime(environment);
  });
  game.state.setPlayerNames(['José', 'Ñina']);
  const done = game.start(startPointSettings('6', true));
  try {
    await waitFor(() => !!captured);
    assert.equal(captured[8][0], '2');
    assert.equal(captured[8][1], 4); assert.equal(captured[8][2], 4);
    assert.deepEqual(captured[6].slice(0, 4), ['J', 'o', 's', -126]);
    assert.deepEqual(captured[7].slice(0, 4), [-91, 'i', 'n', 'a']);
  } finally { game.dispose(); await done; }
});

test('original winner changes names through native reads, then redraws and exits normally', async () => {
  const { createWinnerIdentity } = await import('../src/presentation/winnerIdentity.js');
  const { createPlayerProfile } = await import('../src/presentation/playerIdentity.js');
  let counts;
  const game = session(environment => {
    // Accelerate original text delays for this runtime integration check.
    environment.shims.Sleep = async () => {
      assert.notEqual(environment.console.drawScope, 'winner-prompts', 'Hidden mobile prompts must not run typing delays');
    };
    const play = environment.shims.PlaySound;
    environment.shims.PlaySound = (...args) => {
      assert.notEqual(environment.console.drawScope, 'winner-prompts', 'Hidden mobile prompts must not play typing sound');
      return play(...args);
    };
    const bind = environment.bridge.bindPlayerIdentity;
    environment.bridge.bindPlayerIdentity = value => { bind(value); counts = value; };
    return createRuntime(environment);
  });
  const paintedPrompts = [];
  game.console.setDrawScopeHidden('winner-prompts', true);
  game.console.ctx.fillText = character => {
    if (game.console.drawScope === 'winner-prompts') paintedPrompts.push(character);
  };
  const profile = createPlayerProfile({ storage: null });
  const flow = createWinnerIdentity({ profile, store: game.state });
  const stopReader = game.state.registerNativeTextReader(flow.read, flow.accepts);
  game.state.setPlayerNames(['Ana']);
  const done = game.start(startPointSettings('6', true));
  try {
    await waitFor(() => waiting(game, 'InterfazCongratulations', 'confirmation'));
    game.sendInput('E');
    await waitFor(() => waiting(game, 'InterfazCongratulations', 'key'));
    assert.ok(game.console.cells.flat().some(cell => cell?.scope === 'winner-prompts' && cell.char !== ' '));
    game.sendInput('K');
    await waitFor(() => flow.getSnapshot().visible);
    assert.equal(game.state.getSnapshot().inputRequest.native, true);
    flow.submit('José Ñina');
    await waitFor(() => counts[8][0] === '2' && counts[6][3] === -126 && counts[7][0] === -91);
    assert.deepEqual(profile.getNames(), ['José', 'Ñina']);
    assert.ok(paintedPrompts.length > 0);
    assert.ok(paintedPrompts.every(character => character === ' '), 'Mobile hides prompts while retaining canonical writes');
    await waitFor(() => waiting(game, 'InterfazCongratulations', 'confirmation'));
    game.sendInput('E');
    await waitFor(() => waiting(game, 'InterfazCongratulations', 'key'));
    game.sendInput('E');
    await waitFor(() => game.state.getSnapshot().screen?.id === 'InterfazCreditos');
    assert.equal(flow.getSnapshot().visible, false);
    assert.equal(game.console.drawScope, null);
  } finally { stopReader(); flow.dispose(); game.dispose(); await done; }
});

test('saved selector choices reach original Game Over and Credits through main initialization', async () => {
  const { startPointSettings } = await import('../src/shell/startPoints.js');
  for (const [point, scene] of [['7', 'InterfazGameOver'], ['8', 'InterfazCreditos']]) {
    const game = session(environment => {
      environment.shims.Sleep = async () => {};
      return createRuntime(environment);
    });
    const screens = [];
    const stop = game.state.select(state => state.screen?.id, id => screens.push(id));
    game.setOpening({ enabled: () => true, getNames: () => ['Ana'],
      takeDestination: skipLore => startPointSettings(point, skipLore),
      begin: async () => { throw new DOMException('reset', 'AbortError'); } });
    const done = game.start(startPointSettings('0', false));
    try {
      await waitFor(() => screens.includes(scene));
      assert.equal(screens.slice(0, screens.indexOf(scene)).includes('MenuPrincipal'), false);
      assert.equal(game.state.getSnapshot().game, null);
    } finally { stop(); game.dispose(); await done; }
  }
});
