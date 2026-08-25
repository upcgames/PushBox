<script>
  import Button from './Button.svelte';
  function dispatch(key) {
    const evt = new window.KeyboardEvent('keydown', { key, bubbles: true });
    window.dispatchEvent(evt);
  }
</script>

<div class="ctrl dpad">
  <div class="dpad-grid">
    <button class="dpad-btn up" onclick={() => dispatch('w')}>▲</button>
    <div class="dpad-center"></div>
    <button class="dpad-btn down" onclick={() => dispatch('s')}>▼</button>
  </div>
  <div class="dpad-actions">
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
    flex-direction: column;
    gap: 12px;
    align-items: center;
    justify-content: center;
    min-height: 160px;
    height: 160px;
    box-sizing: border-box;
  }
  .dpad { flex-direction: row; justify-content: space-around; }
  .dpad-grid {
    display: grid;
    grid-template-columns: 48px 48px 48px;
    grid-template-rows: 48px 48px 48px;
    gap: 4px;
    align-items: center;
    justify-items: center;
  }
  .dpad-grid .up { grid-column: 2; grid-row: 1; }
  .dpad-grid .down { grid-column: 2; grid-row: 3; }
  .dpad-center { grid-column: 2; grid-row: 2; width: 32px; height: 32px; background: var(--border); border-radius: 50%; }
  .dpad-btn { width: 48px; height: 48px; background: var(--card-bg); border: 1px solid var(--accent); color: var(--text); border-radius: 8px; font-size: 1.2rem; cursor: pointer; }
  .dpad-actions { display: flex; flex-direction: column; gap: 8px; justify-content: center; }
</style>
