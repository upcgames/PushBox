import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

// Exercise the actual drawing routine with recorded canvas/sprite calls. JSON
// imports and the browser sprite canvas are supplied separately for Node.
function fixture() {
  const read = path => readFileSync(new URL(path, import.meta.url), 'utf8');
  const players = [], rectangles = [];
  const context = { globalAlpha: 1, fillText() {}, fillRect(x, y, width, height) {
    rectangles.push({ x, y, width, height, color: this.fillStyle });
  } };
  const sandbox = vm.createContext({
    map5: JSON.parse(read('../pushbox_modules/maps_json/mapa05.json')),
    collisions: JSON.parse(read('../pushbox_modules/maps_json/collision_data.json')),
    palette: Array.from({ length: 17 }, (_, index) => `color-${index}`),
    player: (_ctx, x, y) => players.push({ x, y }),
    rect: (ctx, color, x, y, width, height) => { ctx.fillStyle = color; ctx.fillRect(x, y, width, height); },
  });
  const source = read('../src/presentation/loreIllustrations.js')
    .replace(/^import .*;\n/gm, '').replace(/export function /g, 'function ');
  vm.runInContext(source, sandbox);
  return { paint(time) {
    players.length = 0; rectangles.length = 0;
    sandbox.lore(context, time, 5);
    return { players: [...players], rectangles: [...rectangles] };
  } };
}

test('level-five first frame tolerates a negative elapsed time without stopping after the map', () => {
  const scene = fixture(), opening = scene.paint(0);
  for (const time of [-0.1, -1, -300]) assert.deepEqual(scene.paint(time), opening);
  assert.equal(opening.players.length, 1);
  const bobby = opening.players[0];
  assert.ok(bobby.x >= 0 && bobby.x + 28 <= 280 && bobby.y >= 0 && bobby.y + 28 <= 224);
});

test('level-five subsequent frames move Bobby and show the exclamation cue', () => {
  const scene = fixture(), initial = scene.paint(0), later = scene.paint(600);
  assert.notDeepEqual(later.players, initial.players);
  assert.ok(later.rectangles.some(rect => rect.color === '#eab308' && rect.width === 4 && rect.height === 11));
  assert.equal(scene.paint(1800).players.length, 1);
});
