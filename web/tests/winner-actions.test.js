import test from 'node:test';
import assert from 'node:assert/strict';
import { createGameState } from '../src/state/gameState.js';
import { createRuntimeBridge } from '../src/state/runtimeBridge.js';
import { createSessionShims } from '../src/runtime/sessionShims.js';
import { createAudioChannel } from '../src/audio/audioChannel.js';
import { mountWinnerActions } from '../src/presentation/winnerActions.js';
import { selectControlMode } from '../src/shell/controlPolicy.js';

function fixture({ muted = false, createAudio } = {}) {
  const store = createGameState(), bridge = createRuntimeBridge(store), tracks = [], abort = new AbortController();
  let enabled = true;
  const audio = createAudioChannel(store, { initialMuted: muted, createAudio: createAudio || (src => {
    const track = Object.assign(new EventTarget(), { src, paused: true, ended: false,
      play() { this.paused = false; return Promise.resolve(); },
      pause() { this.paused = true; this.dispatchEvent(new Event('pause')); } });
    tracks.push(track); return track;
  }) });
  const gate = mountWinnerActions(store.api, { enabled: () => enabled });
  const platform = createSessionShims({}, bridge, { config: {}, audio, signal: abort.signal,
    requestFrame: callback => setTimeout(callback, 0), cancelFrame: clearTimeout });
  const leaveScreen = bridge.enterScreen('InterfazCongratulations');
  let leaveInput;
  return { store, bridge, audio, tracks, platform, gate,
    blocked: () => store.api.getSnapshot().winnerActionsBlocked,
    ready() { leaveInput = bridge.enterInput({ consumer: 'InterfazCongratulations', kind: 'key' }); },
    enable(value) { enabled = value; gate.refresh(); },
    dispose() { leaveInput?.(); leaveScreen(); gate.dispose(); audio.dispose(); abort.abort(); } };
}

test('Winner actions wait for animation and music; early keyboard/UI commands are discarded', async () => {
  const view = fixture();
  try {
    view.audio.play('YouWinMetal.mp3'); view.platform.sendInput('e');
    assert.equal(view.platform.shims._kbhit(), 0);
    view.ready(); assert.equal(view.blocked(), true);
    assert.equal(selectControlMode(view.store.api.getSnapshot()), 'none', 'Actions stay hidden while music plays');
    const choice = view.platform.shims._getch();
    let resolved = false; choice.then(() => { resolved = true; });
    view.platform.sendInput('Enter'); view.platform.sendInput('e'); view.platform.sendInput('k');
    await Promise.resolve(); assert.equal(resolved, false);
    view.tracks[0].dispatchEvent(new Event('ended')); assert.equal(view.blocked(), false);
    assert.equal(selectControlMode(view.store.api.getSnapshot()), 'congrats', 'Name and Exit appear directly when ready');
    await Promise.resolve(); assert.equal(resolved, false, 'No replay of blocked presses');
    view.platform.sendInput('k'); assert.equal(await choice, 'k');
  } finally { view.dispose(); }
});

test('mute/unmute while animating or waiting recomputes readiness; F remains immediate', () => {
  const view = fixture({ muted: true });
  try {
    view.audio.play('YouWinMetal.mp3'); assert.equal(view.blocked(), true);
    view.ready(); assert.equal(view.blocked(), false);
    view.platform.sendInput('f'); assert.equal(view.blocked(), true);
    assert.equal(view.platform.shims._kbhit(), 0);
    view.platform.sendInput('f'); assert.equal(view.blocked(), false);
    view.audio.setWebMuted(false); assert.equal(view.blocked(), true);
    view.tracks[0].dispatchEvent(new Event('ended'));
    view.audio.setWebMuted(true); view.audio.setWebMuted(false);
    assert.equal(view.blocked(), false);
  } finally { view.dispose(); }
});

test('errors and interruptions release the wait; old events cannot unlock a replay or another session', () => {
  const view = fixture(), other = fixture();
  try {
    view.ready(); other.ready(); view.audio.play('YouWinMetal.mp3'); other.audio.play('YouWinMetal.mp3');
    const old = view.tracks[0]; old.dispatchEvent(new Event('error')); assert.equal(view.blocked(), false);
    view.audio.play('YouWinMetal.mp3'); old.dispatchEvent(new Event('ended')); old.dispatchEvent(new Event('error'));
    assert.equal(view.blocked(), true); assert.equal(other.blocked(), true);
    view.tracks[1].pause(); assert.equal(view.blocked(), false);
    view.audio.play('YouWinMetal.mp3'); view.audio.stop(); assert.equal(view.blocked(), false);
    view.audio.play('YouWinMetal.mp3'); view.audio.play('TypeWriter1.mp3'); assert.equal(view.blocked(), false);
  } finally { view.dispose(); other.dispose(); }
});

test('autoplay rejection releases the wait; a stale rejection cannot settle a new track', async () => {
  let reject;
  const view = fixture({ createAudio: () => Object.assign(new EventTarget(), {
    play: () => new Promise((resolve, fail) => { reject = fail; }), pause() {},
  }) });
  const warn = console.warn; console.warn = () => {};
  try {
    view.ready(); view.audio.play('YouWinMetal.mp3'); reject(new Error('blocked'));
    await Promise.resolve(); assert.equal(view.blocked(), false);
    view.audio.play('YouWinMetal.mp3'); const rejectOld = reject;
    view.audio.play('YouWinMetal.mp3'); rejectOld(new Error('late rejection'));
    await Promise.resolve(); assert.equal(view.blocked(), true);
    reject(new Error('current rejection')); await Promise.resolve(); assert.equal(view.blocked(), false);
  } finally { console.warn = warn; view.dispose(); }
});

test('desktop, native name entry, runtime errors and disposal do not retain the gate', () => {
  const view = fixture();
  try {
    view.audio.play('YouWinMetal.mp3'); view.ready(); view.enable(false); assert.equal(view.blocked(), false);
    view.enable(true); assert.equal(view.blocked(), true);
    const leaveNames = view.bridge.enterInput({ consumer: 'InterfazCongratulations', kind: 'text', native: true });
    assert.equal(view.blocked(), false); leaveNames(); assert.equal(view.blocked(), true);
    view.store.event('runtimeError', {}); assert.equal(view.blocked(), false);
    view.store.publish({ screen: { id: 'launcher' }, inputRequest: null }); assert.equal(view.blocked(), false);
    view.store.publish({ screen: { id: 'InterfazCongratulations' }, inputRequest: null }); assert.equal(view.blocked(), true);
    view.gate.dispose(); view.audio.play('YouWinMetal.mp3'); assert.equal(view.blocked(), false);
  } finally { view.dispose(); }
});
