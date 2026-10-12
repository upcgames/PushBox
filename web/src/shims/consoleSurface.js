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

export class VirtualConsole {
  constructor(canvasId, cols = 80, rows = 60, tileSize = 14, transparent = false) {
    this.canvas = typeof canvasId === 'string' ? document.getElementById(canvasId) : canvasId;
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

    this.drawScope = null;
    this.hidePlayer = false;
    this.hiddenDrawScopes = new Set();
    this.hiddenScopeBackdrops = new Map();
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
      this.observer?.write(this.cursorX, this.cursorY, char, this.fgColor, this.bgColor);
      const cell = { char, foreground: this.fgColor, background: this.bgColor, scope: this.drawScope };
      if (this.cursorY < this.rows) {
        this.cells[this.cursorY][this.cursorX] = cell;
        if (this.drawScope === 'board' || this.drawScope === 'terrain') {
          this.terrainCells[this.cursorY][this.cursorX] = cell;
        }
      }
      this.paintCell(this.cursorX, this.cursorY, cell);

      this.cursorX++;
      if (this.cursorX >= this.cols) {
        this.cursorX = 0;
        this.cursorY++;
      }
    }
    return this;
  }

  // Keep canonical drawing data even when presentation hides the player glyphs.
  // No pixel sampling: switching ownership repaints the original tagged cells.
  enterDrawScope(scope) {
    const previous = this.drawScope;
    this.drawScope = scope;
    if (scope === 'board') this.terrainCells = Array.from({ length: this.rows }, () => Array(this.cols).fill(null));
    return () => { this.drawScope = previous; };
  }

  setPlayerHidden(hidden) {
    if (this.hidePlayer === hidden) return;
    this.hidePlayer = hidden;
    for (let y = 0; y < this.rows; y++) for (let x = 0; x < this.cols; x++) {
      const cell = this.cells[y][x];
      if (cell?.scope === 'player') this.paintCell(x, y, cell);
    }
  }

  setDrawScopeHidden(scope, hidden, backdrop = 'blank') {
    if (this.hiddenDrawScopes.has(scope) === hidden && (!hidden || this.hiddenScopeBackdrops.get(scope) === backdrop)) return;
    if (hidden) { this.hiddenDrawScopes.add(scope); this.hiddenScopeBackdrops.set(scope, backdrop); }
    else { this.hiddenDrawScopes.delete(scope); this.hiddenScopeBackdrops.delete(scope); }
    for (let y = 0; y < this.rows; y++) for (let x = 0; x < this.cols; x++) {
      const cell = this.cells[y][x];
      if (cell?.scope === scope) this.paintCell(x, y, cell);
    }
  }

  paintCell(x, y, cell) {
    const hidden = this.hidePlayer && cell.scope === 'player';
    const scopeHidden = this.hiddenDrawScopes.has(cell.scope);
    const restoreTerrain = scopeHidden && this.hiddenScopeBackdrops.get(cell.scope) === 'terrain';
    const terrain = (hidden || restoreTerrain) && this.terrainCells[y]?.[x];
    const { foreground, background } = terrain || (restoreTerrain ? { foreground: cell.foreground, background: DOS_PALETTE[9] } : cell);
    const char = terrain ? terrain.char : hidden || scopeHidden ? ' ' : cell.char;
    const px = x * this.tileSize;
    const py = y * this.tileSize;
    if (this.transparent) {
      this.ctx.clearRect(px, py, this.tileSize, this.tileSize);
      if (background !== DOS_PALETTE[9]) {
        this.ctx.fillStyle = background;
        this.ctx.fillRect(px, py, this.tileSize, this.tileSize);
      }
    } else {
      this.ctx.fillStyle = background;
      this.ctx.fillRect(px, py, this.tileSize, this.tileSize);
    }

    this.ctx.fillStyle = foreground;
    if (char === '█') {
      // Full blocks paint the entire cell without font edge antialiasing.
      this.ctx.fillRect(px, py, this.tileSize, this.tileSize);
    } else {
      this.ctx.font = `${this.tileSize}px "Px437", monospace`;
      this.ctx.textBaseline = 'top';
      // Keep glyph overflow inside the cell that subsequent writes repaint.
      this.ctx.save();
      this.ctx.beginPath();
      this.ctx.rect(px, py, this.tileSize, this.tileSize);
      this.ctx.clip();
      this.ctx.fillText(char, px, py);
      this.ctx.restore();
    }
  }

  Clear() {
    this.cells = Array.from({ length: this.rows }, () => Array(this.cols).fill(null));
    this.terrainCells = Array.from({ length: this.rows }, () => Array(this.cols).fill(null));
    this.observer?.clear(this.cols, this.rows, this.tileSize);
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

  async loadFonts() {
    // Preload Px437 extended CP437 glyphs used by PushBox (176 ░, 219 █ etc.) so first y=0 telaraña isn't half-width
    const glyphs = '░▒▓█▄▌▐▀ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜ¢£¥₧ƒáíóúñÑªº¿⌐¬½¼¡«»│┤╡╢╖╕╣║╗╝╜╛┐└┴┬├─┼╞╟╚╔╩╦╠═╬╧╨╤╥╙╘╒';
    try {
      if (document.fonts?.load) {
        await document.fonts.load(`${this.tileSize}px "Px437"`, glyphs);
        await document.fonts.ready;
      }
    } catch (e) {
      console.warn('[VirtualConsole] loadFonts failed:', e);
    }
    // ensure ctx font is set after load
    this.ctx.font = `${this.tileSize}px "Px437", monospace`;

  }
}
