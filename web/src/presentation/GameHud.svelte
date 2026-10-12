<script>
  import { onMount } from 'svelte';
  import { controllerServices } from '../controllers/services.js';
  import GameplayHud from './GameplayHud.svelte';
  import { gameplayHudSnapshot } from './gameplayHud.js';
  const { store, sendInput, audio } = controllerServices();
  let hud = $state(gameplayHudSnapshot(store.getSnapshot()));
  let muted = $state(store.getSnapshot().audio.muted);
  let jolt = $state(0);
  onMount(() => store.subscribe(state => {
    const next = gameplayHudSnapshot(state);
    if (!next) jolt = 0;
    // Console delivery can follow the movement snapshot by one animation frame.
    // A fresh attempt resets moves spent, so it must not trigger a jolt.
    else if (hud && next.level === hud.level && next.spent >= hud.spent
      && next.remaining !== null && hud.remaining !== null
      && next.remaining < hud.remaining && next.remaining < 20) jolt++;
    hud = next;
    muted = state.audio.muted;
  }));
</script>

{#if hud}
  <GameplayHud lives={hud.lives} remaining={hud.remaining} {muted} {jolt}
    onMute={() => audio.setWebMuted(!store.getSnapshot().audio.muted)} onPause={() => sendInput('p')} />
{/if}
