<script>
  import { controllerServices } from './services.js';
  const { store: GameState, sendInput: dispatch, audio } = controllerServices();
  import Button from './Button.svelte';
  function sendChoice(ch) {
    dispatch(ch);
    dispatch('Enter');
  }
</script>

<div class="ctrl onetwo-ctrl">
  <Button label="1" variant="big" onclick={() => sendChoice('1')} />
  <Button label="2" variant="big" onclick={() => sendChoice('2')} />
</div>

<style>
  .ctrl {
    background: #000;
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 12px;
    display: flex;
    flex-direction: row;
    gap: 12px;
    align-items: center;
    justify-content: center;
    min-height: 160px;
    height: 160px;
    box-sizing: border-box;
  }
  .onetwo-ctrl { gap: 12px; }
</style>
