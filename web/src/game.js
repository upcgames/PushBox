import './shims/audio_shim.js';
import { gameConsole } from './shims/gameConsole.js';
import { main } from './dsl/main.js';

// Platform Virtual Console Instance (80x63 DOS Grid - canonical) - single base instance shared with DSL
window.Console = gameConsole;

window.DEV_CONFIG_OVERRIDES = null;

document.addEventListener('DOMContentLoaded', async () => {
  const launcherOverlay = document.getElementById('launcherOverlay');
  const startBtn = document.getElementById('startBtn');
  const startLevelSelect = document.getElementById('startLevel');
  const skipLoreCheckbox = document.getElementById('skipLore');

  // Load saved config from localStorage
  try {
    const saved = JSON.parse(window.localStorage.getItem('pushboxDevConfig'));
    if (saved) {
      if (saved.startLevel) startLevelSelect.value = saved.startLevel;
      if (saved.skipLore !== undefined) skipLoreCheckbox.checked = saved.skipLore;
    }
  } catch (e) { /* ignore parse errors */ }

  // Wait for the custom retro font to load to prevent canvas rendering gaps
  await document.fonts.ready;
  startBtn.textContent = 'START GAME (Enter)';
  startBtn.disabled = false;

  const startGame = async () => {
    if (startBtn.disabled) return;
    
    // Hide Launcher
    launcherOverlay.style.display = 'none';

    // Parse UI state to global dev config
    const levelInt = parseInt(startLevelSelect.value, 10);
    window.DEV_CONFIG_OVERRIDES = {
      skipIntro: levelInt !== 0,
      startLevel: levelInt > 0 ? levelInt : 0,
      skipLore: skipLoreCheckbox.checked
    };

    // Save state to localStorage for next refresh
    window.localStorage.setItem('pushboxDevConfig', JSON.stringify({
      startLevel: startLevelSelect.value,
      skipLore: skipLoreCheckbox.checked
    }));

    console.log("🕹️ Executing PushBox main() E2E with async/await Sleep timing...");
    try {
      await main();
    } catch (err) {
      console.error("🎮 PushBox Runtime Execution Report:", err);
    }
  };

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
