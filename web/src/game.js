import { VirtualConsole } from './shims/virtual_console.js';
import './shims/audio_shim.js';
import { main } from './dsl/main.js';

// Platform Virtual Console Instance (80x60 DOS Grid)
window.Console = new VirtualConsole('gameCanvas', 80, 60, 14);

document.addEventListener('DOMContentLoaded', async () => {
  console.log("🕹️ Executing PushBox main() E2E with async/await Sleep timing...");
  try {
    await main();
  } catch (err) {
    console.error("🎮 PushBox Runtime Execution Report:", err);
  }
});
