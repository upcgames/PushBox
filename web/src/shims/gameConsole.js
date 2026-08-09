import { VirtualConsole } from './virtual_console.js';
import { ConsoleColor } from './consoleColor.js';
export const gameConsole = new VirtualConsole('gameCanvas', 80, 63, 14);
export const Console = gameConsole;
export { ConsoleColor };
