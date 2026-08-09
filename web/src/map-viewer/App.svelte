<script>
  import { onMount } from 'svelte';
  import MapsPanel from './components/MapsPanel.svelte';
  import SpritesPanel from './components/SpritesPanel.svelte';
  import Viewport from './components/Viewport.svelte';
  import Inspector from './components/Inspector.svelte';
  import Selections from './components/Selections.svelte';
  import './viewer.css';

  let currentMode = $state('maps');
  let currentMapKey = $state('mapa01');
  let currentSpriteKey = $state(null);
  let currentMapData = $state(null);
  let collisionData = $state(null);
  let zoomScale = $state(1.0);
  let isDrawMode = $state(false);
  let selections = $state([]);
  let inspCoords = $state('X: --, Y: --');
  let inspTile = $state('--');
  let inspCollision = $state('None');
  let wallCount = $state(0), holeCount = $state(0), boxCount = $state(0);
  let toggleVisual = $state(true), toggleWalls = $state(true), toggleHoles = $state(true), toggleBoxes = $state(true), toggleGrid = $state(true);
  let viewportRef;

  function storageKey(k){ return `pb_selections_${k}`; }
  function loadSelectionsFor(k){ try{ const v=window.localStorage.getItem(storageKey(k)); return v?JSON.parse(v):[];}catch{return[];} }
  function saveSelectionsFor(k, arr){ try{ window.localStorage.setItem(storageKey(k), JSON.stringify(arr)); }catch{} }

  async function loadCollisionData(){ try{ const r=await fetch('/pushbox_modules/maps_json/collision_data.json'); if(r.ok) collisionData=await r.json(); }catch{} }
  function getLevelIndex(key){ const m=(key||'').match(/\d+/); return m?m[0].replace(/^0+/,''):'1'; }
  function updateCounters(){
    if(currentMode==='sprites'){ wallCount=holeCount=boxCount='—'; return; }
    const key=currentMode==='maps'?currentMapKey:currentSpriteKey;
    const lvl=getLevelIndex(key);
    if(collisionData?.[lvl]){ wallCount=collisionData[lvl].walls.length; holeCount=collisionData[lvl].holes.length; boxCount=collisionData[lvl].boxes.length; } else { wallCount=holeCount=boxCount=0; }
  }
  async function selectMap(key){
    const isSprite = key.startsWith('mapa') ? false : true;
    // fallback: check via fetch manifest sprites list not needed — key prefix is enough for isolation
    if(key.startsWith('mapa')) currentMapKey=key; else currentSpriteKey=key;
    selections = loadSelectionsFor(key);
    try{ const mod=await import(`../../pushbox_modules/maps_json/${key}.json`); currentMapData=mod.default; }catch(e){ console.error(e); }
    updateCounters();
  }

  onMount(async()=>{
    await loadCollisionData();
    await selectMap('mapa01');
    // init sprite key for Sprites tab
    try{ const r=await fetch('/pushbox_modules/maps_json/_manifest.json'); if(r.ok){ const mf=await r.json(); if(mf.sprites?.[0] && !currentSpriteKey) currentSpriteKey=mf.sprites[0]; } }catch{}
  });

  function handleCoords(detail){
    const {x,y,tile,col}=detail;
    inspCoords=`X: ${x}, Y: ${y} (L:${Math.floor(x/2)},${Math.floor(y/2)})`;
    inspTile=`ID ${tile}`;
    inspCollision=col;
  }
</script>

<div class="app-container">
  <header class="navbar">
    <div class="brand"><div class="brand-icon">📦</div><div class="brand-title">PushBox <span class="badge">Map Viewer</span></div></div>
    <nav class="nav-tabs">
      <a href="/" class="tab-btn"><span class="tab-icon">🎮</span> Game</a>
      <button class="tab-btn active" data-tab="maps"><span class="tab-icon">🗺️</span> Maps</button>
      <button class="tab-btn disabled" data-tab="scenes" title="Coming Soon"><span class="tab-icon">🎬</span> Scenes <span class="tag-soon">Soon</span></button>
    </nav>
  </header>
  <main class="main-body">
    <aside class="sidebar">
      <div class="panel tabs-panel">
        <div class="tab-switch">
          <button class="tab-switch-btn" class:active={currentMode==='maps'} onclick={()=>{currentMode='maps'; selectMap(currentMapKey);}}>🗺️ Maps</button>
          <button class="tab-switch-btn" class:active={currentMode==='sprites'} onclick={()=>{currentMode='sprites'; selectMap(currentSpriteKey||'YouWinYouLose');}}>🎨 Sprites</button>
        </div>
      </div>
      {#if currentMode==='maps'}
        <MapsPanel currentKey={currentMapKey} onSelect={selectMap} />
      {:else}
        <SpritesPanel currentKey={currentSpriteKey} onSelect={selectMap} />
      {/if}
      <section class="panel">
        <h3 class="panel-header">Layer & Collision Toggles</h3>
        <div class="toggle-group">
          <label class="toggle-item"><input type="checkbox" bind:checked={toggleVisual}><span class="toggle-slider"></span><span class="toggle-label">👁️ Visual ASCII Tiles</span></label>
          <label class="toggle-item"><input type="checkbox" bind:checked={toggleWalls}><span class="toggle-slider wall"></span><span class="toggle-label">🧱 Walls Layer ({wallCount})</span></label>
          <label class="toggle-item"><input type="checkbox" bind:checked={toggleHoles}><span class="toggle-slider hole"></span><span class="toggle-label">🕳️ Pits / Holes ({holeCount})</span></label>
          <label class="toggle-item"><input type="checkbox" bind:checked={toggleBoxes}><span class="toggle-slider box"></span><span class="toggle-label">📦 Box Spawns ({boxCount})</span></label>
          <label class="toggle-item"><input type="checkbox" bind:checked={toggleGrid}><span class="toggle-slider grid"></span><span class="toggle-label">📐 Grid Lines</span></label>
        </div>
      </section>
      <Inspector coords={inspCoords} tile={inspTile} collision={inspCollision} />
      <Selections selections={selections} storageKey={currentMode==='maps'?currentMapKey:currentSpriteKey}
        onRemove={(idx)=>{ selections=selections.filter((_,i)=>i!==idx); saveSelectionsFor(currentMode==='maps'?currentMapKey:currentSpriteKey, selections); }}
        onClear={()=>{ selections=[]; saveSelectionsFor(currentMode==='maps'?currentMapKey:currentSpriteKey, selections); }}
        onCopy={async()=>{ const t=selections.map((s,i)=>`Selection ${i+1}: (${s.x1},${s.y1}) → (${s.x2},${s.y2}) ${s.x2-s.x1+1}×${s.y2-s.y1+1}  L:(${Math.floor(s.x1/2)},${Math.floor(s.y1/2)})→(${Math.floor(s.x2/2)},${Math.floor(s.y2/2)})`).join('\n')||'No selections'; try{ await window.navigator.clipboard.writeText(t);}catch{}}} />
    </aside>
    <section class="viewport">
      <div class="viewport-header">
        <h2>{(currentMode==='maps'?currentMapKey:currentSpriteKey)?.toUpperCase()} ({currentMapData?.rows||'?'} × {currentMapData?.cols||'?'})</h2>
        <div class="viewport-controls">
          <span class="zoom-level">{Math.round(zoomScale*100)}%</span>
          <button class="btn-icon" onclick={()=>isDrawMode=!isDrawMode} style:background={isDrawMode?'rgba(56,189,248,0.25)':''} title="Toggle Draw Mode">✏️</button>
          <button class="btn-icon" onclick={()=>{ if(zoomScale>0.5) zoomScale-=0.25; }}>➖</button>
          <button class="btn-icon" onclick={()=>zoomScale=1.0}>🔄</button>
          <button class="btn-icon" onclick={()=>{ if(zoomScale<2.5) zoomScale+=0.25; }}>➕</button>
        </div>
      </div>
      <div class="canvas-container">
        <Viewport
          bind:this={viewportRef}
          matrix={currentMapData?.matrix}
          rows={currentMapData?.rows||63}
          cols={currentMapData?.cols||80}
          zoomScale={zoomScale}
          selections={selections}
          isDrawMode={isDrawMode}
          toggleVisual={toggleVisual}
          toggleWalls={toggleWalls}
          toggleHoles={toggleHoles}
          toggleBoxes={toggleBoxes}
          toggleGrid={toggleGrid}
          collisionData={collisionData}
          currentMode={currentMode}
          getLevelIndex={()=>getLevelIndex(currentMode==='maps'?currentMapKey:currentSpriteKey)}
          onCoords={handleCoords}
          onSelection={(detail)=>{ selections=[...selections, detail]; saveSelectionsFor(currentMode==='maps'?currentMapKey:currentSpriteKey, selections); }}
        />
      </div>
    </section>
  </main>
</div>
