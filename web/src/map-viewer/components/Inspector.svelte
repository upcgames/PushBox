<script>
  let { coords, tile, collision } = $props();
</script>

<section class="panel inspector-panel">
  <h3 class="panel-header">Hover Inspector</h3>
  <div class="inspector-details">
    <div class="inspector-row"><span class="lbl">Cell Coords:</span> <span class="val">{coords}</span></div>
    <div class="inspector-row"><span class="lbl">Visual Tile ID:</span> <span class="val">{tile}</span></div>
    <div class="inspector-row"><span class="lbl">Collision Type:</span> <span class="val">{collision}</span></div>
  </div>
</section>
