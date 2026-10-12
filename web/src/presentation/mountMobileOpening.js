import { mount, unmount } from 'svelte';
import OpeningSheet from './OpeningSheet.svelte';
import { createOpeningFlow } from './openingFlow.js';
import { createSeenProgress } from '../state/seenProgress.js';
import { createPlayerProfile } from './playerIdentity.js';

export function mountMobileOpening(root, store, audio, { enabled = () => true,
  progress = createSeenProgress(), profile = createPlayerProfile(), onEnter = () => {} } = {}) {
  const host = document.createElement('div'); host.className = 'mobile-opening-host'; host.hidden = true; root.append(host);
  const flow = createOpeningFlow({ progress, profile, audio, onEnter });
  const instance = mount(OpeningSheet, { target: host, props: { flow, enabled, acceptKeyboard: () => enabled() && (!root.closest('.preview-card') || root.closest('.preview-card').classList.contains('selected')),
    onMute: () => audio.setWebMuted(!store.getSnapshot().audio.muted) } });
  function refresh() {
    const visible = enabled() && !['hidden', 'complete'].includes(flow.getSnapshot().phase);
    host.hidden = !visible;
    if (visible) root.dataset.mobileOpening = 'on'; else delete root.dataset.mobileOpening;
  }
  const stop = flow.subscribe(refresh);
  return {
    enabled, refresh, getNames: profile.getNames, begin: flow.begin, hideLoading: flow.hideLoading, setLoading: flow.setLoading,
    dispose() { stop(); flow.dispose(); unmount(instance); host.remove(); delete root.dataset.mobileOpening; },
  };
}
