import { VirtualConsole } from './virtual_console.js';
import { ConsoleColor } from './consoleColor.js';
export const animConsole = new VirtualConsole('animCanvas', 80, 63, 14, true);
export const Console = animConsole;
export { ConsoleColor };
