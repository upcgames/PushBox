const DOS_COLORS = {
  0: '#0f172a',
  1: '#ffffff',
  2: '#ef4444',
  3: '#22c55e',
  4: '#3b82f6',
  5: '#06b6d4',
  6: '#d946ef',
  7: '#eab308',
  8: '#94a3b8',
  9: '#1e293b',
  10: '#991b1b',
  11: '#166534',
  12: '#1e3a8a',
  13: '#155e75',
  14: '#701a75',
  15: '#854d0e',
  16: '#334155'
};

const MAP_KEYS = ['mapa01', 'mapa02', 'mapa03', 'mapa04', 'mapa05'];
let SPRITE_KEYS = [];

let currentMapKey = 'mapa01';
let currentMode = 'maps'; // maps | sprites
let currentMapData = null;
let collisionData = null;
let zoomScale = 1.0;

const TILE_SIZE = 14;

const canvas = document.getElementById('mapCanvas');
const ctx = canvas.getContext('2d');
const mapListEl = document.getElementById('mapList');
const spriteListEl = document.getElementById('spriteList');
const currentMapTitleEl = document.getElementById('currentMapTitle');

const toggleVisualEl = document.getElementById('toggleVisual');
const toggleWallsEl = document.getElementById('toggleWalls');
const toggleHolesEl = document.getElementById('toggleHoles');
const toggleBoxesEl = document.getElementById('toggleBoxes');
const toggleGridEl = document.getElementById('toggleGrid');

const wallCountEl = document.getElementById('wallCount');
const holeCountEl = document.getElementById('holeCount');
const boxCountEl = document.getElementById('boxCount');

const inspCoordsEl = document.getElementById('inspCoords');
const inspTileEl = document.getElementById('inspTile');
const inspCollisionEl = document.getElementById('inspCollision');

const zoomTextEl = document.getElementById('zoomText');
const selectionListEl = document.getElementById('selectionList');
const selectionCountEl = document.getElementById('selectionCount');
let isDrawMode = false;
let selections = [];
let dragStart = null;
let dragCurrent = null;

function storageKey(k) { return `pb_selections_${k}`; }
function loadSelectionsFor(k) { try { const v = window.localStorage.getItem(storageKey(k)); return v ? JSON.parse(v) : []; } catch { return []; } }
function saveSelectionsFor(k) { try { window.localStorage.setItem(storageKey(k), JSON.stringify(selections)); } catch {} }

let currentSpriteKey = null;

async function initApp() {
  renderMapList();
  await loadSpriteList();
  renderSpriteList();
  setupEventListeners();
  setupTabs();

  await loadCollisionData();
  await selectMap('mapa01');
  // keep sprite selection separate — don't auto-show map in sprites tab
  if (SPRITE_KEYS.length) currentSpriteKey = SPRITE_KEYS[0];
}

function renderMapList() {
  mapListEl.innerHTML = '';
  MAP_KEYS.forEach(key => {
    const btn = document.createElement('button');
    btn.className = `map-btn ${key === currentMapKey ? 'active' : ''}`;
    btn.dataset.key = key;
    btn.innerHTML = `<span>MAPA ${key.replace('mapa', '')}</span> <span class="dim">63×80</span>`;
    btn.addEventListener('click', () => selectMap(key));
    mapListEl.appendChild(btn);
  });
}

async function loadSpriteList() {
  try {
    const res = await fetch('/pushbox_modules/maps_json/_manifest.json');
    if (res.ok) {
      const mf = await res.json();
      SPRITE_KEYS = mf.sprites || [];
    }
  } catch {}
  if (!SPRITE_KEYS.length) SPRITE_KEYS = ['YouWinYouLose','ni1','dh1'];
}

function renderSpriteList() {
  if (!spriteListEl) return;
  spriteListEl.innerHTML = '';
  SPRITE_KEYS.forEach(key => {
    const btn = document.createElement('button');
    btn.className = `map-btn ${key === currentMapKey ? 'active' : ''}`;
    btn.dataset.key = key;
    btn.innerHTML = `<span>${key}</span> <span class="dim">sprite</span>`;
    btn.addEventListener('click', () => selectMap(key));
    spriteListEl.appendChild(btn);
  });
}

function setupTabs() {
  document.querySelectorAll('.tab-switch-btn').forEach(b=>{
    b.addEventListener('click', async ()=>{
      currentMode = b.dataset.tab;
      document.querySelectorAll('.tab-switch-btn').forEach(x=>x.classList.toggle('active', x===b));
      document.getElementById('mapsPanel')?.classList.toggle('hidden', currentMode!=='maps');
      document.getElementById('spritesPanel')?.classList.toggle('hidden', currentMode!=='sprites');
      // refresh active state per mode and load correct matrix — no cross-pollution
      if (currentMode === 'maps' && currentMapKey) await selectMap(currentMapKey);
      else if (currentMode === 'sprites' && currentSpriteKey) await selectMap(currentSpriteKey);
      else if (currentMode === 'sprites') await selectMap(SPRITE_KEYS[0]);
    });
  });
}

async function loadCollisionData() {
  try {
    const res = await fetch('/pushbox_modules/maps_json/collision_data.json');
    if (res.ok) {
      collisionData = await res.json();
    }
  } catch (err) {
    console.warn('Could not fetch collision_data.json:', err);
  }
}

async function selectMap(key) {
  if (SPRITE_KEYS.includes(key)) currentSpriteKey = key; else currentMapKey = key;
  // load selections coupled to this sprite/map
  selections = loadSelectionsFor(key);
  renderSelections();
  document.querySelectorAll('.map-btn').forEach(btn => {
    const isActive = (SPRITE_KEYS.includes(key) ? btn.dataset.key === currentSpriteKey : btn.dataset.key === currentMapKey) && btn.closest(currentMode==='sprites' ? '#spritesPanel' : '#mapsPanel');
    // simpler: toggle based on key equality, but scoped to visible panel
    btn.classList.toggle('active', btn.dataset.key === key);
  });

  const isSprite = SPRITE_KEYS.includes(key);
  if (currentMapData) currentMapTitleEl.textContent = `${key.toUpperCase()} (${currentMapData.rows||'?'} × ${currentMapData.cols||'?'})`;
  else currentMapTitleEl.textContent = `${key.toUpperCase()} ${isSprite?'(sprite)':'(63 × 80)'}`;

  try {
    const mod = await import(`../../pushbox_modules/maps_json/${key}.json`);
    currentMapData = mod.default;
  } catch (err) {
    console.error(`Failed to load ${key}.json:`, err);
  }

  updateCounters();
  drawCanvas();
}

function getLevelIndex() {
  const match = currentMapKey.match(/\d+/);
  return match ? match[0].replace(/^0+/, '') : '1';
}

function updateCounters() {
  if (currentMode === 'sprites') {
    wallCountEl.textContent = '—';
    holeCountEl.textContent = '—';
    boxCountEl.textContent = '—';
    return;
  }
  const lvl = getLevelIndex();
  if (collisionData && collisionData[lvl]) {
    wallCountEl.textContent = collisionData[lvl].walls.length;
    holeCountEl.textContent = collisionData[lvl].holes.length;
    boxCountEl.textContent = collisionData[lvl].boxes.length;
  } else {
    wallCountEl.textContent = '0';
    holeCountEl.textContent = '0';
    boxCountEl.textContent = '0';
  }
}

function drawCanvas() {
  if (!currentMapData || !currentMapData.matrix) return;

  const rows = currentMapData.rows || 63;
  const cols = currentMapData.cols || 80;

  const effectiveTileSize = TILE_SIZE * zoomScale;
  canvas.width = cols * effectiveTileSize;
  canvas.height = rows * effectiveTileSize;

  ctx.clearRect(0, 0, canvas.width, canvas.height);

  const matrix = currentMapData.matrix;
  const lvl = getLevelIndex();
  const lvlCollision = collisionData ? collisionData[lvl] : null;

  if (toggleVisualEl.checked) {
    for (let r = 0; r < rows; r++) {
      for (let c = 0; c < cols; c++) {
        const tileVal = matrix[r][c];
        const color = DOS_COLORS[tileVal] || DOS_COLORS[0];
        ctx.fillStyle = color;
        ctx.fillRect(c * effectiveTileSize, r * effectiveTileSize, effectiveTileSize, effectiveTileSize);
      }
    }
  } else {
    ctx.fillStyle = '#0f172a';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
  }

  const LOGICAL = effectiveTileSize * 2;
  const showCollision = currentMode === 'maps';
  if (showCollision && toggleWallsEl.checked && lvlCollision && lvlCollision.walls) {
    ctx.fillStyle = 'rgba(239, 68, 68, 0.55)';
    ctx.strokeStyle = '#ef4444';
    ctx.lineWidth = 1;
    lvlCollision.walls.forEach(([wx, wy]) => {
      ctx.fillRect(wx * effectiveTileSize, wy * effectiveTileSize, LOGICAL, LOGICAL);
      ctx.strokeRect(wx * effectiveTileSize, wy * effectiveTileSize, LOGICAL, LOGICAL);
    });
  }

  if (showCollision && toggleHolesEl.checked && lvlCollision && lvlCollision.holes) {
    ctx.fillStyle = 'rgba(192, 132, 252, 0.6)';
    ctx.strokeStyle = '#c084fc';
    ctx.lineWidth = 1;
    lvlCollision.holes.forEach(([hx, hy]) => {
      ctx.fillRect(hx * effectiveTileSize, hy * effectiveTileSize, LOGICAL, LOGICAL);
      ctx.strokeRect(hx * effectiveTileSize, hy * effectiveTileSize, LOGICAL, LOGICAL);
    });
  }

  if (showCollision && toggleBoxesEl.checked && lvlCollision && lvlCollision.boxes) {
    ctx.fillStyle = 'rgba(250, 204, 21, 0.7)';
    ctx.strokeStyle = '#facc15';
    ctx.lineWidth = 1.5;
    lvlCollision.boxes.forEach(([bx, by]) => {
      ctx.fillRect(bx * effectiveTileSize + 2, by * effectiveTileSize + 2, LOGICAL - 4, LOGICAL - 4);
      ctx.strokeRect(bx * effectiveTileSize + 1, by * effectiveTileSize + 1, LOGICAL - 2, LOGICAL - 2);
    });
  }

  if (toggleGridEl.checked) {
    ctx.strokeStyle = 'rgba(255, 255, 255, 0.05)';
    ctx.lineWidth = 1;
    for (let c = 0; c <= cols; c++) {
      ctx.beginPath();
      ctx.moveTo(c * effectiveTileSize, 0);
      ctx.lineTo(c * effectiveTileSize, canvas.height);
      ctx.stroke();
    }
    for (let r = 0; r <= rows; r++) {
      ctx.beginPath();
      ctx.moveTo(0, r * effectiveTileSize);
      ctx.lineTo(canvas.width, r * effectiveTileSize);
      ctx.stroke();
    }
  }

  // selections overlay
  ctx.lineWidth = 2;
  selections.forEach((s, idx) => {
    ctx.strokeStyle = idx % 2 === 0 ? '#38bdf8' : '#c084fc';
    ctx.fillStyle = idx % 2 === 0 ? 'rgba(56,189,248,0.15)' : 'rgba(192,132,252,0.15)';
    ctx.fillRect(s.x1*effectiveTileSize, s.y1*effectiveTileSize, (s.x2-s.x1+1)*effectiveTileSize, (s.y2-s.y1+1)*effectiveTileSize);
    ctx.strokeRect(s.x1*effectiveTileSize+0.5, s.y1*effectiveTileSize+0.5, (s.x2-s.x1+1)*effectiveTileSize-1, (s.y2-s.y1+1)*effectiveTileSize-1);
    ctx.fillStyle = ctx.strokeStyle;
    ctx.font = `${Math.max(10, effectiveTileSize*0.6)}px monospace`;
    ctx.fillText(String(idx+1), s.x1*effectiveTileSize+4, s.y1*effectiveTileSize+14);
  });
  if (dragStart && dragCurrent) {
    const x1=Math.min(dragStart.x,dragCurrent.x), y1=Math.min(dragStart.y,dragCurrent.y), x2=Math.max(dragStart.x,dragCurrent.x), y2=Math.max(dragStart.y,dragCurrent.y);
    ctx.strokeStyle = '#facc15';
    ctx.setLineDash([6,4]);
    ctx.strokeRect(x1*effectiveTileSize+0.5, y1*effectiveTileSize+0.5, (x2-x1+1)*effectiveTileSize-1, (y2-y1+1)*effectiveTileSize-1);
    ctx.setLineDash([]);
    ctx.fillStyle = 'rgba(250,204,21,0.12)';
    ctx.fillRect(x1*effectiveTileSize, y1*effectiveTileSize, (x2-x1+1)*effectiveTileSize, (y2-y1+1)*effectiveTileSize);
  }
}

function getCanvasCoords(e) {
  const rect = canvas.getBoundingClientRect();
  const effectiveTileSize = TILE_SIZE * zoomScale;
  const x = Math.floor((e.clientX - rect.left) / effectiveTileSize);
  const y = Math.floor((e.clientY - rect.top) / effectiveTileSize);
  return { x, y, effectiveTileSize };
}

function renderSelections() {
  if (!selectionListEl) return;
  selectionListEl.innerHTML = '';
  selections.forEach((s, idx) => {
    const div = document.createElement('div');
    div.style.cssText = 'display:flex;align-items:center;justify-content:space-between;background:rgba(255,255,255,0.04);border:1px solid var(--bg-panel-border);border-radius:8px;padding:8px 10px;font-family:var(--font-code);font-size:0.78rem';
    const w = s.x2 - s.x1 + 1, h = s.y2 - s.y1 + 1;
    div.innerHTML = `<span><b style="color:var(--accent-cyan)">#${idx+1}</b> (${s.x1},${s.y1}) → (${s.x2},${s.y2}) <span style="color:var(--text-muted)">${w}×${h}</span></span><button data-idx="${idx}" class="btn-icon" style="width:24px;height:24px;font-size:0.8rem">✕</button>`;
    div.querySelector('button').addEventListener('click', () => { selections.splice(idx,1); saveSelectionsFor(currentMapKey); renderSelections(); drawCanvas(); });
    selectionListEl.appendChild(div);
  });
  if (selectionCountEl) selectionCountEl.textContent = String(selections.length);
}

function setupEventListeners() {
  [toggleVisualEl, toggleWallsEl, toggleHolesEl, toggleBoxesEl, toggleGridEl].forEach(t => {
    t.addEventListener('change', drawCanvas);
  });
  const btnDrawModeEl = document.getElementById('btnDrawMode');
  if (btnDrawModeEl) {
    btnDrawModeEl.addEventListener('click', () => {
      isDrawMode = !isDrawMode;
      btnDrawModeEl.style.background = isDrawMode ? 'rgba(56,189,248,0.25)' : '';
      btnDrawModeEl.style.borderColor = isDrawMode ? 'var(--accent-cyan)' : '';
      canvas.style.cursor = isDrawMode ? 'crosshair' : 'crosshair';
      canvas.style.outline = isDrawMode ? '2px dashed var(--accent-cyan)' : '';
      canvas.style.outlineOffset = isDrawMode ? '-2px' : '';
    });
  }
  document.getElementById('btnClearSelections')?.addEventListener('click', () => { selections=[]; saveSelectionsFor(currentMapKey); renderSelections(); drawCanvas(); });
  document.getElementById('btnCopySelections')?.addEventListener('click', async () => {
    const text = selections.map((s,i)=>`Selection ${i+1}: (${s.x1},${s.y1}) → (${s.x2},${s.y2}) ${s.x2-s.x1+1}×${s.y2-s.y1+1}  L:(${Math.floor(s.x1/2)},${Math.floor(s.y1/2)})→(${Math.floor(s.x2/2)},${Math.floor(s.y2/2)})`).join('\n') || 'No selections';
    try { await window.navigator.clipboard.writeText(text); const b=document.getElementById('btnCopySelections'); const t=b.textContent; b.textContent='Copied!'; setTimeout(()=>b.textContent=t,1200);} catch {}
  });

  canvas.addEventListener('mousedown', (e) => {
    if (!isDrawMode) return;
    const { x, y } = getCanvasCoords(e);
    if (x<0||x>=80||y<0||y>=63) return;
    dragStart = { x, y };
    dragCurrent = { x, y };
    e.preventDefault();
  });
  canvas.addEventListener('mouseup', (e) => {
    if (!dragStart || !dragCurrent) return;
    const x1 = Math.min(dragStart.x, dragCurrent.x), y1 = Math.min(dragStart.y, dragCurrent.y);
    const x2 = Math.max(dragStart.x, dragCurrent.x), y2 = Math.max(dragStart.y, dragCurrent.y);
    selections.push({ x1, y1, x2, y2 }); saveSelectionsFor(currentMapKey);
    dragStart = null; dragCurrent = null;
    renderSelections(); drawCanvas();
  });
  canvas.addEventListener('mouseleave', () => { if (dragStart) { dragStart=null; dragCurrent=null; drawCanvas(); }});

  canvas.addEventListener('mousemove', (e) => {
    if (dragStart) {
      const { x, y } = getCanvasCoords(e);
      dragCurrent = { x: Math.max(0,Math.min(79,x)), y: Math.max(0,Math.min(62,y)) };
      drawCanvas();
      return;
    }
    if (isDrawMode) return;
    const rect = canvas.getBoundingClientRect();
    const effectiveTileSize = TILE_SIZE * zoomScale;
    const x = Math.floor((e.clientX - rect.left) / effectiveTileSize);
    const y = Math.floor((e.clientY - rect.top) / effectiveTileSize);

    if (x >= 0 && x < 80 && y >= 0 && y < 63) {
      const lx = Math.floor(x / 2);
      const ly = Math.floor(y / 2);
      inspCoordsEl.textContent = `X: ${x}, Y: ${y} (L:${lx},${ly})`;
      if (currentMapData && currentMapData.matrix && currentMapData.matrix[y]) {
        const val = currentMapData.matrix[y][x];
        inspTileEl.textContent = `ID ${val}`;
      }

      const lvl = getLevelIndex();
      let colType = currentMode === 'sprites' ? '— (Sprite)' : 'None (Empty)';
      if (currentMode === 'maps' && collisionData && collisionData[lvl]) {
        const hit = (arr) => arr.some(([px, py]) => x >= px && x < px + 2 && y >= py && y < py + 2);
        if (hit(collisionData[lvl].walls)) {
          colType = '🧱 Wall (Pared)';
        } else if (hit(collisionData[lvl].holes)) {
          colType = '🕳️ Hole / Pit (Hueco)';
        } else if (hit(collisionData[lvl].boxes)) {
          colType = '📦 Box Spawn (Caja)';
        }
      }
      inspCollisionEl.textContent = colType;
    }
  });

  document.getElementById('btnZoomIn').addEventListener('click', () => {
    if (zoomScale < 2.5) { zoomScale += 0.25; updateZoomText(); drawCanvas(); }
  });

  document.getElementById('btnZoomOut').addEventListener('click', () => {
    if (zoomScale > 0.5) { zoomScale -= 0.25; updateZoomText(); drawCanvas(); }
  });

  document.getElementById('btnZoomReset').addEventListener('click', () => {
    zoomScale = 1.0; updateZoomText(); drawCanvas();
  });
}

function updateZoomText() {
  zoomTextEl.textContent = `${Math.round(zoomScale * 100)}%`;
}

document.addEventListener('DOMContentLoaded', initApp);
