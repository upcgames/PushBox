import { mountMobileOpening } from '../presentation/mountMobileOpening.js';
import { createPlayerProfile } from '../presentation/playerIdentity.js';
import { createSeenProgress } from '../state/seenProgress.js';
import { mountTrollReward } from '../presentation/trollReward.js';
import { mountRewindEntrance } from '../presentation/mountRewindEntrance.js';
import { mountRewindDiscovery } from '../presentation/rewindDiscovery.js';
import { mountUndoHint } from '../presentation/undoHint.js';
import { mountExitCue } from '../presentation/mountExitCue.js';
import { mountBobby } from '../presentation/mountBobby.js';
import { populateStartPoints, startPointSettings } from '../shell/startPoints.js';
import { mountMobileLore } from '../presentation/mountMobileLore.js';
import { createGameSession } from '../runtime/createGameSession.js';
import { setupBoardFeedback } from '../feedback/boardFeedback.js';
import { setupSessionControls } from '../shell/controllerMount.js';
import { mountMobileInstructions } from '../presentation/mountMobileInstructions.js';
import { mountGameplayHud } from '../presentation/mountGameplayHud.js';
import { setupMobileBoardView } from '../presentation/mobileBoardView.js';

export function mountSessionPanel(root, runtimeFactory, routeInput, changed, settingsChanged = () => {}, requestStart,
  { progress = createSeenProgress({ storage: null }) } = {}) {
  root.innerHTML = `
    <div class="console-frame">
      <div class="launcher-overlay">
        <div class="launcher-title">PUSHBOX</div>
        <div class="dev-options"><h3>Start point</h3>
          <div class="dev-row"><select aria-label="Start point"></select></div>
          <label class="dev-row">Skip lore <input class="skip-lore" type="checkbox"></label>
        </div>
        <button class="start-btn" disabled>Loading fonts…</button>
      </div>
      <button class="mute-btn" aria-label="Unmute this preview">🔇</button>
      <div class="canvas-wrap"><canvas width="1120" height="882"></canvas></div>
    </div>
    <div class="controller-area"></div>`;
  const previewProgress = progress;
  const previewProfile = createPlayerProfile({ storage: null });
  const canvas = root.querySelector('canvas');
  const launcher = root.querySelector('.launcher-overlay');
  const startButton = root.querySelector('.start-btn');
  const mute = root.querySelector('.mute-btn');
  const startPoint = root.querySelector('select');
  populateStartPoints(startPoint);
  const skipLore = root.querySelector('.skip-lore');
  const previewSettings = root.closest('.preview-card')?.querySelector('.preview-launch-settings');
  if (previewSettings) previewSettings.append(root.querySelector('.dev-options'));
  const changeStartPoint = () => settingsChanged({ startPoint: startPoint.value });
  const changeSkipLore = () => settingsChanged({ skipLore: skipLore.checked });
  startPoint.addEventListener('change', changeStartPoint);
  skipLore.addEventListener('change', changeSkipLore);
  let session, stopState, stopAudio, stopControls, stopHints, stopHud, instructions, loreView, boardView, bobby, exitCue, trollReward, undoHint, rewindDiscovery, rewindEntrance, opening, ready, running = false, disposed = false;
  let framing = 'walls';
  function teardown() {
    instructions?.dispose();
    loreView?.dispose();
    boardView?.dispose();
    bobby?.dispose();
    exitCue?.dispose();
    trollReward?.dispose();
    undoHint?.dispose();
    rewindDiscovery?.dispose();
    rewindEntrance?.dispose();
    opening?.dispose();
    stopHud?.(); stopState?.(); stopAudio?.(); stopControls?.(); stopHints?.(); session?.dispose();
  }
  function initialize() {
    teardown(); running = false; launcher.hidden = false;
    startButton.disabled = true; startButton.textContent = 'Loading fonts…';
    session = createGameSession(canvas, runtimeFactory, { baseUrl: import.meta.env.BASE_URL });
    const current = session;
    opening = mountMobileOpening(root, session.state, session.audio, { surface: session.console, progress: previewProgress, profile: previewProfile,
      onEnter: destination => destination ? start() : requestStart ? requestStart() : start() });
    opening.setLoading(0); session.setOpening(opening);
    trollReward = mountTrollReward(session.state, { progress: previewProgress });
    rewindDiscovery = mountRewindDiscovery(session.state, { progress: previewProgress });
    undoHint = mountUndoHint(session.state);
    exitCue = mountExitCue(session.console, session.state);
    bobby = mountBobby(session.console, session.state);
    stopState = session.state.subscribe(state => { changed(state); });
    stopAudio = session.state.select(state => state.audio.muted, muted => {
      mute.textContent = muted ? '🔇' : '🔊'; mute.setAttribute('aria-label', muted ? 'Unmute this preview' : 'Mute this preview');
    });
    const services = { store: session.state, sendInput: routeInput, audio: session.audio };
    stopHud = mountGameplayHud(root, session.state, services);
    instructions = mountMobileInstructions(root, session.state, routeInput);
    loreView = mountMobileLore(root, session.state, routeInput);
    stopControls = setupSessionControls(root.querySelector('.controller-area'), services);
    stopHints = setupBoardFeedback(canvas, session.state, { mobile: () => true });
    rewindEntrance = mountRewindEntrance(root, session.console, session.state);
    boardView = setupMobileBoardView(root, session.state, undefined, { surface: session.console });
    boardView.setFraming(framing);
    ready = session.loadAssets(percent => { if (session === current && !disposed) opening.setLoading(percent); }).then(() => {
      if (disposed || session !== current) return;
      startButton.disabled = false; startButton.textContent = 'Start game';
      opening.setLoading(100, true);
    });
  }
  async function start() {
    const current = session;
    await ready;
    if (disposed || current !== session || running) return;
    running = true; launcher.hidden = true;
    opening.hideLoading();
    session.start(startPointSettings(startPoint.value, skipLore.checked)).catch(error => {
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
    start, reset: initialize,
    setFraming(mode) { framing = mode; boardView.setFraming(mode); },
    setStartSettings(settings) {
      if (settings.startPoint !== undefined) startPoint.value = settings.startPoint;
      if (settings.skipLore !== undefined) skipLore.checked = settings.skipLore;
    },
    sendInput(key) { if (running) session.sendInput(key); },
    seenProgress: previewProgress,
    clearSeen(names) { previewProgress.clear(names); initialize(); },
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
