<script>
  let { currentKey, onSelect } = $props();
  const MAP_KEYS = ['mapa01','mapa02','mapa03','mapa04','mapa05'];
</script>

<section class="panel">
  <h3 class="panel-header">Select Level Map</h3>
  <div class="map-list">
    {#each MAP_KEYS as key}
      <button class="map-btn" class:active={key===currentKey} onclick={()=>onSelect(key)}>
        <span>MAPA {key.replace('mapa','')}</span> <span class="dim">63×80</span>
      </button>
    {/each}
  </div>
</section>
