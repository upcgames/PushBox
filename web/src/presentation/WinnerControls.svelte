<script>
  import '../styles/confirmationButton.css';
  let { onInput, allowRename = true } = $props();
</script>

<div class="winner-controls" class:exit-only={!allowRename}>
  {#if allowRename}
  <button type="button" class="pixel-confirmation" onclick={() => onInput?.('k')}>
    <svg viewBox="0 0 24 24" aria-hidden="true"><path d="m15 3 6 6-11 11H4v-6L15 3Zm-9 12v3h3l8-8-3-3-8 8Z" /></svg>
    <span>Cambiar<br />Nombre</span>
  </button>
  {/if}
  <button type="button" class="pixel-confirmation" onclick={() => onInput?.('e')}>
    <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M3 3h10v3H6v12h7v3H3V3Zm12 4h3l5 5-5 5h-3l3-3H9v-4h9l-3-3Z" /></svg>
    <span>Salir</span>
  </button>
</div>

<style>
  .winner-controls { width: 100%; display: grid; grid-template-columns: repeat(2, minmax(0, 1fr)); align-items: center; gap: 16px; padding: 20px; box-sizing: border-box; min-height: 160px; background: #000; }
  .winner-controls.exit-only { grid-template-columns: minmax(0, 160px); justify-content: center; }
  button { min-width: 0; display: flex; flex-direction: column; align-items: center; gap: 14px; padding: 16px; font-size: 10px; }
  span { max-width: 100%; overflow-wrap: anywhere; text-align: center; }
  svg { width: 24px; height: 24px; fill: currentColor; shape-rendering: crispEdges; }
</style>
