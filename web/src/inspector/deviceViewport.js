import './deviceViewport.css';

export const INSPECTOR_DEVICES = [[360, 800], [393, 852], [430, 932]];

export function deviceViewportMarkup(content = '') {
  return `<div class="phone-scale device-frame"><div class="phone-screen">
    <div class="status-bar"><span>9:41</span><span>▂▄▆ ▰</span></div>
    <div class="browser-top"><span>⌂</span><span class="address">▣ pushbox.local</span><span>⋮</span></div>
    <div class="web-viewport">${content}</div>
    <div class="browser-bottom"><span>◁</span><span>○</span><span>▢</span></div>
  </div></div>`;
}

export function sizeDevicePreview(card, [width, height], { scale = 0.85, top = 56, bottom = 48 } = {}) {
  for (const [name, value] of Object.entries({ 'device-width': `${width}px`, 'device-height': `${height}px`,
    'top-height': `${top}px`, 'bottom-height': `${bottom}px`, 'preview-scale': scale })) card.style.setProperty(`--${name}`, value);
  card.style.width = `${width * scale}px`;
  card.querySelector('.phone-scale').style.height = `${height * scale}px`;
  const label = card.querySelector('.viewport-size');
  if (label) label.textContent = `Web viewport: ${width} × ${height - 24 - top - bottom}`;
}
