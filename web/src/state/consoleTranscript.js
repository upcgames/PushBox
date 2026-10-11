import { runtimeState } from './gameState.js';

// Retain what is actually on screen, including overwrites and CP437 glyphs.
// Flush once per frame, rather than publishing thousands of drawing operations.
export function observeConsole(consoleInstance, schedule = requestAnimationFrame, publisher = runtimeState) {
  let cols, rows, tileSize, cells, pending = false, disposed = false;
  function flush() {
    pending = false;
    if (disposed) return;
    publisher.publish({ console: { cols, rows, tileSize,
      lines: cells.map(row => row.map(cell => cell?.char || ' ').join('').trimEnd()),
      cells } }, 'consoleChanged');
  }
  function changed() {
    if (!pending) { pending = true; schedule(flush); }
  }
  const observer = {
    clear(width, height, size) {
      cols = width; rows = height; tileSize = size;
      cells = Array.from({ length: rows }, () => Array(cols).fill(null));
      changed();
    },
    write(x, y, char, foreground, background) {
      if (x < 0 || x >= cols || y < 0 || y >= rows) return;
      cells[y][x] = { char, foreground, background };
      changed();
    },
  };
  consoleInstance.observer = observer;
  observer.clear(consoleInstance.cols, consoleInstance.rows, consoleInstance.tileSize);
  return () => {
    disposed = true;
    if (consoleInstance.observer === observer) consoleInstance.observer = null;
  };
}
