<script>
  let { selections, storageKey, onRemove, onClear, onCopy } = $props();
</script>

<section class="panel">
  <h3 class="panel-header">Selections <span style="opacity:0.6;font-weight:400">{selections.length}</span></h3>
  <div style="display:flex;flex-direction:column;gap:8px;max-height:200px;overflow:auto">
    {#each selections as s, idx}
      <div style="display:flex;align-items:center;justify-content:space-between;background:rgba(255,255,255,0.04);border:1px solid var(--bg-panel-border);border-radius:8px;padding:8px 10px;font-family:var(--font-code);font-size:0.78rem">
        <span><b style="color:var(--accent-cyan)">#{idx+1}</b> ({s.x1},{s.y1}) → ({s.x2},{s.y2}) <span style="color:var(--text-muted)">{s.x2-s.x1+1}×{s.y2-s.y1+1}</span></span>
        <button class="btn-icon" style="width:24px;height:24px;font-size:0.8rem" onclick={()=>onRemove(idx)}>✕</button>
      </div>
    {/each}
  </div>
  <div style="display:flex;gap:8px;margin-top:10px">
    <button class="btn-icon" style="flex:1;height:32px" onclick={onClear}>Clear All</button>
    <button class="btn-icon" style="flex:1;height:32px" onclick={onCopy}>Copy</button>
  </div>
  <div style="font-size:0.75rem;color:var(--text-muted);margin-top:8px">Tip: Toggle ✏️ then drag on canvas. Coords are console <code>80×63</code> (x1,y1 → x2,y2).</div>
</section>
