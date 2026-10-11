// Convert pipeline data into a standard Tiled map + PNG tileset, without dependencies.
import { readFile, mkdir, writeFile } from 'node:fs/promises';
import { deflateSync } from 'node:zlib';

const root = new URL('../', import.meta.url);
const read = async path => JSON.parse(await readFile(new URL(path, root), 'utf8'));
const art = await read('pushbox_modules/maps_json/mapa01.json');
const collision = (await read('pushbox_modules/maps_json/collision_data.json'))['1'];
if (['walls', 'boxes', 'holes', 'voids'].map(key => collision[key].length).join() !== '52,4,4,0') {
  throw new Error('Extracted level 1 shape changed; review POC conversion');
}
const cell = 16;
// Extrude each solid-color tile into a two-pixel border so fractional camera
// zoom cannot sample the neighboring palette color along a tile edge.
const padding = 2, pitch = cell + padding * 2;
const objects = [];
const groups = { wall: collision.walls, box: collision.boxes, target: collision.holes,
  player: [[36, 34]], portal: [[36, 34]] };
for (const [role, points] of Object.entries(groups)) {
  for (const [x, y] of points) objects.push({ id: objects.length + 1, name: role, type: role,
    x: x * cell, y: y * cell, width: cell * 2, height: cell * 2, rotation: 0, visible: true });
}
const map = {
  type: 'map', version: '1.10', tiledversion: '1.11.0', orientation: 'orthogonal',
  renderorder: 'right-down', infinite: false, width: art.cols, height: art.rows,
  tilewidth: cell, tileheight: cell, nextlayerid: 3, nextobjectid: objects.length + 1,
  properties: Object.entries({ level: 1, stepSize: 2, moveLimit: 150, initialLives: 5,
    undoLimit: 5, undoCost: 3 }).map(([name, value]) => ({ name, type: 'int', value })),
  layers: [
    { id: 1, name: 'Artwork', type: 'tilelayer', width: art.cols, height: art.rows,
      x: 0, y: 0, opacity: 1, visible: true, data: art.matrix.flat() },
    { id: 2, name: 'Gameplay', type: 'objectgroup', x: 0, y: 0, opacity: 1,
      visible: true, draworder: 'topdown', objects },
  ],
  tilesets: [{ firstgid: 1, name: 'DOS Colors', tilewidth: cell, tileheight: cell,
    tilecount: 16, columns: 16, spacing: padding * 2, margin: padding, image: 'colors.png',
    imagewidth: pitch * 16, imageheight: pitch }],
};
const colors = ['ffffff', 'ef4444', '22c55e', '3b82f6', '06b6d4', 'd946ef',
  'eab308', '94a3b8', '000000', '991b1b', '166534', '1e3a8a', '155e75',
  '701a75', '854d0e', '334155'];
function chunk(type, data) {
  const body = Buffer.concat([Buffer.from(type), data]);
  let crc = 0xffffffff;
  for (const byte of body) {
    crc ^= byte;
    for (let bit = 0; bit < 8; bit++) crc = (crc >>> 1) ^ (crc & 1 ? 0xedb88320 : 0);
  }
  const size = Buffer.alloc(4), checksum = Buffer.alloc(4);
  size.writeUInt32BE(data.length); checksum.writeUInt32BE((crc ^ 0xffffffff) >>> 0);
  return Buffer.concat([size, body, checksum]);
}
const header = Buffer.alloc(13);
header.writeUInt32BE(pitch * 16, 0); header.writeUInt32BE(pitch, 4);
header[8] = 8; header[9] = 2;
const row = Buffer.concat([Buffer.from([0]), ...colors.map(color =>
  Buffer.concat(Array.from({ length: pitch }, () => Buffer.from(color, 'hex'))))]);
const png = Buffer.concat([Buffer.from('89504e470d0a1a0a', 'hex'), chunk('IHDR', header),
  chunk('IDAT', deflateSync(Buffer.concat(Array.from({ length: pitch }, () => row)))), chunk('IEND', Buffer.alloc(0))]);
const destination = new URL('public/level1-poc/', root);
await mkdir(destination, { recursive: true });
await writeFile(new URL('level1.tmj', destination), JSON.stringify(map) + '\n');
await writeFile(new URL('colors.png', destination), png);
console.log('Exported level 1 POC: Tiled map + PNG tileset');
