import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';
import { createOpeningFlow } from '../src/presentation/openingFlow.js';
import { createPlayerProfile, parsePlayerNames, writePlayerIdentity } from '../src/presentation/playerIdentity.js';
import { createSeenProgress } from '../src/state/seenProgress.js';
import { runMobileRuntime } from '../src/runtime/runMobileRuntime.js';

function fixture(progress = createSeenProgress({ storage: null })) {
  const tasks = new Map(), delays = [], audio = [];
  let sequence = 0;
  const profile = createPlayerProfile({ storage: null });
  const flow = createOpeningFlow({ progress, profile, message: 'Hola... fin',
    audio: { play: (...args) => audio.push(args), stop: () => audio.push('stop') },
    schedule: (fn, delay) => { delays.push(delay); tasks.set(++sequence, fn); return sequence; }, cancel: id => tasks.delete(id) });
  return { flow, progress, profile, tasks, delays, audio,
    finish() { while (tasks.size) { const [id, task] = tasks.entries().next().value; tasks.delete(id); task(); } } };
}

test('first warning cannot skip and becomes seen only when advancing to native name entry', async () => {
  const one = fixture();
  const done = one.flow.begin();
  one.flow.continue();
  assert.equal(one.flow.getSnapshot().phase, 'typing');
  assert.equal(one.progress.has('warning'), false);
  one.finish();
  assert.equal(one.flow.getSnapshot().phase, 'warning');
  assert.equal(one.progress.has('warning'), false);
  assert.equal(one.delays.filter(delay => delay === 1000).length, 1, 'one pause after a complete ellipsis');
  one.flow.continue();
  assert.equal(one.progress.has('warning'), true);
  assert.equal(one.flow.getSnapshot().phase, 'name');
  assert.equal(one.flow.submit('💥 !'), false);
  one.flow.submit('  Fránciscólong 💥 Jara99! ignored');
  assert.deepEqual(await done, ['Fráncisc', 'Jara99']);
  assert.deepEqual(one.profile.getNames(), ['Fráncisc', 'Jara99']);
  assert.equal(one.tasks.size, 0);
  const seen = fixture(one.progress), again = seen.flow.begin();
  seen.flow.continue();
  assert.equal(seen.flow.getSnapshot().phase, 'warning');
  seen.flow.continue(); assert.equal(seen.flow.getSnapshot().phase, 'name');
  seen.flow.submit('Ana'); await again;
  one.flow.dispose(); seen.flow.dispose();
});

test('opening reset cancels typing and cannot mark an unfinished warning seen', async () => {
  const one = fixture(), done = one.flow.begin();
  one.flow.dispose();
  await assert.rejects(done, { name: 'AbortError' });
  assert.equal(one.tasks.size, 0);
  assert.equal(one.progress.has('warning'), false);
});

test('native names feed every supported accent to the original BuscarLetra renderer', () => {
  const source = readFileSync(new URL('../src/generated/math.js', import.meta.url), 'utf8');
  const sandbox = vm.createContext({});
  vm.runInContext(source.replace(/^import .*;\n/gm, '').replace(/export /g, ''), sandbox);
  const names = parsePlayerNames('áéíóúñÑ ÁÉÍÓÚ');
  const counts = Array.from({ length: 9 }, () => Array(8));
  writePlayerIdentity(counts, names);
  assert.equal(counts[8][0], '2'); assert.equal(counts[8][1], 7); assert.equal(counts[8][2], 5);
  for (const character of [...counts[6].slice(0, 7), ...counts[7].slice(0, 5)]) {
    const coordinates = Array.from({ length: 4 }, () => ({ v: undefined }));
    sandbox.BuscarLetra(character, ...coordinates);
    assert.ok(coordinates.every(value => Number.isFinite(value.v)), `Original renderer recognizes ${character}`);
  }
});

test('mobile opening composes before original main and returns to warning on Exit', async () => {
  const calls = [], config = { skipIntro: false, startLevel: 0 }, original = { main: async () => calls.push('main') };
  let visits = 0;
  const opening = { enabled: () => true, getNames: () => [], begin: async () => {
    calls.push('warning');
    if (++visits === 3) throw new DOMException('reset', 'AbortError');
    return ['Ana'];
  } };
  await assert.rejects(runMobileRuntime(original, { settings: { ...config, entry: 'main' },
    opening, setPlayerNames: names => calls.push(names.join(' ')), configure: patch => Object.assign(config, patch) }), { name: 'AbortError' });
  assert.deepEqual(calls, ['', 'warning', 'Ana', 'main', 'warning', 'Ana', 'main', 'warning']);
  assert.equal(config.skipIntro, true);
  assert.equal(config.startLevel, 0);
  const desktop = [];
  await runMobileRuntime({ main: async () => desktop.push('original') }, {
    settings: { entry: 'main' }, opening: { enabled: () => false, begin() { assert.fail('Desktop opening changed'); } },
  });
  assert.deepEqual(desktop, ['original']);
});
