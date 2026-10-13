import test from 'node:test';
import assert from 'node:assert/strict';
import { createGameState } from '../src/state/gameState.js';
import { createSeenProgress } from '../src/state/seenProgress.js';
import { createPlayerProfile } from '../src/presentation/playerIdentity.js';
import { createOpeningFlow } from '../src/presentation/openingFlow.js';
import { mountWarningAlarm } from '../src/presentation/warningAlarm.js';
import { createAudioChannel } from '../src/audio/audioChannel.js';

function fixture() {
  const store = createGameState(), tracks = [], tasks = new Map(), visibility = new EventTarget();
  let id = 0, hidden = false, enabled = true;
  const createAudio = src => {
    const track = { src, paused: true, plays: 0, volume: 1,
      play() { this.paused = false; this.plays++; return Promise.resolve(); }, pause() { this.paused = true; } };
    tracks.push(track); return track;
  };
  const audio = createAudioChannel(store, { createAudio });
  const flow = createOpeningFlow({ progress: createSeenProgress({ storage: null }), profile: createPlayerProfile({ storage: null }),
    audio, message: 'Hola... fin', schedule: fn => { tasks.set(++id, fn); return id; }, cancel: token => tasks.delete(token) });
  const alarm = mountWarningAlarm(flow, store.api, { createAudio, visibilityTarget: visibility, hidden: () => hidden, enabled: () => enabled });
  return { store, tracks, audio, flow, alarm,
    tick() { const [token, callback] = tasks.entries().next().value; tasks.delete(token); callback(); },
    finish() { while (tasks.size) { const [token, callback] = tasks.entries().next().value; tasks.delete(token); callback(); } },
    hide(value) { hidden = value; flow.pause(value); visibility.dispatchEvent(new Event('visibilitychange')); },
    enable(value) { enabled = value; alarm.refresh(); },
    dispose() { alarm.dispose(); flow.dispose(); audio.dispose(); } };
}

test('warning alarm loops alongside typing, shares mute, and stops before name entry', async () => {
  const view = fixture(), done = view.flow.begin();
  const alarm = view.tracks.find(track => track.src.endsWith('alert.mp3'));
  assert.equal(alarm.paused, false, 'Alarm starts during the initial typing delay');
  assert.equal(view.tracks.length, 1, 'Typewriter has not started yet');
  view.tick();
  const typing = view.tracks.find(track => track.src.endsWith('TypeWriter1.mp3'));
  assert.equal(alarm.loop, true);
  assert.equal(alarm.paused, false); assert.equal(typing.paused, false);
  assert.equal(view.store.api.getSnapshot().audio.playback.file, 'TypeWriter1.mp3', 'Alarm does not replace canonical playback state');
  view.audio.setWebMuted(true);
  assert.equal(alarm.volume, 0); assert.equal(typing.volume, 0);
  view.audio.setWebMuted(false);
  assert.equal(alarm.volume, 1); assert.equal(typing.volume, 1);
  view.finish();
  assert.equal(view.flow.getSnapshot().phase, 'warning');
  assert.equal(alarm.paused, false); assert.equal(alarm.plays, 1, 'Typing pauses never restart the alarm');
  assert.equal(view.store.api.getSnapshot().audio.playback, null);
  view.flow.continue();
  assert.equal(view.flow.getSnapshot().phase, 'name'); assert.equal(alarm.paused, true);
  view.flow.submit('Ana'); await done;
  view.dispose();
});

test('alarm visibility, reset and disposal are local to each opening session', async () => {
  const one = fixture(), two = fixture();
  const done = one.flow.begin(), other = two.flow.begin();
  const alarm = one.tracks[0], second = two.tracks[0];
  one.hide(true); assert.equal(alarm.paused, true); assert.equal(second.paused, false);
  one.hide(false); assert.equal(alarm.paused, false);
  one.enable(false); assert.equal(alarm.paused, true);
  one.enable(true); assert.equal(alarm.paused, false);
  const reset = assert.rejects(done, { name: 'AbortError' });
  one.flow.setLoading(100, true); await reset;
  assert.equal(alarm.paused, true);
  const stopped = assert.rejects(other, { name: 'AbortError' });
  two.dispose(); await stopped;
  assert.equal(second.paused, true);
  one.dispose();
});

test('warning immediately stops outgoing menu or credits music before the curtain and typing delay', async () => {
  for (const file of ['intro.mp3', 'Outro.mp3']) {
    const view = fixture();
    const outgoing = view.audio.play(file, null, 9);
    const done = view.flow.begin();
    assert.equal(outgoing.paused, true, file);
    assert.equal(view.store.api.getSnapshot().audio.playback, null);
    assert.equal(view.tracks.find(track => track.src.endsWith('alert.mp3')).paused, false);
    assert.equal(view.tracks.some(track => track.src.endsWith('TypeWriter1.mp3')), false);
    const stopped = assert.rejects(done, { name: 'AbortError' });
    view.dispose(); await stopped;
  }
});

test('Exit holds a silent blackout before revealing the warning and starting its alarm', async () => {
  const view = fixture(), outgoing = view.audio.play('intro.mp3', null, 9);
  const done = view.flow.begin({ afterExit: true });
  assert.equal(view.flow.getSnapshot().phase, 'blackout');
  assert.equal(outgoing.paused, true);
  assert.equal(view.tracks.length, 1, 'Neither alarm nor typing plays during blackout');
  view.tick();
  assert.equal(view.flow.getSnapshot().phase, 'typing');
  assert.equal(view.flow.getSnapshot().position, 0);
  assert.equal(view.tracks.find(track => track.src.endsWith('alert.mp3')).paused, false);
  assert.equal(view.tracks.some(track => track.src.endsWith('TypeWriter1.mp3')), false);
  const stopped = assert.rejects(done, { name: 'AbortError' });
  view.dispose(); await stopped;
});
