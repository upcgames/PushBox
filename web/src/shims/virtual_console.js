import { ConsoleColor } from './consoleColor.js';

// DOS Console 16-Color Palette
const DOS_PALETTE = {
  0: '#000000',  // Pitch Black
  1: '#ffffff',  // White
  2: '#ef4444',  // Red
  3: '#22c55e',  // Green
  4: '#3b82f6',  // Blue
  5: '#06b6d4',  // Cyan
  6: '#d946ef',  // Magenta
  7: '#eab308',  // Yellow
  8: '#94a3b8',  // Gray
  9: '#000000',  // Pitch Black (Default Console Background)
  10: '#991b1b', // Dark Red
  11: '#166534', // Dark Green
  12: '#1e3a8a', // Dark Blue
  13: '#155e75', // Dark Cyan
  14: '#701a75', // Dark Magenta
  15: '#854d0e', // Dark Yellow
  16: '#334155'  // Plomo Oscuro
};

// Official MS-DOS Code Page 437 Extended ASCII Lookup Table (Bytes 128-255)
const CP437_CHARS = 'ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜ¢£¥₧ƒáíóúñÑªº¿⌐¬½¼¡«»░▒▓│┤╡╢╖╕╣║╗╝╜╛┐└┴┬├─┼╞╟╚╔╩╦╠═╬╧╨╤╥╙╘╒Ⓢ╫╪┘┌█▄▌▐▀αßΓπΣσµτΦΘΩδ∞φε∩≡±≥≤⌠⌡÷≈°∙·√ⁿ²■ ';

function decodeCp437(ch) {
  let code = 0;
  if (typeof ch === 'number') {
    code = ch & 0xFF;
  } else if (typeof ch === 'string' && ch.length === 1) {
    code = ch.charCodeAt(0);
  } else {
    return ch;
  }

  if (code >= 128 && code <= 255) {
    return CP437_CHARS[code - 128];
  }
  return String.fromCharCode(code);
}

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

  // No-op: Win32 input buffer flush; DOM keydown listeners queue keypresses asynchronously
  window.FlushConsoleInputBuffer = () => { };
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
    if (keyQueue.length > 0) {
      return keyQueue.shift();
    }
    return new Promise(resolve => keyWaiters.push(resolve));
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

export class VirtualConsole {
  constructor(canvasId, cols = 80, rows = 60, tileSize = 14, transparent = false) {
    this.canvas = document.getElementById(canvasId);
    if (!this.canvas) {
      console.warn(`[VirtualConsole] canvas #${canvasId} not found at ctor - creating offscreen dummy to avoid crash (gallery vs main)`);
      this.canvas = document.createElement('canvas');
      this.canvas.id = canvasId;
    }
    this.ctx = this.canvas.getContext('2d');
    this.cols = cols;
    this.rows = rows;
    this.tileSize = tileSize;
    this.transparent = transparent;

    this.cursorX = 0;
    this.cursorY = 0;
    this.fgColor = DOS_PALETTE[1];
    this.bgColor = DOS_PALETTE[9]; // Pitch Black

    this.canvas.width = cols * tileSize;
    this.canvas.height = rows * tileSize;

    this.Clear();
  }

  SetWindowSize(cols, rows) {
    this.cols = cols;
    this.rows = rows;
    this.canvas.width = cols * this.tileSize;
    this.canvas.height = rows * this.tileSize;
    this.Clear();
  }

  SetCursorPosition(x, y) {
    this.cursorX = Math.max(0, Math.min(x, this.cols - 1));
    this.cursorY = Math.max(0, Math.min(y, this.rows - 1));
  }

  SetBackgroundColor(colorIndex) {
    this.bgColor = DOS_PALETTE[colorIndex] || DOS_PALETTE[9];
  }

  SetForegroundColor(colorIndex) {
    this.fgColor = DOS_PALETTE[colorIndex] || DOS_PALETTE[1];
  }

  get BackgroundColor() { return this.bgColor; }
  set BackgroundColor(colorIndex) { this.SetBackgroundColor(colorIndex); }

  get ForegroundColor() { return this.fgColor; }
  set ForegroundColor(colorIndex) { this.SetForegroundColor(colorIndex); }

  Write(str) {
    const textStr = String(str);

    for (let i = 0; i < textStr.length; i++) {
      const rawChar = textStr[i];

      // Standard Terminal Control Characters
      if (rawChar === '\n') {
        this.cursorX = 0;
        this.cursorY++;
        continue;
      }
      if (rawChar === '\r') {
        this.cursorX = 0;
        continue;
      }
      if (rawChar === '\t') {
        this.cursorX = (Math.floor(this.cursorX / 8) + 1) * 8;
        if (this.cursorX >= this.cols) {
          this.cursorX = 0;
          this.cursorY++;
        }
        continue;
      }

      const char = decodeCp437(rawChar);
      const px = this.cursorX * this.tileSize;
      const py = this.cursorY * this.tileSize;
      if (this.transparent) {
        this.ctx.clearRect(px, py, this.tileSize, this.tileSize);
        if (this.bgColor !== DOS_PALETTE[9]) {
          this.ctx.fillStyle = this.bgColor;
          this.ctx.fillRect(px, py, this.tileSize, this.tileSize);
        }
      } else {
        this.ctx.fillStyle = this.bgColor;
        this.ctx.fillRect(px, py, this.tileSize, this.tileSize);
      }

      this.ctx.fillStyle = this.fgColor;
      this.ctx.font = `${this.tileSize}px "Px437", monospace`;
      this.ctx.textBaseline = 'top';
      this.ctx.fillText(char, px, py);

      this.cursorX++;
      if (this.cursorX >= this.cols) {
        this.cursorX = 0;
        this.cursorY++;
      }
    }
    return this;
  }

  Clear() {
    if (this.transparent) {
      this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    } else {
      this.ctx.fillStyle = DOS_PALETTE[9]; // Pitch Black
      this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);
    }
    this.ctx.font = `${this.tileSize}px "Px437", monospace`;
    this.cursorX = 0;
    this.cursorY = 0;
  }

  async loadAssets() {
    // Preload Px437 extended CP437 glyphs used by PushBox (176 ░, 219 █ etc.) so first y=0 telaraña isn't half-width
    const glyphs = '░▒▓█▄▌▐▀ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜ¢£¥₧ƒáíóúñÑªº¿⌐¬½¼¡«»│┤╡╢╖╕╣║╗╝╜╛┐└┴┬├─┼╞╟╚╔╩╦╠═╬╧╨╤╥╙╘╒';
    try {
      if (document.fonts?.load) {
        await document.fonts.load(`${this.tileSize}px "Px437"`, glyphs);
        await document.fonts.ready;
      }
    } catch {}
    // ensure ctx font is set after load
    this.ctx.font = `${this.tileSize}px "Px437", monospace`;
  }
}
