import { reachableBounds, wallBounds, fitBoard, usesBoardFraming } from './boardFraming.js';
import { createBoardZoomTransition } from './boardZoomTransition.js';
import map1 from '../../pushbox_modules/maps_json/mapa01.json';
import map2 from '../../pushbox_modules/maps_json/mapa02.json';
import map3 from '../../pushbox_modules/maps_json/mapa03.json';
import map4 from '../../pushbox_modules/maps_json/mapa04.json';
import map5 from '../../pushbox_modules/maps_json/mapa05.json';
import './mobileBoardView.css';

const maps = [null, map1, map2, map3, map4, map5];

// A camera over the existing console and hints, with no changes to their drawing.
export function setupMobileBoardView(root, store, enabled = () => true, { surface } = {}) {
  const frame = root.querySelector('.console-frame');
  const wrap = frame.querySelector('.canvas-wrap');
  const canvas = wrap.querySelector('canvas');
  const reducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)');
  const zoom = createBoardZoomTransition(frame, wrap, { canvas, reducedMotion: () => reducedMotion.matches });
  const pauseSoundCover = document.createElement('div');
  pauseSoundCover.className = 'mobile-pause-sound-cover';
  pauseSoundCover.setAttribute('aria-hidden', 'true');
  pauseSoundCover.hidden = true;
  wrap.append(pauseSoundCover);
  const boundsByLevel = new Map();
  let state = store.getSnapshot(), active = false, framing = 'walls';
  let resumeFrom = null;
  const stopPauseExit = store.on('screenExited', ({ screen, option }) => {
    if (screen.id === 'InterfazPausa') {
      resumeFrom = option === 1 && enabled() && framing === 'walls' ? canvas.getBoundingClientRect() : null;
    }
  });
  function layout() {
    surface?.setDrawScopeHidden('canonical-hud', enabled(), 'terrain');
    // Original InterfazPausa writes its sound caption at (15, 45), 52 cells.
    // Cover only that mobile region; canonical cells and desktop stay intact.
    const outgoingRect = active ? canvas.getBoundingClientRect() : null;
    pauseSoundCover.hidden = !enabled() || state.screen?.id !== 'InterfazPausa';
    if (!pauseSoundCover.hidden) {
      const cols = canvas.width / 14, rows = canvas.height / 14;
      pauseSoundCover.style.left = `${15 / cols * 100}%`;
      pauseSoundCover.style.top = `${45 / rows * 100}%`;
      pauseSoundCover.style.width = `${52 / cols * 100}%`;
      pauseSoundCover.style.height = `${1 / rows * 100}%`;
    }
    const game = state.game;
    if (!game) boundsByLevel.clear();
    if (game && !boundsByLevel.has(game.level)) {
      const map = maps[game.level];
      const walls = wallBounds(game);
      boundsByLevel.set(game.level, {
        walls: map ? reachableBounds(game, map.matrix) || walls : walls,
      });
    }
    const bounds = game && boundsByLevel.get(game.level)?.[framing];
    active = enabled() && usesBoardFraming(state) && !!bounds;
    if (!active) {
      delete frame.dataset.boardZoom; delete root.dataset.mobileBoard;
      resumeFrom = null;
      zoom.update({ active: false, screen: state.screen?.id, rect: outgoingRect, eligible: enabled() && framing === 'walls' });
      return;
    }
    frame.dataset.boardZoom = 'on'; root.dataset.mobileBoard = 'on';
    const styles = window.getComputedStyle(frame);
    const width = frame.clientWidth - parseFloat(styles.paddingLeft) - parseFloat(styles.paddingRight);
    const height = frame.clientHeight - parseFloat(styles.paddingTop) - parseFloat(styles.paddingBottom);
    const fitted = fitBoard(bounds, width, height);
    wrap.style.setProperty('--board-width', `${fitted.width}px`);
    wrap.style.setProperty('--board-height', `${fitted.height}px`);
    wrap.style.setProperty('--console-width', `${game.grid.cols / bounds.width * 100}%`);
    wrap.style.setProperty('--console-height', `${game.grid.rows / bounds.height * 100}%`);
    wrap.style.setProperty('--console-left', `${-bounds.x / bounds.width * 100}%`);
    wrap.style.setProperty('--console-top', `${-bounds.y / bounds.height * 100}%`);
    zoom.update({ active: true, screen: state.screen?.id, rect: () => canvas.getBoundingClientRect(), eligible: true, resumeFrom });
    resumeFrom = null;
  }
  const stop = store.subscribe(next => { state = next; layout(); });
  const observer = new ResizeObserver(layout);
  observer.observe(frame);
  const resize = () => { resumeFrom = null; zoom.cancel(); layout(); };
  const stopError = store.on('runtimeError', zoom.cancel);
  window.addEventListener('resize', resize);
  reducedMotion.addEventListener('change', resize);
  return {
    refresh: layout,
    setFraming(mode) {
      framing = ['walls', 'console'].includes(mode) ? mode : 'walls';
      layout();
    },
    dispose() {
      stop(); stopError(); stopPauseExit(); observer.disconnect(); zoom.dispose();
      window.removeEventListener('resize', resize);
      reducedMotion.removeEventListener('change', resize);
      pauseSoundCover.remove();
      surface?.setDrawScopeHidden('canonical-hud', false);
      delete frame.dataset.boardZoom; delete root.dataset.mobileBoard;
      for (const name of ['board-width', 'board-height', 'console-width', 'console-height', 'console-left', 'console-top']) {
        wrap.style.removeProperty(`--${name}`);
      }
    },
  };
}
