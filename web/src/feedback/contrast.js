// Sample the original board, never the hint overlay. Read only after board updates.
export function sampleLavaContrast(baseCanvas, scene) {
  for (const cue of scene.cues) {
    if (cue.kind !== 'danger') continue;
    cue.contrast = sampleTileContrast(baseCanvas, scene.grid, cue);
  }
}

export function sampleTileContrast(baseCanvas, { cellSize, objectSize }, tile) {
  const center = cellSize * objectSize / 2;
  try {
    const { data } = baseCanvas.getContext('2d').getImageData(tile.x * cellSize + center - 1,
      tile.y * cellSize + center - 1, 3, 3);
    let brightness = 0, count = 0;
    for (let pixel = 0; pixel < data.length; pixel += 4) {
      if (!data[pixel + 3]) continue;
      brightness += data[pixel] * 0.2126 + data[pixel + 1] * 0.7152 + data[pixel + 2] * 0.0722;
      count++;
    }
    return count && brightness / count >= 145 ? 'dark' : 'light';
  } catch {
    return 'light';
  }
}
