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

let currentMapKey = 'mapa01';
let currentMapData = null;
let collisionData = null;
let zoomScale = 1.0;

const TILE_SIZE = 14;

const canvas = document.getElementById('mapCanvas');
const ctx = canvas.getContext('2d');
const mapListEl = document.getElementById('mapList');
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

async function initApp() {
  renderMapList();
  setupEventListeners();

  await loadCollisionData();
  await selectMap('mapa01');
}

function renderMapList() {
  mapListEl.innerHTML = '';
  MAP_KEYS.forEach(key => {
    const btn = document.createElement('button');
    btn.className = `map-btn ${key === currentMapKey ? 'active' : ''}`;
    btn.dataset.key = key;
    btn.innerHTML = `<span>MAPA ${key.replace('mapa', '')}</span> <span class="dim">60×80</span>`;
    btn.addEventListener('click', () => selectMap(key));
    mapListEl.appendChild(btn);
  });
}

async function loadCollisionData() {
  try {
    const res = await fetch('/src/dsl/maps_json/collision_data.json');
    if (res.ok) {
      collisionData = await res.json();
    }
  } catch (err) {
    console.warn('Could not fetch collision_data.json:', err);
  }
}

async function selectMap(key) {
  currentMapKey = key;
  document.querySelectorAll('.map-btn').forEach(btn => {
    btn.classList.toggle('active', btn.dataset.key === key);
  });

  currentMapTitleEl.textContent = `${key.toUpperCase()} (60 × 80)`;

  try {
    const mod = await import(`../dsl/maps_json/${key}.json`);
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

  const rows = currentMapData.rows || 60;
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

  if (toggleWallsEl.checked && lvlCollision && lvlCollision.walls) {
    ctx.fillStyle = 'rgba(239, 68, 68, 0.55)';
    ctx.strokeStyle = '#ef4444';
    ctx.lineWidth = 1;
    lvlCollision.walls.forEach(([wx, wy]) => {
      ctx.fillRect(wx * effectiveTileSize, wy * effectiveTileSize, effectiveTileSize, effectiveTileSize);
      ctx.strokeRect(wx * effectiveTileSize, wy * effectiveTileSize, effectiveTileSize, effectiveTileSize);
    });
  }

  if (toggleHolesEl.checked && lvlCollision && lvlCollision.holes) {
    ctx.fillStyle = 'rgba(192, 132, 252, 0.6)';
    ctx.strokeStyle = '#c084fc';
    ctx.lineWidth = 1;
    lvlCollision.holes.forEach(([hx, hy]) => {
      ctx.fillRect(hx * effectiveTileSize, hy * effectiveTileSize, effectiveTileSize, effectiveTileSize);
      ctx.strokeRect(hx * effectiveTileSize, hy * effectiveTileSize, effectiveTileSize, effectiveTileSize);
    });
  }

  if (toggleBoxesEl.checked && lvlCollision && lvlCollision.boxes) {
    ctx.fillStyle = 'rgba(250, 204, 21, 0.7)';
    ctx.strokeStyle = '#facc15';
    ctx.lineWidth = 1.5;
    lvlCollision.boxes.forEach(([bx, by]) => {
      ctx.fillRect(bx * effectiveTileSize + 2, by * effectiveTileSize + 2, effectiveTileSize - 4, effectiveTileSize - 4);
      ctx.strokeRect(bx * effectiveTileSize + 1, by * effectiveTileSize + 1, effectiveTileSize - 2, effectiveTileSize - 2);
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
}

function setupEventListeners() {
  [toggleVisualEl, toggleWallsEl, toggleHolesEl, toggleBoxesEl, toggleGridEl].forEach(t => {
    t.addEventListener('change', drawCanvas);
  });

  canvas.addEventListener('mousemove', (e) => {
    const rect = canvas.getBoundingClientRect();
    const effectiveTileSize = TILE_SIZE * zoomScale;
    const x = Math.floor((e.clientX - rect.left) / effectiveTileSize);
    const y = Math.floor((e.clientY - rect.top) / effectiveTileSize);

    if (x >= 0 && x < 80 && y >= 0 && y < 60) {
      inspCoordsEl.textContent = `X: ${x}, Y: ${y}`;
      if (currentMapData && currentMapData.matrix && currentMapData.matrix[y]) {
        const val = currentMapData.matrix[y][x];
        inspTileEl.textContent = `ID ${val}`;
      }

      const lvl = getLevelIndex();
      let colType = 'None (Empty)';
      if (collisionData && collisionData[lvl]) {
        if (collisionData[lvl].walls.some(([wx, wy]) => wx === x && wy === y)) {
          colType = '🧱 Wall (Pared)';
        } else if (collisionData[lvl].holes.some(([hx, hy]) => hx === x && hy === y)) {
          colType = '🕳️ Hole / Pit (Hueco)';
        } else if (collisionData[lvl].boxes.some(([bx, by]) => bx === x && by === y)) {
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
