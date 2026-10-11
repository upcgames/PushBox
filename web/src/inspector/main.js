import { createRuntime } from 'virtual:pushbox-session-runtime';
import { createInputRouter } from './inputRouter.js';
import { mountSessionPanel } from './sessionPanel.js';
import '../styles/canvas.css';
import '../styles/launcher.css';
import '../styles/mute.css';
import './page.css';

const devices = [[360, 800], [393, 852], [430, 932]];
const router = createInputRouter(), panels = [], cleanups = [];
const container = document.getElementById('previews');
let selected = 0;
devices.forEach(([width, height], index) => {
  const card = document.createElement('section');
  card.className = 'preview-card'; card.style.setProperty('--device-width', `${width}px`);
  card.style.setProperty('--device-height', `${height}px`);
  card.innerHTML = `
    <div class="preview-heading"><button class="select-preview" aria-pressed="${index === 0}">${width} × ${height}</button><button class="reset-preview">Reset</button></div>
    <div class="phone-scale"><div class="phone-screen">
      <div class="status-bar"><span>9:41</span><span>▂▄▆ ▰</span></div>
      <div class="browser-top"><span>⌂</span><span class="address">▣ pushbox.local</span><span>⋮</span></div>
      <div class="web-viewport"><div class="mobile-session"></div></div>
      <div class="browser-bottom"><span>◁</span><span>○</span><span>▢</span></div>
    </div></div>
    <div class="viewport-size"></div><div class="session-status" role="status">Launcher</div>`;
  container.append(card);
  const status = card.querySelector('.session-status');
  const panel = mountSessionPanel(card.querySelector('.mobile-session'), createRuntime,
    key => { select(index); router.send(index, key); }, state => {
      status.textContent = state.error || `${state.screen?.id || 'Transition'}${state.game ? ` · Level ${state.game.level} · ${state.game.steps} moves · ${state.game.lives} lives` : ''}`;
      compare();
    }, settings => {
      if (linkInput.checked) panels.forEach(({ panel }) => panel.setStartSettings(settings));
    }, () => {
      select(index);
      if (linkInput.checked) panels.forEach(({ panel }) => panel.start());
      else panels[index].panel.start();
    });
  panels.push({ panel, card });
  cleanups.push(router.register(index, key => panel.sendInput(key)));
  card.querySelector('.reset-preview').addEventListener('click', () => panel.reset());
  card.querySelector('.select-preview').addEventListener('click', () => select(index));
  card.querySelector('.phone-screen').addEventListener('pointerdown', () => select(index));
});
function select(index) {
  selected = index;
  panels.forEach(({ card }, i) => {
    card.classList.toggle('selected', i === index);
    card.querySelector('.select-preview').setAttribute('aria-pressed', String(i === index));
  });
}
function compare() {
  if (panels.length !== devices.length) return;
  const signatures = panels.map(({ panel }) => {
    const state = panel.getSnapshot();
    return JSON.stringify({ screen: state.screen, request: state.inputRequest, game: state.game });
  });
  document.getElementById('comparison').textContent = new Set(signatures).size === 1 ? 'Sessions match' : 'Sessions differ';
}
const topInput = document.getElementById('topHeight'), bottomInput = document.getElementById('bottomHeight');
const scaleInput = document.getElementById('scale');
const framingInput = document.getElementById('framing');
function updateFraming() {
  panels.forEach(({ panel }) => panel.setFraming(framingInput.value));
}
framingInput.addEventListener('change', updateFraming);
function layout() {
  const top = Math.max(0, Math.min(100, Number(topInput.value) || 0));
  const bottom = Math.max(0, Math.min(100, Number(bottomInput.value) || 0));
  const scale = Number(scaleInput.value) / 100;
  panels.forEach(({ card, panel }, i) => {
    card.style.setProperty('--top-height', `${top}px`); card.style.setProperty('--bottom-height', `${bottom}px`);
    card.style.setProperty('--preview-scale', scale);
    const [width, height] = devices[i];
    card.style.width = `${width * scale}px`;
    card.querySelector('.phone-scale').style.height = `${height * scale}px`;
    card.querySelector('.viewport-size').textContent = `Web viewport: ${width} × ${height - 24 - top - bottom}`;
    panel.measure();
  });
  document.getElementById('scaleValue').textContent = `${scaleInput.value}%`;
}
const linkInput = document.getElementById('linked');
router.setLinked(linkInput.checked);
linkInput.addEventListener('change', () => router.setLinked(linkInput.checked));
document.getElementById('resetAll').addEventListener('click', () => { panels.forEach(({ panel }) => panel.reset()); compare(); });
const quickLevelInput = document.getElementById('quickLevel');
function jumpToLevel() {
  const startPoint = quickLevelInput.value;
  if (!startPoint) return;
  panels.forEach(({ panel }) => {
    panel.setStartSettings({ startPoint });
    panel.reset();
    panel.start();
  });
  quickLevelInput.value = ''; // Allow choosing the same level again to restart it.
}
quickLevelInput.addEventListener('change', jumpToLevel);
for (const input of [topInput, bottomInput, scaleInput]) input.addEventListener('input', layout);
function keyboard(event) {
  if (event.ctrlKey || event.metaKey || event.altKey || event.target.closest('input, select, textarea, [contenteditable]')) return;
  const key = ({ ArrowUp: 'w', ArrowDown: 's', ArrowLeft: 'a', ArrowRight: 'd' })[event.key] || event.key;
  if (!['w', 'a', 's', 'd', 'r', 'p', 'e', 'f', 'k', 'Enter', 'Backspace'].includes(key) && key.length !== 1) return;
  if (event.key === 'Enter' && event.target.closest('button')) return;
  event.preventDefault(); router.send(selected, key);
}
window.addEventListener('keydown', keyboard);
layout(); updateFraming(); select(0);
window.PushBoxInspector = { getSessions: () => panels.map(({ panel }) => panel.getSession()) };
const dispose = () => {
  window.removeEventListener('keydown', keyboard);
  framingInput.removeEventListener('change', updateFraming);
  quickLevelInput.removeEventListener('change', jumpToLevel);
  cleanups.forEach(cleanup => cleanup()); panels.forEach(({ panel }) => panel.dispose()); container.replaceChildren();
  delete window.PushBoxInspector;
};
if (import.meta.hot) import.meta.hot.dispose(dispose);
