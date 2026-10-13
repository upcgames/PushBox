import test from 'node:test';
import assert from 'node:assert/strict';
import vm from 'node:vm';
import { readFileSync } from 'node:fs';

function fixture(horizontalDisabled) {
  const inputs = [], timers = new Map(); let id = 0;
  const shell = { getBoundingClientRect: () => ({ left: 0, top: 0, width: 186, height: 186 }),
    setPointerCapture() {}, hasPointerCapture: () => true, releasePointerCapture() {} };
  const schedule = callback => { timers.set(++id, callback); return id; };
  const context = vm.createContext({ $state: value => value,
    $props: () => ({ horizontalDisabled, onDir: key => inputs.push(key) }), onDestroy() {},
    setTimeout: schedule, setInterval: schedule, clearTimeout: id => timers.delete(id), clearInterval: id => timers.delete(id) });
  const source = readFileSync(new URL('../src/components/Dpad.svelte', import.meta.url), 'utf8');
  const script = source.match(/<script>([\s\S]*?)<\/script>/)[1].replace(/^\s*import .*;\n/gm, '');
  vm.runInContext(script, context);
  context.testShell = shell;
  vm.runInContext('shellEl = testShell;', context);
  const handlers = vm.runInContext('({ handlePointerDown, handlePointerMove, handlePointerUp })', context);
  const event = (clientX, clientY) => ({ clientX, clientY, pointerId: 1, buttons: 1, type: 'pointermove', preventDefault() {} });
  return { inputs, timers, handlers, event };
}

test('menu D-pad ignores horizontal presses and stops repeat when dragged onto a disabled direction', () => {
  const view = fixture(true), { handlers, event } = view;
  handlers.handlePointerDown(event(155, 93));
  handlers.handlePointerDown(event(31, 93));
  assert.deepEqual(view.inputs, []);
  assert.equal(view.timers.size, 0);
  handlers.handlePointerDown(event(93, 31));
  assert.deepEqual(view.inputs, ['w']);
  assert.equal(view.timers.size, 1);
  handlers.handlePointerMove(event(155, 93));
  assert.equal(view.timers.size, 0, 'Disabled direction cancels the previous held direction');
  handlers.handlePointerMove(event(93, 155));
  assert.equal(view.timers.size, 1, 'Returning to an enabled direction resumes repeat');
  handlers.handlePointerUp(event(93, 155));
  assert.equal(view.timers.size, 0);
});

test('gameplay D-pad still dispatches both horizontal directions', () => {
  const view = fixture(false), { handlers, event } = view;
  handlers.handlePointerDown(event(155, 93)); handlers.handlePointerUp(event(155, 93));
  handlers.handlePointerDown(event(31, 93)); handlers.handlePointerUp(event(31, 93));
  assert.deepEqual(view.inputs, ['d', 'a']);
});
