<script>
  import Dpad from '../components/Dpad.svelte';
  let { onDir, rewindVisible = false, trollVisible = false, rewind, troll } = $props();
</script>

<div class="gameplay-deck">
  <Dpad facelift {onDir} />
  <div class="secondary-actions">
    <div class="action-slot" data-action-slot="rewind">
      {#if rewindVisible}{@render rewind?.()}
      {:else}<div class="slot-placeholder" aria-hidden="true"></div>{/if}
    </div>
    <div class="action-slot" data-action-slot="troll">
      {#if trollVisible}{@render troll?.()}
      {:else}<div class="slot-placeholder" aria-hidden="true"></div>{/if}
    </div>
  </div>
</div>

<style>
  .gameplay-deck { width: 100%; display: flex; align-items: center; justify-content: space-between; gap: 16px; padding: 10px 24px; box-sizing: border-box; background: #000; }
  .secondary-actions { display: grid; grid-template-rows: repeat(2, 76px); justify-items: center; gap: 20px; flex: none; }
  .action-slot { width: 76px; height: 76px; display: grid; place-items: center; }
  .slot-placeholder { width: 100%; height: 100%; background: #101320; box-shadow: inset 2px 2px #20283b, inset -2px -2px #060811; }
  @media (max-width: 370px) { .gameplay-deck { padding-inline: 16px; gap: 8px; } }
</style>
