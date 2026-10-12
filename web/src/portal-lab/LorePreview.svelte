<script>
  import CurtainScene from '../presentation/CurtainScene.svelte';
  import LoreSheet from '../presentation/LoreSheet.svelte';
  let { level } = $props();
  let phase = $state('entering');
  let revision = $state(0);
  export function replay() { revision++; phase = 'entering'; }
</script>

<div class="lore-preview-scene">
  {#key revision}
    <CurtainScene {phase} onEntered={() => phase = 'open'} onExited={() => phase = 'closed'}>
      <LoreSheet {level} ready={phase === 'open'} onContinue={() => phase = 'exiting'} />
    </CurtainScene>
  {/key}
</div>

<style>
  .lore-preview-scene { height: 500px; }
</style>
