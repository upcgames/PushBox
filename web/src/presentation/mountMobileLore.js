import { mount, unmount } from 'svelte';
import RuntimeLore from './RuntimeLore.svelte';
import './mobileLore.css';

export function mountMobileLore(root, store, sendInput = store.sendInput, enabled = () => true) {
  let host = null, instance = null, runtimeExited = false, curtainClosed = false;
  function hide() {
    if (instance) unmount(instance);
    instance = null; host?.remove(); host = null;
    runtimeExited = false; curtainClosed = false;
    delete root.dataset.mobileLore;
  }
  function refresh() {
    const screen = store.getSnapshot().screen?.id;
    if (!enabled()) { hide(); return; }
    if (screen !== 'Lore') {
      if (!instance) return;
      runtimeExited = true;
      if (curtainClosed) hide();
      return;
    }
    if (instance && runtimeExited) hide();
    if (instance) return;
    root.dataset.mobileLore = 'on';
    const currentHost = document.createElement('div');
    host = currentHost; host.className = 'mobile-lore-host'; root.append(host);
    instance = mount(RuntimeLore, { target: host, props: { store, sendInput,
      onClosed() { if (host !== currentHost) return; curtainClosed = true; if (runtimeExited) hide(); },
    } });
  }
  const stop = store.select(state => state.screen?.id, refresh);
  const stopErrors = store.on('runtimeError', hide);
  return { refresh, dispose() { stop(); stopErrors(); hide(); } };
}
