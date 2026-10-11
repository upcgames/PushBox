// The sole boundary between standard Tiled assets and PushBox rules.
export function levelFromTiled(map) {
  const settings = Object.fromEntries(map.properties.map(({ name, value }) => [name, value]));
  const objects = map.layers.find(layer => layer.name === 'Gameplay').objects;
  const points = role => objects.filter(object => object.type === role).map(object => ({
    x: object.x / map.tilewidth, y: object.y / map.tileheight,
  }));
  if (settings.level !== 1 || points('player').length !== 1 || points('portal').length !== 1) {
    throw new Error('The POC requires a level-one map with one player and portal');
  }
  return { ...settings, width: map.width, height: map.height,
    player: points('player')[0], portal: points('portal')[0],
    walls: points('wall'), boxes: points('box'), targets: points('target') };
}
