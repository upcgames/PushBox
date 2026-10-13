import { parsePlayerNames, encodePlayerName } from './playerIdentity.js';

// Supplies original scanf targets directly, never queues keyboard characters.
export function createWinnerIdentity({ profile, store, enabled = () => true }) {
  let state = { visible: false, name: '', rejected: false }, pending = null, resolve, reject, names = [], index = 0, disposed = false;
  let nameTargets = new WeakMap(), retryIndex = null;
  const listeners = new Set();
  function update(patch) { state = { ...state, ...patch }; listeners.forEach(listener => listener(state)); }
  function open(name, retry = null) {
    retryIndex = retry;
    pending = new Promise((yes, no) => { resolve = yes; reject = no; });
    // The modal can open on K consumption before the original reaches scanf.
    pending.catch(() => {});
    update({ visible: true, name, rejected: retry !== null });
  }
  function begin() {
    if (pending || disposed) return;
    open(profile.getNames().join(' '));
  }
  return {
    accepts: consumer => !disposed && enabled() && consumer === 'InterfazCongratulations',
    getSnapshot: () => state,
    subscribe(listener) { listeners.add(listener); listener(state); return () => listeners.delete(listener); },
    begin,
    submit(value) {
      if (!state.visible) return false;
      const parsed = parsePlayerNames(value);
      if (!parsed.length) return false;
      if (retryIndex !== null) names[retryIndex] = parsed[0];
      else { names = parsed; index = 0; nameTargets = new WeakMap(); }
      profile.save(names); store.setPlayerNames(names);
      retryIndex = null;
      update({ visible: false, rejected: false }); resolve(names); return true;
    },
    read(request, target) {
      if (disposed || !enabled() || request.consumer !== 'InterfazCongratulations') return undefined;
      return (async () => {
        if (request.choices?.join(',') === '1,2') {
          begin(); await pending;
          target[0] = String(names.length); target[1] = '\0';
        } else {
          let slot = nameTargets.get(target);
          if (slot !== undefined) {
            // A repeated scanf target is an original validation retry, not the
            // next name. Reopen just this field and retain the other name/count.
            open('', slot); await pending;
          } else {
            slot = index++;
            nameTargets.set(target, slot);
          }
          if (slot >= names.length) throw new Error('Unexpected original name input target');
          const encoded = encodePlayerName(names[slot]);
          target.length = encoded.length + 1;
          encoded.forEach((character, position) => target[position] = character);
          target[encoded.length] = '\0';
          if (slot === names.length - 1) { pending = null; resolve = reject = null; }
        }
        return 1;
      })();
    },
    dispose() {
      disposed = true; update({ visible: false }); reject?.(new DOMException('Name entry stopped', 'AbortError'));
      pending = null; resolve = reject = null; listeners.clear();
    },
  };
}
