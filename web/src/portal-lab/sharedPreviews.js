import { mount, unmount } from 'svelte';
import PreviewPixelButton from './PreviewPixelButton.svelte';
import HudStudy from './HudStudy.svelte';

// Preview state is local; the assets and styles are the game's real components.
export function mountSharedPreviews(root, onPress = () => {}) {
  const instances = [];
  for (const host of root.querySelectorAll('[data-pixel-icon]')) {
    // Control studies own their mounts, including during lab hot reload.
    if (root.id !== 'control-studies' && host.closest('#control-studies')) continue;
    instances.push(mount(PreviewPixelButton, { target: host, props: {
      icon: host.dataset.pixelIcon, label: host.dataset.label,
      variant: host.dataset.variant || '', hinted: host.dataset.state === 'hinted',
      active: host.dataset.state === 'active', onPress: action => onPress(host, action),
    } }));
  }
  for (const host of root.querySelectorAll('[data-hud-study]')) {
    instances.push(mount(HudStudy, { target: host, props: { critical: host.dataset.hudStudy === 'critical' } }));
  }
  return () => instances.forEach(instance => unmount(instance));
}
