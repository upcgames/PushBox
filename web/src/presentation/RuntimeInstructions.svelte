<script>
  import { onMount } from 'svelte';
  import CurtainScene from './CurtainScene.svelte';
  import InstructionSheet from './InstructionSheet.svelte';
  import { instructionConfirmation } from './instructionHandoff.js';
  let { store, sendInput, onClosed = () => {} } = $props();
  let request = $state(instructionConfirmation(store.getSnapshot()));
  let phase = $state('entering');
  onMount(() => store.subscribe(state => {
    request = instructionConfirmation(state);
    // Keyboard confirmation uses the same exit as the in-screen button.
    if (state.screen?.id !== 'InterfazInstructions' && phase !== 'closed') phase = 'exiting';
  }));
  function continueInstructions() {
    const current = instructionConfirmation(store.getSnapshot());
    if (!current || phase !== 'open') return;
    phase = 'exiting';
    sendInput(current.key);
  }
  function closed() {
    phase = 'closed';
    onClosed();
  }
</script>

<CurtainScene {phase} onEntered={() => phase = 'open'} onExited={closed}>
  <InstructionSheet ready={!!request && phase === 'open'} onContinue={continueInstructions} />
</CurtainScene>
