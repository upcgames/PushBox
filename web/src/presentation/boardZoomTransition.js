const DESTINATIONS = new Set(['InterfazPausa', 'InterfazYouWin', 'InterfazYouLose', 'InterfazCongratulations', 'InterfazGameOver']);
const TRANSIENT_SCREENS = new Set(['gameplay', 'main']);
export const BOARD_ZOOM_DURATION = 480;

// Rects include ancestor scaling; transforms use local CSS pixels around the
// wrapper origin. The canvas can be offset inside its cropped wrapper on Resume.
export function boardZoomTransform(from, to, size = {}, origin = to) {
  if (!from || !to || from.width <= 0 || from.height <= 0 || to.width <= 0 || to.height <= 0) return null;
  const width = size.width ?? origin.width, height = size.height ?? origin.height;
  const scaleX = from.width / to.width, scaleY = from.height / to.height;
  const x = (from.left - origin.left - scaleX * (to.left - origin.left)) * width / origin.width;
  const y = (from.top - origin.top - scaleY * (to.top - origin.top)) * height / origin.height;
  return `translate(${x}px, ${y}px) scale(${scaleX}, ${scaleY})`;
}

export function createBoardZoomTransition(frame, wrap, {
  canvas = wrap, reducedMotion = () => false, schedule = requestAnimationFrame, cancelSchedule = cancelAnimationFrame,
} = {}) {
  let source = null, scene = null, queued = null, animation = null, direction = null, disposed = false, active = false;
  function transformToFrame(from) {
    const origin = wrap.getBoundingClientRect();
    return boardZoomTransform(from, canvas.getBoundingClientRect(), {
      width: wrap.offsetWidth ?? origin.width, height: wrap.offsetHeight ?? origin.height,
    }, origin);
  }
  function cancel() {
    if (queued !== null) cancelSchedule(queued);
    queued = null;
    const previous = animation; animation = null;
    previous?.cancel();
    wrap.style.removeProperty('transform');
    source = scene = direction = null;
    delete frame.dataset.framingTransition;
  }
  function animate(from, screen, mode) {
    source = null; scene = screen; direction = mode;
    frame.dataset.framingTransition = mode;
    const initial = transformToFrame(from);
    if (!initial) { cancel(); return; }
    // Hold the previous pose immediately, then let HUD/control layout settle.
    wrap.style.transform = initial;
    queued = schedule(() => {
      queued = null;
      if (disposed || reducedMotion()) { cancel(); return; }
      wrap.style.removeProperty('transform');
      const transform = transformToFrame(from);
      if (!transform) { cancel(); return; }
      const current = wrap.animate([{ transform }, { transform: 'none' }], {
        duration: BOARD_ZOOM_DURATION, easing: 'cubic-bezier(.22, .61, .36, 1)',
      });
      animation = current;
      current.finished.then(() => {
        if (animation !== current) return;
        cancel();
        if (active) source = canvas.getBoundingClientRect();
      }, () => {});
    });
  }
  function update({ active: nextActive, screen, rect, eligible, resumeFrom }) {
    if (disposed) return;
    active = nextActive;
    if (!eligible) { cancel(); return; }
    if (active) {
      // Ordinary gameplay updates must not restart or cancel a Resume zoom.
      if (direction === 'in' && scene === screen) return;
      cancel();
      source = typeof rect === 'function' ? rect() : rect;
      if (resumeFrom && !reducedMotion() && wrap.animate) animate(resumeFrom, screen, 'in');
      return;
    }
    if (scene && screen !== scene) cancel();
    if (rect) source = typeof rect === 'function' ? rect() : rect;
    if (!source || reducedMotion() || !wrap.animate) { source = null; return; }
    if (!DESTINATIONS.has(screen)) {
      if (!TRANSIENT_SCREENS.has(screen)) source = null;
      return;
    }
    animate(source, screen, 'out');
  }
  return { update, cancel, dispose() { disposed = true; cancel(); } };
}
