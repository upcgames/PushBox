<script>
  import { onMount } from 'svelte';
  let { currentKey, onSelect } = $props();
  let spriteKeys = $state([]);
  onMount(async()=>{
    try{
      const res=await fetch('/pushbox_modules/maps_json/_manifest.json');
      if(res.ok){ const mf=await res.json(); spriteKeys=mf.sprites||[]; }
    }catch{}
    if(!spriteKeys.length) spriteKeys=['YouWinYouLose','ni1','dh1'];
  });
</script>

<section class="panel">
  <h3 class="panel-header">Select Sprite Matrix</h3>
  <div class="map-list">
    {#each spriteKeys as key}
      <button class="map-btn" class:active={key===currentKey} onclick={()=>onSelect(key)}>
        <span>{key}</span> <span class="dim">sprite</span>
      </button>
    {/each}
  </div>
</section>
