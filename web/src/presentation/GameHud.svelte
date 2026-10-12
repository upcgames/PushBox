<script>
  import { onMount } from 'svelte';
  import { controllerServices } from '../controllers/services.js';
  import GameplayHud from './GameplayHud.svelte';
  import { gameplayHudSnapshot } from './gameplayHud.js';
  const { store, sendInput, audio } = controllerServices();
  let hud = $state(gameplayHudSnapshot(store.getSnapshot()));
  let muted = $state(store.getSnapshot().audio.muted);
  let jolt = $state(0);
  let canResume = $state(false);
  onMount(() => store.subscribe(state => {
    const next = gameplayHudSnapshot(state, hud);
    if (!next) jolt = 0;
    // Console delivery can follow the movement snapshot by one animation frame.
    // A fresh attempt resets moves spent, so it must not trigger a jolt.
    else if (hud && next.level === hud.level && next.spent >= hud.spent
      && next.remaining !== null && hud.remaining !== null
      && next.remaining < hud.remaining && next.remaining < 20) jolt++;
    hud = next;
    muted = state.audio.muted;
    canResume = state.inputRequest?.consumer === 'InterfazPausa' && state.inputRequest.kind === 'key';
  }));
</script>

{#if hud}
  <GameplayHud lives={hud.lives} remaining={hud.remaining} paused={hud.paused} {canResume} {muted} {jolt}
    onMute={() => audio.setWebMuted(!store.getSnapshot().audio.muted)} onPause={() => sendInput(hud.paused ? 'Resume' : 'p')} />
{/if}
