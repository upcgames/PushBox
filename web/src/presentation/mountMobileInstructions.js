import { mount, unmount } from 'svelte';
import RuntimeInstructions from './RuntimeInstructions.svelte';
import './mobileInstructions.css';

// Follow the original screen lifecycle; never skip or replace its function.
export function mountMobileInstructions(root, store, sendInput = store.sendInput, enabled = () => true) {
  const stopPresentation = store.registerPresentationOverride('InterfazInstructions', enabled);
  let host = null, instance = null, runtimeExited = false, curtainClosed = false;
  function hide() {
    if (instance) unmount(instance);
    instance = null;
    host?.remove(); host = null;
    runtimeExited = false; curtainClosed = false;
    delete root.dataset.mobileInstructions;
  }
  function refresh() {
    const screen = store.getSnapshot().screen?.id;
    if (!enabled()) { hide(); return; }
    if (screen !== 'InterfazInstructions') {
      if (!instance) return;
      // MenuPrincipal owns the fade AFTER InterfazInstructions returns. Keep
      // the closed curtain until both that exit and our visual closure finish.
      runtimeExited = screen !== 'MenuPrincipal';
      if (runtimeExited && curtainClosed) hide();
      return;
    }
    if (instance) return;
    root.dataset.mobileInstructions = 'on';
    const currentHost = document.createElement('div');
    host = currentHost;
    host.className = 'mobile-instructions-host';
    root.append(host);
    instance = mount(RuntimeInstructions, { target: host, props: { store, sendInput,
      onClosed() {
        if (host !== currentHost) return;
        curtainClosed = true;
        if (runtimeExited) hide();
      },
    } });
  }
  const stop = store.select(state => state.screen?.id, refresh);
  const stopErrors = store.on('runtimeError', hide);
  return { refresh, dispose() { stopPresentation(); stop(); stopErrors(); hide(); } };
}
