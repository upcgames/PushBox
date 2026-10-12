<script>
  import { onMount } from 'svelte';
  import CurtainScene from './CurtainScene.svelte';
  import LoreSheet from './LoreSheet.svelte';
  import { loreLevel, loreConfirmation } from './loreHandoff.js';
  let { store, sendInput, onClosed = () => {} } = $props();
  let level = $state(loreLevel(store.getSnapshot()));
  let request = $state(loreConfirmation(store.getSnapshot()));
  let phase = $state(level ? 'entering' : 'closed');
  let rewardSeen = $state(store.getSnapshot().trollReward.unlocked);
  let leaving = false;
  onMount(() => store.subscribe(state => {
    rewardSeen = state.trollReward.unlocked;
    request = loreConfirmation(state);
    if (state.screen?.id !== 'Lore') {
      leaving = true;
      if (phase !== 'closed') phase = 'exiting';
      else onClosed();
    } else if (!level) {
      const known = loreLevel(state);
      if (known) { level = known; phase = 'entering'; }
    }
  }));
  function continueLore() {
    const current = loreConfirmation(store.getSnapshot());
    if (!current || phase !== 'open') return;
    leaving = true; phase = 'exiting'; sendInput(current.key);
  }
  function closed() { phase = 'closed'; if (leaving) onClosed(); }
</script>

<CurtainScene {phase} onEntered={() => phase = 'open'} onExited={closed}>
  {#if level}<LoreSheet {level} {rewardSeen} ready={!!request && phase === 'open'} onContinue={continueLore} />{/if}
</CurtainScene>
