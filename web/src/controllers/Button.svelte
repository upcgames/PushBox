<script>
  let { label = '', icon = '', variant = '', onclick } = $props();
</script>

<button class="btn {variant}" onclick={onclick}>
  {#if icon}<span class="icon">{icon}</span>{/if}
  {#if label}<span class="label">{label}</span>{/if}
</button>

<style>
  .btn {
    background: var(--accent);
    color: #000;
    border: none;
    padding: 10px 18px;
    border-radius: 8px;
    font-weight: 700;
    font-family: var(--font);
    cursor: pointer;
    min-height: 42px;
    display: inline-flex;
    align-items: center;
    justify-content: center;
    gap: 6px;
    font-size: 0.95rem;
    line-height: 1;
    box-sizing: border-box;
  }
  .btn.primary { background: var(--accent); }
  .btn.big { font-size: 1.6rem; padding: 16px 32px; min-height: 56px; }
  .btn.troll .icon { font-size: 1.7em; }
  .icon { font-size: 1.1em; }
</style>
