import { createGameSession } from '../runtime/createGameSession.js';
import { setupBoardFeedback } from '../feedback/boardFeedback.js';
import { setupSessionControls } from '../shell/controllerMount.js';
import { setupMobileBoardView } from '../presentation/mobileBoardView.js';

export function mountSessionPanel(root, runtimeFactory, routeInput, changed, settingsChanged = () => {}, requestStart) {
  root.innerHTML = `
    <div class="mobile-title">PUSHBOX</div>
    <div class="console-frame">
      <div class="launcher-overlay">
        <div class="launcher-title">PUSHBOX</div>
        <div class="dev-options"><h3>Start point</h3>
          <div class="dev-row"><select aria-label="Start point">
            <option value="1">Level 1</option><option value="2">Level 2</option>
            <option value="3">Level 3</option><option value="4">Level 4</option>
            <option value="5">Level 5</option><option value="0">Full introduction</option>
            <option value="-1">Skip intro · menu</option>
          </select></div>
          <label class="dev-row">Skip lore <input class="skip-lore" type="checkbox" checked></label>
        </div>
        <button class="start-btn" disabled>Loading fonts…</button>
      </div>
      <button class="mute-btn" aria-label="Unmute this preview">🔇</button>
      <button class="feedback-button" aria-pressed="true" hidden>Hints on</button>
      <div class="canvas-wrap"><canvas width="1120" height="882"></canvas></div>
    </div>
    <div class="controller-area"></div>`;
  const canvas = root.querySelector('canvas');
  const launcher = root.querySelector('.launcher-overlay');
  const startButton = root.querySelector('.start-btn');
  const mute = root.querySelector('.mute-btn');
  const startPoint = root.querySelector('select');
  const skipLore = root.querySelector('.skip-lore');
  const changeStartPoint = () => settingsChanged({ startPoint: startPoint.value });
  const changeSkipLore = () => settingsChanged({ skipLore: skipLore.checked });
  startPoint.addEventListener('change', changeStartPoint);
  skipLore.addEventListener('change', changeSkipLore);
  let session, stopState, stopAudio, stopControls, stopHints, boardView, ready, running = false, disposed = false;
  let framing = 'walls';
  function measure() {
    const game = root.querySelector('.canvas-wrap').getBoundingClientRect();
    const controls = root.querySelector('.controller-area').getBoundingClientRect();
    root.dataset.title = root.clientHeight - game.height - controls.height > 80 ? 'show' : 'hide';
  }
  function teardown() {
    boardView?.dispose();
    stopState?.(); stopAudio?.(); stopControls?.(); stopHints?.(); session?.dispose();
  }
  function initialize() {
    teardown(); running = false; launcher.hidden = false;
    startButton.disabled = true; startButton.textContent = 'Loading fonts…';
    session = createGameSession(canvas, runtimeFactory, { baseUrl: import.meta.env.BASE_URL });
    const current = session;
    stopState = session.state.subscribe(state => { changed(state); measure(); });
    stopAudio = session.state.select(state => state.audio.muted, muted => {
      mute.textContent = muted ? '🔇' : '🔊'; mute.setAttribute('aria-label', muted ? 'Unmute this preview' : 'Mute this preview');
    });
    stopControls = setupSessionControls(root.querySelector('.controller-area'), {
      store: session.state, sendInput: routeInput, audio: session.audio,
    }, measure);
    stopHints = setupBoardFeedback(canvas, root.querySelector('.feedback-button'), session.state);
    boardView = setupMobileBoardView(root, session.state);
    boardView.setFraming(framing);
    ready = session.loadAssets().then(() => {
      if (disposed || session !== current) return;
      startButton.disabled = false; startButton.textContent = 'Start game';
    });
  }
  async function start() {
    const current = session;
    await ready;
    if (disposed || current !== session || running) return;
    running = true; launcher.hidden = true;
    const value = Number(startPoint.value);
    session.start({ skipIntro: value !== 0, startLevel: value > 0 ? value : 0,
      skipLore: skipLore.checked }).catch(error => {
      if (current !== session || disposed) return;
      changed({ screen: { id: 'error' }, error: error.message });
    });
  }
  const clickStart = () => requestStart ? requestStart() : start();
  startButton.addEventListener('click', clickStart);
  const toggleMute = () => session.audio.setWebMuted(!session.state.getSnapshot().audio.muted);
  mute.addEventListener('click', toggleMute);
  initialize();
  return {
    start, reset: initialize, measure,
    setFraming(mode) { framing = mode; boardView.setFraming(mode); measure(); },
    setStartSettings(settings) {
      if (settings.startPoint !== undefined) startPoint.value = settings.startPoint;
      if (settings.skipLore !== undefined) skipLore.checked = settings.skipLore;
    },
    sendInput(key) { if (running) session.sendInput(key); },
    getSnapshot: () => session.state.getSnapshot(),
    getSession: () => session,
    dispose() {
      disposed = true; teardown(); startButton.removeEventListener('click', clickStart);
      mute.removeEventListener('click', toggleMute);
      startPoint.removeEventListener('change', changeStartPoint);
      skipLore.removeEventListener('change', changeSkipLore);
    },
  };
}
