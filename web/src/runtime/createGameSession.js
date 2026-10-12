import { VirtualConsole } from '../shims/consoleSurface.js';
import { ConsoleColor } from '../shims/consoleColor.js';
import { createGameState } from '../state/gameState.js';
import { createRuntimeBridge, boardSnapshot } from '../state/runtimeBridge.js';
import { observeConsole } from '../state/consoleTranscript.js';
import { createSessionShims } from './sessionShims.js';
import { createSessionAnimation } from './sessionAnimation.js';
import { createSessionAudio } from './sessionAudio.js';

export function createGameSession(canvas, runtimeFactory, options = {}) {
  const controller = new AbortController();
  let platform, started = false, disposed = false;
  const store = createGameState(key => platform.sendInput(key));
  const bridge = { ...createRuntimeBridge(store), boardSnapshot };
  const surface = new VirtualConsole(canvas, 80, 63, 14);
  const audio = options.audioFactory ? options.audioFactory(store) : createSessionAudio(store, options.baseUrl || '/');
  const config = { skipIntro: true, startLevel: 1, skipLore: true };
  platform = createSessionShims(surface, bridge, { ...options.clock, config, audio, signal: controller.signal });
  const runtime = runtimeFactory({ console: surface, consoleColor: ConsoleColor, bridge,
    shims: platform.shims, window: platform.window, runAnim: createSessionAnimation(platform) });
  const stopConsole = observeConsole(surface, options.scheduleTranscript || requestAnimationFrame, store);
  const leaveLauncher = bridge.enterScreen('launcher');
  let done = null;
  return Object.freeze({
    state: store.api, console: surface, audio,
    loadAssets: () => surface.loadFonts(),
    sendInput: key => store.api.sendInput(key),
    start(settings = {}) {
      if (disposed) throw new Error('Session disposed');
      if (started) return done;
      started = true; Object.assign(config, settings); leaveLauncher();
      done = runtime.main().catch(error => {
        if (error.name !== 'AbortError') {
          store.event('runtimeError', { message: String(error.message || error) });
          throw error;
        }
      });
      return done;
    },
    dispose() {
      if (disposed) return;
      disposed = true; stopConsole(); controller.abort(); if (audio.dispose) audio.dispose(); else audio.stop(); leaveLauncher();
    },
  });
}
