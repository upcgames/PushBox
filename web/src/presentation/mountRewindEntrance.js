import { mount, unmount } from 'svelte';
import RewindEntranceOverlay from './RewindEntranceOverlay.svelte';

export function mountRewindEntrance(root, surface, store, enabled = () => true) {
  // Body ownership avoids double-scaling fixed coordinates inside Inspector's
  // transformed phone frames. All measurements still belong to this runtime.
  const host = document.createElement('div'); document.body.append(host);
  const instance = mount(RewindEntranceOverlay, { target: host, props: { root, surface, store, enabled } });
  return { dispose() { unmount(instance); host.remove(); } };
}
