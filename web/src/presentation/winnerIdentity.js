import { parsePlayerNames, encodePlayerName } from './playerIdentity.js';

// Supplies original scanf targets directly, never queues keyboard characters.
export function createWinnerIdentity({ profile, store, enabled = () => true }) {
  let state = { visible: false, name: '' }, pending = null, resolve, reject, names = [], index = 0, disposed = false;
  const listeners = new Set();
  function update(patch) { state = { ...state, ...patch }; listeners.forEach(listener => listener(state)); }
  function begin() {
    if (pending || disposed) return;
    update({ visible: true, name: profile.getNames().join(' ') });
    pending = new Promise((yes, no) => { resolve = yes; reject = no; });
    // The modal can open on K consumption before the original reaches scanf.
    pending.catch(() => {});
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
      profile.save(parsed); store.setPlayerNames(parsed);
      names = parsed; index = 0;
      update({ visible: false }); resolve(parsed); return true;
    },
    read(request, target) {
      if (disposed || !enabled() || request.consumer !== 'InterfazCongratulations') return undefined;
      return (async () => {
        if (request.choices?.join(',') === '1,2') {
          begin(); await pending;
          target[0] = String(names.length); target[1] = '\0';
        } else {
          const encoded = encodePlayerName(names[index++]);
          encoded.forEach((character, position) => target[position] = character);
          target[encoded.length] = '\0';
          if (index === names.length) { pending = null; resolve = reject = null; }
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
