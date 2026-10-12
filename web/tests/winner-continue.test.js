import test from 'node:test';
import assert from 'node:assert/strict';
import { createGameState } from '../src/state/gameState.js';
import { createRuntimeBridge } from '../src/state/runtimeBridge.js';
import { createSessionShims } from '../src/runtime/sessionShims.js';
import { createAudioChannel } from '../src/audio/audioChannel.js';
import { mountWinnerContinue } from '../src/presentation/winnerContinue.js';

function fixture({ muted = false, createAudio } = {}) {
  const store = createGameState(), bridge = createRuntimeBridge(store), tracks = [], abort = new AbortController();
  let enabled = true;
  const audio = createAudioChannel(store, { initialMuted: muted, createAudio: createAudio || (src => {
    const track = Object.assign(new EventTarget(), { src, paused: true, ended: false,
      play() { this.paused = false; return Promise.resolve(); },
      pause() { this.paused = true; this.dispatchEvent(new Event('pause')); } });
    tracks.push(track); return track;
  }) });
  const gate = mountWinnerContinue(store.api, { enabled: () => enabled });
  const platform = createSessionShims({}, bridge, { config: {}, audio, signal: abort.signal,
    requestFrame: callback => setTimeout(callback, 0), cancelFrame: clearTimeout });
  const leaveScreen = bridge.enterScreen('InterfazCongratulations');
  let leaveInput;
  return { store, bridge, audio, tracks, platform, gate,
    blocked: () => store.api.getSnapshot().winnerContinueBlocked,
    ready() { leaveInput = bridge.enterInput({ consumer: 'InterfazCongratulations', kind: 'confirmation', key: 'E' }); },
    enable(value) { enabled = value; gate.refresh(); },
    dispose() { leaveInput?.(); leaveScreen(); gate.dispose(); audio.dispose(); abort.abort(); } };
}

test('Continue waits for animation and music; early keyboard/UI commands are discarded', async () => {
  const view = fixture();
  try {
    view.audio.play('YouWinMetal.wav'); view.platform.sendInput('e');
    assert.equal(view.platform.shims._kbhit(), 0);
    view.ready(); assert.equal(view.blocked(), true);
    const confirmation = view.platform.shims._getch();
    let resolved = false; confirmation.then(() => { resolved = true; });
    view.platform.sendInput('Enter'); view.platform.sendInput('e');
    await Promise.resolve(); assert.equal(resolved, false);
    view.tracks[0].dispatchEvent(new Event('ended')); assert.equal(view.blocked(), false);
    await Promise.resolve(); assert.equal(resolved, false, 'No replay of blocked presses');
    view.platform.sendInput('e'); assert.equal(await confirmation, 'e');
  } finally { view.dispose(); }
});

test('mute/unmute while animating or waiting recomputes readiness; F remains immediate', () => {
  const view = fixture({ muted: true });
  try {
    view.audio.play('YouWinMetal.wav'); assert.equal(view.blocked(), true);
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
    view.ready(); other.ready(); view.audio.play('YouWinMetal.wav'); other.audio.play('YouWinMetal.wav');
    const old = view.tracks[0]; old.dispatchEvent(new Event('error')); assert.equal(view.blocked(), false);
    view.audio.play('YouWinMetal.wav'); old.dispatchEvent(new Event('ended')); old.dispatchEvent(new Event('error'));
    assert.equal(view.blocked(), true); assert.equal(other.blocked(), true);
    view.tracks[1].pause(); assert.equal(view.blocked(), false);
    view.audio.play('YouWinMetal.wav'); view.audio.stop(); assert.equal(view.blocked(), false);
    view.audio.play('YouWinMetal.wav'); view.audio.play('TypeWriter1.wav'); assert.equal(view.blocked(), false);
  } finally { view.dispose(); other.dispose(); }
});

test('autoplay rejection releases the wait; a stale rejection cannot settle a new track', async () => {
  let reject;
  const view = fixture({ createAudio: () => Object.assign(new EventTarget(), {
    play: () => new Promise((resolve, fail) => { reject = fail; }), pause() {},
  }) });
  const warn = console.warn; console.warn = () => {};
  try {
    view.ready(); view.audio.play('YouWinMetal.wav'); reject(new Error('blocked'));
    await Promise.resolve(); assert.equal(view.blocked(), false);
    view.audio.play('YouWinMetal.wav'); const rejectOld = reject;
    view.audio.play('YouWinMetal.wav'); rejectOld(new Error('late rejection'));
    await Promise.resolve(); assert.equal(view.blocked(), true);
    reject(new Error('current rejection')); await Promise.resolve(); assert.equal(view.blocked(), false);
  } finally { console.warn = warn; view.dispose(); }
});

test('desktop, Change name/Exit requests, runtime errors and disposal do not retain the gate', () => {
  const view = fixture();
  try {
    view.audio.play('YouWinMetal.wav'); view.ready(); view.enable(false); assert.equal(view.blocked(), false);
    view.enable(true); assert.equal(view.blocked(), true);
    const leaveKeys = view.bridge.enterInput({ consumer: 'InterfazCongratulations', kind: 'key' });
    assert.equal(view.blocked(), false); leaveKeys(); assert.equal(view.blocked(), true);
    view.store.event('runtimeError', {}); assert.equal(view.blocked(), false);
    view.store.publish({ screen: { id: 'launcher' }, inputRequest: null }); assert.equal(view.blocked(), false);
    view.store.publish({ screen: { id: 'InterfazCongratulations' }, inputRequest: null }); assert.equal(view.blocked(), true);
    view.gate.dispose(); view.audio.play('YouWinMetal.wav'); assert.equal(view.blocked(), false);
  } finally { view.dispose(); }
});
