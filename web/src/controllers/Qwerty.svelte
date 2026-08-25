<script>
  import Button from './Button.svelte';
  const ROWS = ["QWERTYUIOP","ASDFGHJKL","ZXCVBNM"];
  function dispatch(key) {
    const evt = new window.KeyboardEvent('keydown', { key, bubbles: true });
    window.dispatchEvent(evt);
  }
</script>

<div class="ctrl qwerty-ctrl">
  <div class="qwerty-main">
    <div class="qwerty-grid">
      {#each ROWS as row}
        <div class="qrow">
          {#each [...row] as ch}
            <button class="qkey" onclick={() => dispatch(ch.toLowerCase())}>{ch}</button>
          {/each}
        </div>
      {/each}
    </div>
    <button class="qkey wide side-delete" onclick={() => dispatch('Backspace')}>⌫</button>
  </div>
  <Button icon="✔" label="Enter" onclick={() => dispatch('Enter')} />
</div>

<style>
  .ctrl {
    background: rgba(22, 30, 46, 0.9);
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 8px 12px;
    display: flex;
    flex-direction: column;
    gap: 6px;
    align-items: center;
    justify-content: center;
    min-height: 160px;
    height: 160px;
    box-sizing: border-box;
  }
  .qwerty-ctrl { gap: 6px; }
  .qwerty-main { display: flex; flex-direction: row; gap: 4px; align-items: center; justify-content: center; }
  .qwerty-grid { display: flex; flex-direction: column; gap: 2px; }
  .qrow { display: flex; gap: 3px; justify-content: center; }
  .qkey { min-width: 26px; height: 32px; background: var(--card-bg); border: 1px solid var(--border); color: var(--text); border-radius: 6px; font-family: 'Px437', monospace; cursor: pointer; font-size: 0.85rem; }
  .qkey.wide { min-width: 44px; }
  .side-delete { align-self: stretch; height: auto; min-height: 100px; }
</style>
