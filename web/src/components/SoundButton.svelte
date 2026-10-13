<script>
  import { onMount } from 'svelte';
  import PixelButton from './PixelButton.svelte';
  let { store, onToggle } = $props();
  let muted = $state(store.getSnapshot().audio.muted);
  onMount(() => store.select(state => state.audio.muted, next => muted = next));
</script>

<PixelButton icon="sound" label={muted ? 'Unmute' : 'Mute'} variant={muted ? 'utility muted' : 'utility'} pressed={muted} onclick={onToggle} />
