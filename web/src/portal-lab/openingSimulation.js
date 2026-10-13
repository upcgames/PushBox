import { mount, unmount } from 'svelte';
import OpeningSheet from '../presentation/OpeningSheet.svelte';
import { createOpeningFlow } from '../presentation/openingFlow.js';
import { createSeenProgress } from '../state/seenProgress.js';
import { createPlayerProfile } from '../presentation/playerIdentity.js';
import { createAudioChannel } from '../audio/audioChannel.js';
import { createGameState } from '../state/gameState.js';
import { mountWarningAlarm } from '../presentation/warningAlarm.js';
import { deviceViewportMarkup, sizeDevicePreview, INSPECTOR_DEVICES } from '../inspector/deviceViewport.js';

export function mountOpeningSimulation(root) {
  root.innerHTML = `${deviceViewportMarkup('<div class="opening-preview"></div>')}<div class="viewport-size"></div><div class="simulation-toolbar"><button class="sample-action simulation-replay">Replay</button><span class="simulation-status">Loading preview</span></div>`;
  sizeDevicePreview(root, INSPECTOR_DEVICES[1]);
  const store = createGameState(), progress = createSeenProgress({ storage: null }), profile = createPlayerProfile({ storage: null });
  const audio = createAudioChannel(store, { baseUrl: import.meta.env.BASE_URL });
  const status = root.querySelector('.simulation-status');
  const flow = createOpeningFlow({ progress, profile, audio, onEnter: () => {
    flow.begin().then(names => { status.textContent = `Opening complete · ${names.join(' ')} · preview stops before gameplay`; }).catch(() => {});
  } });
  const alarm = mountWarningAlarm(flow, store.api, { baseUrl: import.meta.env.BASE_URL,
    enabled: () => !root.closest('[role=tabpanel]')?.hidden });
  const visibility = new window.MutationObserver(alarm.refresh);
  visibility.observe(root.closest('[role=tabpanel]'), { attributes: true, attributeFilter: ['hidden'] });
  const instance = mount(OpeningSheet, { target: root.querySelector('.opening-preview'), props: { flow, store: store.api, acceptKeyboard: () => false,
    onMute: () => audio.setWebMuted(!store.api.getSnapshot().audio.muted) } });
  const stop = flow.subscribe(state => {
    if (state.phase === 'hidden') return;
    status.textContent = state.phase === 'typing' ? (state.seen ? 'Seen warning · Continue reveals text' : 'First warning · wait for typing') : state.phase;
  });
  flow.setLoading(100, true);
  const replay = () => flow.setLoading(100, true);
  root.querySelector('.simulation-replay').addEventListener('click', replay);
  if (import.meta.hot) import.meta.hot.dispose(() => { stop(); visibility.disconnect(); alarm.dispose(); flow.dispose(); audio.dispose(); unmount(instance); });
}
