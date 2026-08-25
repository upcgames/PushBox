// Lightweight web bus for canonical → web telemetry (no pull needed yet)
const listeners = new Map();

export function emit(type, payload) {
  const cbs = listeners.get(type);
  if (!cbs) return;
  for (const fn of [...cbs]) {
    try { fn(payload); } catch (e) { console.warn(`[GameState] handler for ${type} failed:`, e); }
  }
}

export function on(type, fn) {
  if (!listeners.has(type)) listeners.set(type, new Set());
  listeners.get(type).add(fn);
  return () => listeners.get(type).delete(fn);
}

// Convenience for inputMode
export function emitInputMode(mode) {
  emit('inputMode', mode);
}
export function onInputMode(fn) { return on('inputMode', fn); }

if (typeof window !== 'undefined') {
  window.GameState = { emit, on, emitInputMode, onInputMode };
}

// Exported object for generated modules (import { GameState })
export const GameState = { emit, on, emitInputMode, onInputMode };
