import { continueButton } from './buttons.js';
import { WARNING_COPY } from './warningCopy.js';
import { deviceViewportMarkup, sizeDevicePreview, INSPECTOR_DEVICES } from '../inspector/deviceViewport.js';
import { drawTitle } from './titleArt.js';
import { parsePlayerNames } from './nameInput.js';

const MESSAGE = WARNING_COPY;

export function mountOpeningSimulation(root, palette) {
  root.innerHTML = `${deviceViewportMarkup(`<div class="opening-screen opening-simulation">
    <div class="simulation-loading">
      <canvas class="simulation-title" width="256" height="112" aria-label="PushBox"></canvas><h3>Loading</h3>
      <canvas class="simulation-link" width="56" height="76" aria-label="Link loading animation"></canvas>
      <div class="load-meter" role="progressbar" aria-label="Loading preview" aria-valuemin="0" aria-valuemax="100" aria-valuenow="100"><span></span></div>
      <p class="simulation-percent">100%</p>
    </div>
    <div class="simulation-warning" hidden>
      <canvas class="simulation-warning-title" width="128" height="20" aria-label="Warning"></canvas>
      <canvas class="simulation-alien" width="84" height="64" aria-label="Original space invader"></canvas>
      <div class="simulation-content"><p class="simulation-copy"></p>
        <form class="simulation-name" hidden><h3>¿Cómo te llamas?</h3><div class="name-fields"><input type="text" autocomplete="name" autocapitalize="words" spellcheck="false" enterkeyhint="done" aria-label="¿Cómo te llamas?"></div></form>
      </div>
    </div>
    ${continueButton({ className: 'simulation-continue', label: 'Enter', disabled: true, hidden: true })}
  </div>`)}<div class="viewport-size"></div><div class="simulation-toolbar"><button class="sample-action simulation-replay">Replay</button><span class="simulation-status" aria-live="polite">Loading preview</span></div>`;
  sizeDevicePreview(root, INSPECTOR_DEVICES[1]);
  drawTitle(root.querySelector('.simulation-title'), 0);
  const audio = new Audio(`${import.meta.env.BASE_URL}audio/TypeWriter1.wav`);
  audio.preload = 'auto'; audio.loop = true; audio.load();
  const button = root.querySelector('.simulation-continue'), copy = root.querySelector('.simulation-copy');
  const input = root.querySelector('input'), status = root.querySelector('.simulation-status');
  const motion = window.matchMedia('(prefers-reduced-motion: reduce)');
  let stage = 'loading', position = 0, timer = null, frame = null, link, ready = false, disposed = false;
  // Lay out complete words first, then reveal characters without changing wrapping.
  const characters = [];
  let textOffset = 0;
  for (const part of MESSAGE.split(/(\s+)/u)) {
    if (/^\s+$/.test(part)) copy.append(document.createTextNode(part));
    else {
      const word = document.createElement('span'); word.className = 'simulation-word';
      for (const [index, character] of [...part].entries()) {
        const glyph = document.createElement('span'); glyph.textContent = character;
        glyph.style.visibility = 'hidden'; word.append(glyph);
        characters.push({ glyph, index: textOffset + index });
      }
      copy.append(word);
    }
    textOffset += part.length;
  }
  function revealText(count) {
    characters.forEach(({ glyph, index }) => { glyph.style.visibility = index < count ? 'visible' : 'hidden'; });
  }
  function stopTyping() { clearTimeout(timer); timer = null; audio.pause(); }
  function playTyping() { if (audio.paused) audio.play().catch(() => {}); }
  function type() {
    if (disposed || stage !== 'typing') return;
    if (root.closest('[role=tabpanel]').hidden || document.hidden) {
      audio.pause(); timer = setTimeout(type, 150); return;
    }
    playTyping(); position++; revealText(position);
    if (position === MESSAGE.length) { stage = 'warning'; stopTyping(); return; }
    // Pause only after the third dot in each ellipsis; silence makes the beat land.
    const beat = MESSAGE.slice(position - 3, position) === '...' || (MESSAGE[position - 1] === '.' && MESSAGE[position] !== '.');
    if (beat) audio.pause();
    timer = setTimeout(type, beat ? 1000 : 45);
  }
  function continueScene() {
    if (button.disabled) return;
    if (stage === 'loading') {
      root.querySelector('.simulation-loading').hidden = true;
      root.querySelector('.simulation-warning').hidden = false;
      button.textContent = 'Continue'; stage = 'typing'; position = 0;
      status.textContent = 'Warning · Continue reveals all text';
      playTyping(); type();
    } else if (stage === 'typing') {
      stopTyping(); revealText(MESSAGE.length); stage = 'warning';
    } else if (stage === 'warning') {
      stopTyping(); copy.hidden = true; root.querySelector('.simulation-name').hidden = false;
      stage = 'name'; status.textContent = 'Name entry';
      input.focus();
    } else if (stage === 'name') {
      const names = parsePlayerNames(input.value);
      if (!names.length) { input.focus(); return; }
      input.value = names.join(' '); input.blur(); button.disabled = true;
      stage = 'done'; status.textContent = `Opening complete · ${names.join(' ')} · preview stops before gameplay`;
    }
  }
  button.addEventListener('click', continueScene);
  root.querySelector('form').addEventListener('submit', event => { event.preventDefault(); continueScene(); });
  root.querySelector('.simulation-replay').addEventListener('click', () => {
    stopTyping(); audio.currentTime = 0; stage = 'loading'; position = 0;
    revealText(0); copy.hidden = false; input.value = '';
    root.querySelector('.simulation-name').hidden = true;
    root.querySelector('.simulation-warning').hidden = true;
    root.querySelector('.simulation-loading').hidden = false;
    button.textContent = 'Enter'; button.disabled = true; button.hidden = true; status.textContent = 'Loading preview';
  });
  async function asset(name) {
    const response = await fetch(`${import.meta.env.BASE_URL}pushbox_modules/maps_json/${name}.json`);
    if (!response.ok) throw new Error(`${name}: ${response.status}`);
    return (await response.json()).matrix;
  }
  Promise.all([asset('LinkSprite'), asset('Warning')]).then(([sprite, warning]) => {
    if (disposed) return;
    link = sprite;
    const heading = root.querySelector('.simulation-warning-title').getContext('2d');
    const alien = root.querySelector('.simulation-alien').getContext('2d');
    warning.forEach((row, y) => row.forEach((value, x) => {
      if (!value) return;
      if (y < 5) { heading.fillStyle = '#ef4444'; heading.fillRect(x * 4, y * 4, 4, 4); }
      else if (x >= 5 && x <= 25) { alien.fillStyle = '#fff0ba'; alien.fillRect((x - 5) * 4, (y - 5) * 4, 4, 4); }
    }));
    ready = true;
  }).catch(error => { status.textContent = `Preview assets unavailable: ${error.message}`; });
  function tick(time) {
    if (disposed) return;
    if (stage === 'loading') {
      const percent = 100;
      root.querySelector('.simulation-percent').textContent = `${percent}%`;
      root.querySelector('.load-meter').setAttribute('aria-valuenow', String(percent));
      root.querySelector('.load-meter span').style.width = `${percent}%`;
      button.disabled = !ready; button.hidden = !ready;
      if (link) {
        const ctx = root.querySelector('.simulation-link').getContext('2d'); ctx.clearRect(0, 0, 56, 76);
        const offset = [0, 17, 34, 17][motion.matches ? 1 : Math.floor(time / 80) % 4];
        for (let y = 0; y < 19; y++) for (let x = 0; x < 14; x++) {
          const value = link[y][offset + x];
          if (value) { ctx.fillStyle = palette[value]; ctx.fillRect(x * 4, y * 4, 4, 4); }
        }
      }
    }
    frame = requestAnimationFrame(tick);
  }
  frame = requestAnimationFrame(tick);
  if (import.meta.hot) import.meta.hot.dispose(() => { disposed = true; stopTyping(); cancelAnimationFrame(frame); });
}
