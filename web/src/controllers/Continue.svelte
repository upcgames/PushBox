<script>
  import { controllerServices } from './services.js';
  const { store: GameState, sendInput: dispatch } = controllerServices();
  import ContinueButton from '../components/ContinueButton.svelte';
</script>

<div class="ctrl continue-ctrl">
  <ContinueButton onclick={() => dispatch(GameState.getSnapshot().inputRequest?.key || 'e')} />
</div>

<style>
  .ctrl {
    background: #000;
    padding: 12px;
    display: flex;
    flex-direction: column;
    gap: 12px;
    align-items: center;
    justify-content: center;
    min-height: 160px;
    height: 160px;
    box-sizing: border-box;
  }
  .continue-ctrl { flex-direction: row; justify-content: center; gap: 12px; }
</style>
