import { preloadAudio, PlaySound, StopSound, setWebMuted } from './shims/audio_shim.js';
import { gameConsole } from './shims/gameConsole.js';
import * as originalRuntime from './runtime/originalRuntime.js';
import { runMobileRuntime } from './runtime/runMobileRuntime.js';
import { mountMobileOpening } from './presentation/mountMobileOpening.js';
import { createSeenProgress } from './state/seenProgress.js';
import { runAnim } from './animationDriver.js';
import { populateStartPoints, startPointSettings } from './shell/startPoints.js';
import { setupMobileShell, isMobile } from './shell/mobileController.js';
import { setupMuteButton, showMuteButton } from './shell/muteButton.js';
import { observeConsole } from './state/consoleTranscript.js';
import { enterScreen } from './state/runtimeBridge.js';
import { runtimeState, GameState } from './state/gameState.js';
import { setupBoardFeedback } from './feedback/boardFeedback.js';

// Platform Virtual Console Instance (80x63 DOS Grid - canonical) - single base instance shared with generated modules
window.Console = gameConsole;
observeConsole(gameConsole);
const leaveLauncher = enterScreen('launcher');

window.DEV_CONFIG_OVERRIDES = null;

document.addEventListener('DOMContentLoaded', async () => {
  const launcherOverlay = document.getElementById('launcherOverlay');
  const startBtn = document.getElementById('startBtn');
  const startLevelSelect = document.getElementById('startLevel');
  const skipLoreCheckbox = document.getElementById('skipLore');
  populateStartPoints(startLevelSelect);

  // Load saved config from localStorage
  try {
    const saved = JSON.parse(window.localStorage.getItem('pushboxDevConfig'));
    if (saved) {
      if (saved.startLevel) startLevelSelect.value = saved.startLevel;
      if (saved.skipLore !== undefined) skipLoreCheckbox.checked = saved.skipLore;
    }
  } catch (e) { console.warn('[Game] Failed to parse pushboxDevConfig from localStorage:', e); }

  const progress = createSeenProgress();
  setupMobileShell({ progress });
  const opening = mountMobileOpening(document.body, GameState, { play: PlaySound, stop: StopSound, setWebMuted }, { enabled: isMobile, surface: gameConsole, progress, onEnter: () => startGame() });
  opening.setLoading(0);
  if (import.meta.hot) import.meta.hot.dispose(opening.dispose);
  setupMuteButton();
  setupBoardFeedback(gameConsole.canvas, undefined, { mobile: isMobile });

  // WEB loading state — preload all required assets before enabling START
  // Fonts (VirtualConsole) + audio (preloadAudio) — both are web shell concerns
  startBtn.textContent = 'Loading fonts...';
  await gameConsole.loadFonts();
  opening.setLoading(2);
  startBtn.textContent = 'Loading audio 0/39...';
  await preloadAudio((loaded, total) => {
    startBtn.textContent = `Loading audio ${loaded}/${total}...`;
    opening.setLoading(Math.round((loaded + 1) / (total + 1) * 100));
  });
  startBtn.textContent = 'START GAME (Enter)';
  startBtn.disabled = false;
  opening.setLoading(100, true);
  let starting = false;

  async function startGame() {
    if (startBtn.disabled || starting) return;
    starting = true;
    opening.hideLoading();
    
    // Hide Launcher
    launcherOverlay.style.display = 'none';
    leaveLauncher();
    showMuteButton();

    // Parse UI state to global dev config
    const settings = startPointSettings(isMobile() ? '0' : startLevelSelect.value, skipLoreCheckbox.checked);
    window.DEV_CONFIG_OVERRIDES = settings;

    // Save state to localStorage for next refresh
    window.localStorage.setItem('pushboxDevConfig', JSON.stringify({
      startLevel: startLevelSelect.value,
      skipLore: skipLoreCheckbox.checked
    }));

    console.log("🕹️ Executing PushBox main() E2E with async/await Sleep timing...");
    try {
      await runMobileRuntime(originalRuntime, { settings, runAnim, opening, setPlayerNames: GameState.setPlayerNames,
        configure: patch => Object.assign(window.DEV_CONFIG_OVERRIDES, patch) });
    } catch (err) {
      runtimeState.event('runtimeError', { message: String(err.message || err) });
      console.error("🎮 PushBox Runtime Execution Report:", err);
    }
  }

  startBtn.addEventListener('click', startGame);

  // Bind Enter key to start the game
  const enterListener = (e) => {
    if (e.key === 'Enter' && launcherOverlay.style.display !== 'none') {
      e.preventDefault();
      document.removeEventListener('keydown', enterListener);
      startGame();
    }
  };
  document.addEventListener('keydown', enterListener);
});
