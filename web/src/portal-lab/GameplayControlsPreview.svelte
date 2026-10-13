<script>
  import GameplayDeck from '../presentation/GameplayDeck.svelte';
  import PreviewPixelButton from './PreviewPixelButton.svelte';
  let rewindVisible = $state(false), trollVisible = $state(false);
  let readout = $state('Tap a control');
  const pressed = action => readout = action;
</script>

<div class="slot-choices" role="group" aria-label="Gameplay button visibility">
  <label><input type="checkbox" bind:checked={rewindVisible}> Rewind visible</label>
  <label><input type="checkbox" bind:checked={trollVisible}> Carita visible</label>
</div>
<div class="preview-scroll">
  <div class="control-study gameplay-preview">
    <div class="control-topbar">
      <span>PUSHBOX</span>
      <PreviewPixelButton icon="sound" label="Mute" variant="utility" onPress={pressed} />
      <PreviewPixelButton icon="pause" label="Pause" variant="utility" onPress={pressed} />
    </div>
    <GameplayDeck {rewindVisible} {trollVisible} onDir={key => pressed({ w: 'Up', a: 'Left', s: 'Down', d: 'Right' }[key])}>
      {#snippet rewind()}<PreviewPixelButton icon="hourglass" label="Retroceder" variant="rewind-hourglass" onPress={pressed} />{/snippet}
      {#snippet troll()}<PreviewPixelButton icon="troll" label="¿Premio?" variant="face" onPress={pressed} />{/snippet}
    </GameplayDeck>
    <p class="control-readout" aria-live="polite">{readout}</p>
  </div>
</div>

<style>
  .slot-choices { display: flex; flex-wrap: wrap; gap: 16px; margin: 0 0 16px; font-size: 13px; color: #b7b3c9; }
  label { display: flex; align-items: center; gap: 8px; cursor: pointer; }
  input { accent-color: #eab308; }
  .preview-scroll { overflow-x: auto; }
  .gameplay-preview { width: 360px; min-width: 360px; max-width: none; padding: 0; }
  .control-topbar { margin: 0 16px; padding-top: 16px; }
  .control-readout { margin: 0; padding: 16px; }
</style>
