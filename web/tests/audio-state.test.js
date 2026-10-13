import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync, readdirSync } from 'node:fs';
import { createGameState } from '../src/state/gameState.js';
import { createRuntimeBridge } from '../src/state/runtimeBridge.js';
import { createSessionShims } from '../src/runtime/sessionShims.js';
import { createAudioChannel } from '../src/audio/audioChannel.js';
import { AUDIO_FILES, CONGRATULATIONS_MUSIC } from '../src/generated/audioAssets.js';

function channel(store, options = {}) {
  const tracks = [];
  const audio = createAudioChannel(store, { ...options, createAudio: src => {
    const track = { src, volume: 1, paused: true, ended: false, currentTime: 0,
      play() { this.paused = false; return Promise.resolve(); }, pause() { this.paused = true; } };
    tracks.push(track); return track;
  } });
  return { audio, tracks };
}

test('all canonical sound requests match the generated manifest and asset casing exactly', () => {
  const sounds = readFileSync(new URL('../src/generated/sounds.js', import.meta.url), 'utf8');
  const source = readdirSync(new URL('../../Retro Push Box/', import.meta.url));
  const served = readdirSync(new URL('../public/audio/', import.meta.url));
  for (const match of sounds.matchAll(/TEXT\("([^"]+\.wav)"\)/g)) {
    assert.ok(AUDIO_FILES.includes(match[1]), match[1]);
    assert.ok(source.includes(match[1]), match[1]);
    assert.ok(served.includes(match[1]), match[1]);
  }
  assert.equal(CONGRATULATIONS_MUSIC, sounds.match(/function MusicaCongratulations\(\)[\s\S]*?TEXT\("([^"]+)"\)/)[1]);
});

test('endurecimiento replaces the final placement bell on the canonical single channel', () => {
  const store = createGameState(), { audio, tracks } = channel(store);
  audio.play('Coin02.wav', null, 1);
  audio.play('Endurecimiento.wav', null, 1);
  assert.equal(tracks[0].paused, true);
  assert.equal(audio.getCurrentAudio(), tracks[1]);
  assert.equal(tracks[1].paused, false);
  audio.setWebMuted(true);
  assert.equal(tracks[1].volume, 0);
  audio.dispose();
});

test('UI mute, canonical sound references and every playback type use the same state', () => {
  const store = createGameState(), bridge = createRuntimeBridge(store);
  const { audio, tracks } = channel(store);
  const sound = { v: 0 }; bridge.bindSound(sound);
  assert.equal(sound.v, true, 'The store, not a stale Ref initializer, owns sound');
  store.publish({ game: { sound: true } });
  const history = [];
  const stop = store.api.select(state => state.audio.muted, muted => history.push(muted));
  audio.play('PuedeRe.wav', null, 1);
  audio.setWebMuted(true);
  assert.equal(tracks[0].volume, 0);
  assert.equal(sound.v, false);
  assert.equal(store.api.getSnapshot().game.sound, false);
  audio.play('TypeWriter1.wav', null, 8);
  assert.equal(tracks[1].loop, true);
  assert.equal(tracks[1].volume, 0);
  assert.equal(tracks[0].paused, true);
  audio.setWebMuted(false);
  assert.equal(sound.v, true);
  assert.equal(tracks[1].volume, 1);
  audio.play('movf.wav', null, 1);
  assert.equal(tracks[2].volume, 1, 'Unmute cannot leave movement disabled');
  sound.v = 0;
  assert.equal(audio.isWebMuted(), true);
  assert.equal(tracks[2].volume, 0);
  sound.v = 1;
  assert.equal(tracks[2].volume, 1);
  assert.deepEqual(history, [false, true, false, true, false]);
  stop(); audio.dispose();
});

test('sessions isolate audio, troll choice avoids repeats, and muted playback never unmutes', () => {
  const a = createGameState(), b = createGameState();
  const first = channel(a, { initialMuted: true, random: () => 0 }), second = channel(b);
  const one = first.audio.playTrollSound();
  assert.equal(one.volume, 0);
  assert.equal(a.api.getSnapshot().audio.muted, true);
  one.currentTime = 5;
  assert.equal(first.audio.playTrollSound(), one);
  assert.equal(one.currentTime, 0);
  one.ended = true;
  const two = first.audio.playTrollSound();
  assert.notEqual(one.src, two.src);
  second.audio.play('movf.wav', null, 1);
  first.audio.setWebMuted(false); first.audio.setWebMuted(true);
  assert.equal(second.tracks[0].volume, 1);
  assert.equal(b.api.getSnapshot().audio.muted, false);
  first.audio.dispose(); second.audio.dispose();
  assert.equal(first.audio.getCurrentAudio(), null);
});

test('F applies immediately without entering gameplay input queue; text F stays literal', async () => {
  const store = createGameState(), bridge = createRuntimeBridge(store), abort = new AbortController();
  const { audio } = channel(store);
  const platform = createSessionShims({}, bridge, { audio, config: {}, signal: abort.signal,
    requestFrame: callback => setTimeout(callback, 0), cancelFrame: clearTimeout });
  const leave = bridge.enterInput({ kind: 'key', consumer: 'ControlDeMovimiento' });
  const movement = platform.shims._getch();
  platform.sendInput('F');
  assert.equal(audio.isWebMuted(), true);
  assert.equal(platform.shims._kbhit(), 0);
  // A UI toggle during an animation cannot leave a delayed F behind to toggle again.
  audio.setWebMuted(false);
  platform.sendInput('d');
  assert.equal(await movement, 'd');
  assert.equal(audio.isWebMuted(), false);
  leave();
  const text = bridge.enterInput({ kind: 'text', consumer: 'main', maxLength: 8 });
  platform.sendInput('f');
  assert.equal(await platform.shims._getch(), 'f');
  assert.equal(audio.isWebMuted(), false);
  text();
  const pause = bridge.enterInput({ kind: 'key', consumer: 'InterfazPausa' });
  const repaint = platform.shims._getch();
  platform.sendInput('f');
  assert.equal(await repaint, 'f', 'Pause receives F only to redraw its sound label');
  assert.equal(audio.isWebMuted(), true);
  pause(); abort.abort(); audio.dispose();
});
