<script>
  import GameplayHud from '../presentation/GameplayHud.svelte';
  let { critical = false } = $props();
  let remaining = $state(critical ? 8 : 24);
  let muted = $state(false);
  let jolt = $state(0);
  let action = $state('');
  function takeStep() {
    remaining = remaining <= 1 ? 8 : remaining - 1;
    jolt++;
  }
</script>

<GameplayHud lives={critical ? 1 : 3} {remaining} {muted} {jolt}
  onMute={() => muted = !muted} onPause={() => action = 'Pause preview'} />
{#if critical}<button class="sample-action" onclick={takeStep}>Take a step</button>{/if}
{#if action}<p class="control-readout">{action}</p>{/if}
