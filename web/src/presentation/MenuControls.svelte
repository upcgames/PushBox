<script>
  import Dpad from '../components/Dpad.svelte';
  import '../styles/confirmationButton.css';
  let { onInput } = $props();
</script>

<div class="mobile-menu-controls">
  <Dpad facelift verticalOnly onDir={onInput} />
  <button type="button" class="pixel-confirmation menu-select" onclick={() => onInput?.('e')}>
    <svg viewBox="0 0 24 24" aria-hidden="true"><path d="m3 12 4-4 4 4 7-7 4 4-11 11-8-8Z" /></svg>
    <span>Seleccionar</span>
  </button>
</div>

<style>
  .mobile-menu-controls {
    width: 100%;
    min-height: 222px;
    display: grid;
    grid-template-columns: repeat(2, minmax(0, 1fr));
    align-items: center;
    justify-items: center;
    gap: 16px;
    padding: 12px clamp(8px, 4%, 20px);
    box-sizing: border-box;
    background: #080914;
  }
  .menu-select { display: flex; flex-direction: column; align-items: center; gap: 14px; max-width: 100%; min-width: 0; padding: 16px; font-size: 10px; box-sizing: border-box; }
  .menu-select span { max-width: 100%; overflow-wrap: anywhere; }
  .menu-select svg { width: 24px; height: 24px; fill: currentColor; shape-rendering: crispEdges; }
</style>
