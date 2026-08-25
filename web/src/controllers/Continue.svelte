<script>
  import Button from './Button.svelte';
  function dispatch(key) {
    const evt = new window.KeyboardEvent('keydown', { key, bubbles: true });
    window.dispatchEvent(evt);
  }
</script>

<div class="ctrl continue-ctrl">
  <Button icon="▶" label="Continue" onclick={() => dispatch('e')} />
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
  .continue-ctrl { flex-direction: row; justify-content: center; gap: 12px; }
</style>
