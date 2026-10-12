// Platform functions with session ownership. No global keyboard listener.
export function createSessionShims(surface, bridge, { config, audio, signal,
  requestFrame = requestAnimationFrame, cancelFrame = cancelAnimationFrame,
  now = () => performance.now() }) {
  const queue = [], waiters = [], scheduled = new Set();
  let lastFrameTime = now();
  const cancelled = () => new DOMException('Session stopped', 'AbortError');
  const check = () => { if (signal.aborted) throw cancelled(); };
  function scheduledWait(schedule, cancel) {
    check();
    return new Promise((resolve, reject) => {
      const task = { reject, cancel: () => cancel(id) };
      const id = schedule(value => { scheduled.delete(task); resolve(value); });
      scheduled.add(task);
    });
  }
  const frame = () => scheduledWait(requestFrame, cancelFrame);
  function sendInput(key) {
    check();
    if (typeof key !== 'string' || !key) throw new TypeError('Input key must be a nonempty string');
    const value = key === 'Enter' ? 13 : key === 'Escape' ? 27 : key;
    bridge.recordInput(value, 'received');
    if (bridge.handleAudioInput(value)) {
      // Only pause needs the original F branch to redraw its console label.
      if (waiters.length && bridge.inputConsumer() === 'InterfazPausa') waiters.shift().resolve(value);
      else bridge.recordInput(value, 'consumed');
      return;
    }
    if (bridge.inputBlocked()) return;
    if (waiters.length) waiters.shift().resolve(value);
    else queue.push(value);
  }
  async function getch() {
    check(); bridge.recordInput(null, 'waiting');
    const key = queue.length ? queue.shift() : await new Promise((resolve, reject) => waiters.push({ resolve, reject }));
    check(); bridge.recordInput(key, 'consumed'); return key;
  }
  async function sleep(ms) {
    check();
    if (ms <= 0) return;
    if (ms <= 16) {
      if (now() - lastFrameTime >= 16) { await frame(); lastFrameTime = now(); }
      return;
    }
    await scheduledWait(callback => setTimeout(callback, ms), clearTimeout);
    lastFrameTime = now();
  }
  const abort = () => {
    queue.length = 0;
    waiters.splice(0).forEach(waiter => waiter.reject(cancelled()));
    for (const task of scheduled) { task.cancel(); task.reject(cancelled()); }
    scheduled.clear();
  };
  signal.addEventListener('abort', abort, { once: true });
  const shims = {
    Ref: class { constructor(value) { this.v = value; } valueOf() { return this.v; } toString() { return String(this.v); } },
    Random: class { Next(min, max) { return Math.floor(Math.random() * (max - min)) + min; } },
    CONSOLE_SCREEN_BUFFER_INFO: class { constructor() { this.dwCursorPosition = { X: 0, Y: 0 }; } },
    SetConsoleTextAttribute(handle, color) {
      const palette = [9, 12, 11, 13, 10, 14, 15, 8, 16, 4, 3, 5, 2, 6, 7, 1];
      surface.SetForegroundColor(palette[color & 15]);
      surface.SetBackgroundColor(palette[(color >> 4) & 15]);
    },
    GetStdHandle: handle => handle, system() {}, fflush() {},
    FlushConsoleInputBuffer() { queue.length = 0; return 1; },
    STD_OUTPUT_HANDLE: 1, STD_INPUT_HANDLE: 0, stdin: 0,
    toupper: c => typeof c === 'string' ? c.toUpperCase() : c >= 97 && c <= 122 ? c - 32 : c,
    Convert: { ToByte: v => Number(v) & 255, ToInt32: v => Number(v) | 0,
      ToChar: v => typeof v === 'number' ? String.fromCharCode(v) : String(v),
      ToString: String, ToBoolean: Boolean },
    _kbhit: () => queue.length ? 1 : 0, _getch: getch, Sleep: sleep,
    async scanf(format, target) {
      const maxLength = Number(String(format).match(/%(\d+)s/)?.[1] || 8);
      let text = '';
      while (true) {
        check();
        if (queue.length) {
          const key = await getch();
          if (key === 13 && text.length) break;
          if (key === 'Backspace' || key === 8 || key === '\b') {
            if (text.length) {
              text = text.slice(0, -1); surface.cursorX = Math.max(0, surface.cursorX - 1);
              surface.Write(' '); surface.cursorX = Math.max(0, surface.cursorX - 1);
            }
          } else if (typeof key === 'string' && key.length === 1 && text.length < maxLength) {
            text += key; surface.Write(key);
          }
        }
        await sleep(16);
      }
      if (target) { [...text].forEach((char, i) => { target[i] = char; }); target[text.length] = '\0'; }
      return 1;
    },
    strlen(value) {
      if (value == null || typeof value.length === 'undefined') throw new TypeError('Invalid strlen input');
      const index = typeof value === 'string' ? value.indexOf('\0') : value.findIndex(char => char === '\0' || char === 0);
      return index < 0 ? value.length : index;
    },
    GetConsoleScreenBufferInfo(handle, info) {
      if (info) info.dwCursorPosition = { X: surface.cursorX, Y: surface.cursorY };
    },
    PlaySound: (...args) => { check(); audio.play(...args); }, TEXT: text => text,
    SND_SYNC: 0, SND_ASYNC: 1, SND_NODEFAULT: 2, SND_MEMORY: 4, SND_LOOP: 8, SND_NOSTOP: 16,
  };
  return { shims, sendInput, frame, now, check,
    window: { getDevConfig: key => ({ 1: config.skipIntro ? 1 : 0, 2: config.startLevel, 3: config.skipLore ? 1 : 0 })[key] || 0 } };
}
