<script>
  import Button from './Button.svelte';
  import { sendInput as dispatch } from '../state/gameState.js';
  import Dpad from '../components/Dpad.svelte';
</script>

<div class="ctrl game-paused">
  <Dpad verticalOnly={true} onDir={dispatch} />
  <div class="ctrl-actions">
    <Button icon="✔" label="Select" onclick={() => dispatch('e')} />
  </div>
</div>

<style>
  .ctrl {
    background: rgba(22, 30, 46, 0.9);
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 12px;
    display: flex;
    gap: 12px;
    align-items: center;
    justify-content: space-between;
    min-height: 184px;
    height: 184px;
    box-sizing: border-box;
  }
  .game-paused { flex-direction: row; }
  .ctrl-actions { display: flex; flex-direction: column; gap: 8px; justify-content: center; }
</style>
