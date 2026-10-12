import { mount, unmount } from 'svelte';
import '../styles/gameplayControls.css';
import GameHud from './GameHud.svelte';
import { showsGameplayHud } from './gameplayHud.js';
import { SESSION_CONTEXT } from '../controllers/services.js';

// The actual phone page and inspector mount the same HUD with session services.
export function mountGameplayHud(root, store, services) {
  const host = document.createElement('div');
  host.className = 'mobile-gameplay-hud-host';
  root.querySelector('.console-frame').before(host);
  const instance = mount(GameHud, {
    target: host,
    ...(services ? { context: new Map([[SESSION_CONTEXT, services]]) } : {}),
  });
  const stop = store.select(showsGameplayHud, visible => {
    host.hidden = !visible;
    if (visible) root.dataset.mobileGameplay = 'on';
    else delete root.dataset.mobileGameplay;
  });
  return () => { stop(); unmount(instance); host.remove(); delete root.dataset.mobileGameplay; };
}
