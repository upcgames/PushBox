<script>
  import CurtainScene from '../presentation/CurtainScene.svelte';
  import InstructionSheet from '../presentation/InstructionSheet.svelte';
  let phase = $state('entering');
  let revision = $state(0);
  export function replay() { revision++; phase = 'entering'; }
</script>

{#key revision}
<CurtainScene {phase} onEntered={() => phase = 'open'} onExited={() => phase = 'closed'}>
  <InstructionSheet ready={phase === 'open'} onContinue={() => phase = 'exiting'} />
</CurtainScene>
{/key}
