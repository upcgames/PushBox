import { mount, unmount } from 'svelte';
import SoundButton from '../components/SoundButton.svelte';

export function mountSoundButton(host, store, audio) {
  const instance = mount(SoundButton, { target: host, props: {
    store, onToggle: () => audio.setWebMuted(!store.getSnapshot().audio.muted),
  } });
  return () => unmount(instance);
}
