<script>
  import Button from './Button.svelte';
  function dispatch(key) {
    const evt = new window.KeyboardEvent('keydown', { key, bubbles: true });
    window.dispatchEvent(evt);
  }
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
    background: rgba(22, 30, 46, 0.9);
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
