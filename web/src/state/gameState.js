const owned = new WeakSet();
function immutable(value) {
  if (!value || typeof value !== 'object') return value;
  if (owned.has(value)) return value;
  const copy = Array.isArray(value) ? value.map(immutable) : Object.fromEntries(
    Object.entries(value).map(([key, item]) => [key, immutable(item)])
  );
  owned.add(copy);
  return Object.freeze(copy);
}

export function createGameState(inputCommand = sendInput) {
  const presentationOverrides = new Map();
  let nativeTextReader = null;
  let acceptsNativeText = () => false;
  let state = immutable({ version: 0, inputRequest: null, screen: null, game: null,
    input: null, playerNames: [], playerDrawing: null, playerAnimation: null, undoHint: false, undoHintSource: null, rewindEntranceActive: false, rewindDiscovery: { visible: false, entrancePending: false }, winnerActionsBlocked: false, trollActive: false, trollReward: { unlocked: false, hinted: false }, audio: { muted: false }, console: { cols: 80, rows: 63, tileSize: 14, lines: [] } });
  const listeners = new Map(), subscribers = new Set();
  let sequence = 0;
  const notifications = [];
  let notifying = false;
  const safely = (fn, ...args) => {
    try { fn(...args); } catch (error) { console.warn('[GameState] consumer failed:', error); }
  };
  function deliver(notification) {
    notifications.push(notification);
    if (notifying) return;
    notifying = true;
    try { while (notifications.length) notifications.shift()(); }
    finally { notifying = false; }
  }
  function on(type, fn) {
    if (!listeners.has(type)) listeners.set(type, new Set());
    listeners.get(type).add(fn);
    return () => listeners.get(type)?.delete(fn);
  }
  function event(type, payload, version = state.version) {
    const detail = immutable(payload);
    const envelope = immutable({ sequence: ++sequence, type, payload: detail, version });
    deliver(() => {
      for (const fn of [...(listeners.get(type) || [])]) safely(fn, detail);
      for (const fn of [...(listeners.get('*') || [])]) safely(fn, envelope);
    });
  }
  function publish(patch, reason = 'state') {
    const previous = state;
    state = immutable({ ...state, ...patch, version: state.version + 1 });
    const next = state;
    deliver(() => {
      for (const fn of [...subscribers]) safely(fn, next, previous, reason);
      event(reason, next, next.version);
    });
  }
  function subscribe(fn) {
    subscribers.add(fn);
    safely(fn, state, null, 'initial');
    return () => subscribers.delete(fn);
  }
  function select(selector, fn, equal = Object.is) {
    let initialized = false, selected;
    return subscribe(next => {
      const value = selector(next);
      if (!initialized || !equal(selected, value)) {
        const previous = selected;
        selected = value; initialized = true;
        fn(value, previous);
      }
    });
  }
  function setTrollReward(reward) {
    if (state.trollReward.unlocked === reward.unlocked && state.trollReward.hinted === reward.hinted) return;
    publish({ trollReward: reward }, 'trollRewardChanged');
  }
  function useTrollReward() {
    if (!state.trollReward.unlocked) return;
    publish({ trollReward: { unlocked: true, hinted: false } }, 'trollRewardUsed');
  }
  const api = Object.freeze({ getSnapshot: () => state, subscribe, select, on,
    setUndoHint(hinted, source = null) {
      const undoHintSource = hinted ? source : null;
      if (state.undoHint !== !!hinted || JSON.stringify(state.undoHintSource ?? null) !== JSON.stringify(undoHintSource)) {
        publish({ undoHint: !!hinted, undoHintSource }, 'undoHintChanged');
      }
    },
    setRewindEntranceActive(active) {
      if (!!state.rewindEntranceActive !== !!active) publish({ rewindEntranceActive: !!active }, 'rewindEntranceChanged');
    },
    reportRewindRecovery(detail) { event('rewindRecovered', detail); },
    setRewindDiscovery(next) {
      if (state.rewindDiscovery.visible !== next.visible || state.rewindDiscovery.entrancePending !== next.entrancePending) {
        publish({ rewindDiscovery: next }, 'rewindDiscoveryChanged');
      }
    },
    acknowledgeRewindEntrance() { event('rewindEntrancePlayed', {}); },
    setWinnerActionsBlocked(blocked) { if (state.winnerActionsBlocked !== !!blocked) publish({ winnerActionsBlocked: !!blocked }, 'winnerActionsChanged'); },
    registerPresentationOverride(consumer, enabled = () => true) {
      const registration = { enabled };
      presentationOverrides.set(consumer, registration);
      return () => { if (presentationOverrides.get(consumer) === registration) presentationOverrides.delete(consumer); };
    },
    hasPresentationOverride: consumer => !!presentationOverrides.get(consumer)?.enabled(),
    registerNativeTextReader(reader, accepts = () => false) {
      nativeTextReader = reader; acceptsNativeText = accepts;
      return () => { if (nativeTextReader === reader) { nativeTextReader = null; acceptsNativeText = () => false; } };
    },
    hasNativeTextReader: consumer => !!nativeTextReader && acceptsNativeText(consumer),
    readNativeText: (request, target) => nativeTextReader?.(request, target),
    setPlayerNames: names => publish({ playerNames: names }, 'playerNamesChanged'), setTrollReward, useTrollReward, setTrollActive: active => publish({ trollActive: !!active }, 'trollChanged'), sendInput: inputCommand });
  return { api, publish, event };
}

const store = createGameState();
export const GameState = store.api;
export const runtimeState = Object.freeze({ publish: store.publish, event: store.event });
// UI commands travel through the existing keyboard path, with identical semantics.
export function sendInput(key) {
  if (typeof key !== 'string' || !key) throw new TypeError('Input key must be a nonempty string');
  window.dispatchEvent(new window.KeyboardEvent('keydown', { key, bubbles: true }));
}
if (typeof window !== 'undefined') window.GameState = GameState;
