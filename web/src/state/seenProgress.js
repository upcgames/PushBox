// Browser persistence for things the player has actually encountered.
// Preview callers can supply null storage to keep progression local.
export function createSeenProgress({ storage, key = 'pushboxSeen' } = {}) {
  if (storage === undefined) {
    try { storage = window.localStorage; } catch { storage = null; }
  }
  let seen = {};
  try {
    const saved = JSON.parse(storage?.getItem(key) || '{}');
    if (saved && typeof saved === 'object' && !Array.isArray(saved)) seen = saved;
  } catch {}
  const listeners = new Set();
  const notify = () => { for (const listener of listeners) listener(); };
  function persist() {
    try { storage?.setItem(key, JSON.stringify(seen)); } catch {}
    notify();
  }
  function storageChanged(event) {
    if ((event.key !== key && event.key !== null) || event.storageArea !== storage) return;
    try {
      const saved = JSON.parse(storage?.getItem(key) || '{}');
      seen = saved && typeof saved === 'object' && !Array.isArray(saved) ? saved : {};
      notify();
    } catch {}
  }
  const canListen = storage && typeof window !== 'undefined' && window.addEventListener;
  return {
    has: name => seen[name] === true,
    getSnapshot: () => Object.freeze({ ...seen }),
    mark(name) {
      if (seen[name] === true) return;
      seen = { ...seen, [name]: true };
      persist();
    },
    clear(names) {
      if (names === undefined) seen = {};
      else {
        seen = { ...seen };
        for (const name of Array.isArray(names) ? names : [names]) delete seen[name];
      }
      persist();
    },
    subscribe(listener) {
      if (!listeners.size && canListen) window.addEventListener('storage', storageChanged);
      listeners.add(listener);
      return () => {
        listeners.delete(listener);
        if (!listeners.size && canListen) window.removeEventListener('storage', storageChanged);
      };
    },
  };
}
