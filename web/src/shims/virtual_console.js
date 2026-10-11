import { ConsoleColor } from './consoleColor.js';
import { recordInput } from '../state/runtimeBridge.js';

export class Random {
  Next(min, max) {
    return Math.floor(Math.random() * (max - min)) + min;
  }
}

export class CONSOLE_SCREEN_BUFFER_INFO {
  constructor() {
    this.dwCursorPosition = { X: 0, Y: 0 };
  }
}

let lastFrameTime = typeof performance !== 'undefined' ? performance.now() : 0;
const keyQueue = [];
const keyWaiters = [];

if (typeof window !== 'undefined') {
  window.addEventListener('keydown', (e) => {
    if (['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight', ' '].includes(e.key)) {
      e.preventDefault();
    }
    let keyVal = e.key;
    if (keyVal === 'Enter') keyVal = 13;
    if (keyVal === 'Escape') keyVal = 27;
    recordInput(keyVal, 'received');

    if (keyWaiters.length > 0) {
      const resolve = keyWaiters.shift();
      resolve(keyVal);
    } else {
      keyQueue.push(keyVal);
    }
  });
}

export class Ref {
  constructor(val) {
    this.v = val;
  }
  valueOf() {
    return this.v;
  }
  toString() {
    return String(this.v);
  }
}

if (typeof window !== 'undefined') {
  window.Ref = Ref;
  window.Random = Random;
  window.CONSOLE_SCREEN_BUFFER_INFO = CONSOLE_SCREEN_BUFFER_INFO;

  // Win32 & C stdio Low-Level Shims
  // Win32 console text color attribute parser; unpacks foreground/background bits and applies them to VirtualConsole
  window.SetConsoleTextAttribute = (handle, wColor) => {
    if (window.Console) {
      const fgWin32 = wColor & 0x0F;
      const bgWin32 = (wColor >> 4) & 0x0F;

      // Map Win32 indices (0-15) to our DOS_PALETTE 1-16 indices
      const WIN32_TO_CONSOLE_COLOR = [
        9, 12, 11, 13, 10, 14, 15, 8, 16, 4, 3, 5, 2, 6, 7, 1
      ];

      window.Console.SetForegroundColor(WIN32_TO_CONSOLE_COLOR[fgWin32]);
      window.Console.SetBackgroundColor(WIN32_TO_CONSOLE_COLOR[bgWin32]);
    }
  };
  // No-op: Win32 console handle getter; returns nominal handle index for shim compatibility
  window.GetStdHandle = (handle) => handle;
  // No-op: C stdlib OS terminal command runner; screen clear/pause commands are handled natively by VirtualConsole and DOM listeners
  window.system = () => { };

  // Discard buffered keypresses when the game requests fresh input.
  window.FlushConsoleInputBuffer = () => {
    keyQueue.length = 0;
    return 1;
  };
  window.fflush = () => { };

  window.STD_OUTPUT_HANDLE = 1;
  window.STD_INPUT_HANDLE = 0;
  window.stdin = 0;

  // C stdio toupper and C# Convert helpers
  window.toupper = (c) => (typeof c === 'string' ? c.toUpperCase() : (typeof c === 'number' && c >= 97 && c <= 122 ? c - 32 : c));
  window.Convert = {
    ToByte: (v) => Number(v) & 0xFF,
    ToInt32: (v) => Number(v) | 0,
    ToChar: (v) => (typeof v === 'number' ? String.fromCharCode(v) : String(v)),
    ToString: (v) => String(v),
    ToBoolean: (v) => Boolean(v)
  };

  // C conio keyboard polling shims (Universal non-blocking keypress queue)
  window._kbhit = () => (keyQueue.length > 0 ? 1 : 0);

  window._getch = async () => {
    recordInput(null, 'waiting');
    let key;
    if (keyQueue.length > 0) {
      key = keyQueue.shift();
    } else {
      key = await new Promise(resolve => keyWaiters.push(resolve));
    }
    recordInput(key, 'consumed');
    return key;
  };

  // Async DOM Text Input Shim for scanf(format, targetArray)
  window.scanf = async (format, targetArray) => {
    let maxLen = 8;
    const match = String(format).match(/%(\d+)s/);
    if (match) maxLen = parseInt(match[1], 10);

    let inputStr = "";
    while (true) {
      if (window._kbhit()) {
        const char = await window._getch();
        if (char === 13 || char === '\r' || char === 'Enter') {
          if (inputStr.length > 0) break;
        } else if (char === 8 || char === '\b' || char === 'Backspace') {
          if (inputStr.length > 0) {
            inputStr = inputStr.slice(0, -1);
            if (window.Console) {
              window.Console.cursorX = Math.max(0, window.Console.cursorX - 1);
              window.Console.Write(" ");
              window.Console.cursorX = Math.max(0, window.Console.cursorX - 1);
            }
          }
        } else if (typeof char === 'string' && char.length === 1) {
          if (inputStr.length < maxLen) {
            inputStr += char;
            if (window.Console) {
              window.Console.Write(char);
            }
          }
        }
      }
      await window.Sleep(16);
    }

    if (targetArray) {
      for (let i = 0; i < inputStr.length; i++) {
        targetArray[i] = inputStr[i];
      }
      targetArray[inputStr.length] = '\0';
    }
    return 1;
  };

  // C stdio string length helper (Fails fast on NULL or invalid non-array/string pointers, matching C strlen SIGSEGV semantics)
  window.strlen = (str) => {
    if (str == null || typeof str.length === 'undefined') {
      throw new TypeError(`strlen(${str}): Segmentation fault or invalid pointer (no length property)`);
    }
    if (typeof str === 'string') {
      const nul = str.indexOf('\0');
      return nul === -1 ? str.length : nul;
    }
    if (Array.isArray(str)) {
      let len = 0;
      for (let i = 0; i < str.length; i++) {
        if (str[i] === '\0' || str[i] === 0) break;
        len++;
      }
      return len;
    }
    return str.length;
  };

  window.Sleep = async (ms) => {
    if (ms <= 0) return;

    const now = performance.now();
    if (ms <= 16) {
      if (now - lastFrameTime >= 16) {
        await new Promise(resolve => requestAnimationFrame(resolve));
        lastFrameTime = performance.now();
      }
      return;
    }

    await new Promise(resolve => setTimeout(resolve, ms));
    lastFrameTime = performance.now();
  };

  window.GetConsoleScreenBufferInfo = (handle, csbi) => {
    if (csbi && window.Console) {
      csbi.dwCursorPosition = { X: window.Console.cursorX, Y: window.Console.cursorY };
    }
  };

  window.ConsoleColor = ConsoleColor;

  /* global URLSearchParams */
  window.getDevConfig = (key) => {
    // If the web launcher UI passed overrides, use them first
    if (window.DEV_CONFIG_OVERRIDES) {
      if (key === 1) return window.DEV_CONFIG_OVERRIDES.skipIntro ? 1 : 0;
      if (key === 2) return window.DEV_CONFIG_OVERRIDES.startLevel;
      if (key === 3) return window.DEV_CONFIG_OVERRIDES.skipLore ? 1 : 0;
    }

    // Fallback to URL parameters
    const params = new URLSearchParams(window.location.search);
    if (key === 1) return params.get('skipIntro') === '1' ? 1 : 0;
    if (key === 2) return parseInt(params.get('startLevel') || params.get('startLevel1') || '0', 10);
    if (key === 3) return params.get('skipLore') === '1' ? 1 : 0;
    return 0;
  };
}

export { VirtualConsole } from './consoleSurface.js';
