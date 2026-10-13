import { mount, unmount } from 'svelte';
import NativeNameModal from './NativeNameModal.svelte';
import { createWinnerIdentity } from './winnerIdentity.js';
import OpeningSheet from './OpeningSheet.svelte';
import { createOpeningFlow } from './openingFlow.js';
import { createSeenProgress } from '../state/seenProgress.js';
import { createPlayerProfile } from './playerIdentity.js';
import { mountSeenDestinations } from './seenDestinations.js';
import { mountWinnerActions } from './winnerActions.js';

export function mountMobileOpening(root, store, audio, { enabled = () => true,
  surface, progress = createSeenProgress(), profile = createPlayerProfile(), onEnter = () => {} } = {}) {
  const host = document.createElement('div'); host.className = 'mobile-opening-host'; host.hidden = true; root.append(host);
  const acceptKeyboard = () => enabled() && (!root.closest('.preview-card') || root.closest('.preview-card').classList.contains('selected'));
  const winnerNames = createWinnerIdentity({ profile, store, enabled });
  const winnerActions = mountWinnerActions(store, { enabled });
  const modalHost = document.createElement('div'); modalHost.className = 'mobile-name-modal-host'; modalHost.hidden = true; root.append(modalHost);
  const modal = mount(NativeNameModal, { target: modalHost, props: { flow: winnerNames, acceptKeyboard } });
  const stopModal = winnerNames.subscribe(state => {
    modalHost.hidden = !state.visible;
    if (state.visible) root.dataset.mobileNameModal = 'on'; else delete root.dataset.mobileNameModal;
  });
  const stopReader = store.registerNativeTextReader(winnerNames.read, winnerNames.accepts);
  const stopError = store.on('runtimeError', winnerNames.dispose);
  const stopInput = store.on('input:consumed', ({ key, request }) => {
    if (enabled() && request?.consumer === 'InterfazCongratulations' && request.kind === 'key' && String(key).toLowerCase() === 'k') winnerNames.begin();
  });
  const flow = createOpeningFlow({ progress, profile, audio, onEnter });
  const stopVisits = mountSeenDestinations(store, progress, enabled);
  const instance = mount(OpeningSheet, { target: host, props: { flow, enabled, acceptKeyboard,
    onMute: () => audio.setWebMuted(!store.getSnapshot().audio.muted) } });
  function refresh() {
    winnerActions.refresh();
    surface?.setDrawScopeHidden('winner-prompts', enabled());
    const visible = enabled() && !['hidden', 'complete'].includes(flow.getSnapshot().phase);
    host.hidden = !visible;
    if (visible) root.dataset.mobileOpening = 'on'; else delete root.dataset.mobileOpening;
  }
  const stop = flow.subscribe(refresh);
  const pointer = window.matchMedia('(pointer: coarse)');
  pointer.addEventListener('change', refresh);
  return {
    enabled, refresh, getNames: profile.getNames, begin: flow.begin, hideLoading: flow.hideLoading, setLoading: flow.setLoading, takeDestination: flow.takeDestination,
    dispose() { pointer.removeEventListener('change', refresh); winnerActions.dispose(); stopVisits(); stopReader(); stopInput(); stopError(); winnerNames.dispose(); stopModal(); unmount(modal); modalHost.remove(); delete root.dataset.mobileNameModal; surface?.setDrawScopeHidden('winner-prompts', false); stop(); flow.dispose(); unmount(instance); host.remove(); delete root.dataset.mobileOpening; },
  };
}
