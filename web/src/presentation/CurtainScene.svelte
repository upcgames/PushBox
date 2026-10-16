<script>
  // Presentation of the original top/bottom black curtain, shared by preview
  // and runtime screens. Runtime animations and their clocks remain untouched.
  let { phase = 'open', revealFromTop = false, onEntered = () => {}, onExited = () => {}, children } = $props();
  function finished(event) {
    if (event.target !== event.currentTarget) return;
    if (phase === 'entering') onEntered();
    else if (phase === 'exiting') onExited();
  }
</script>

<div class="curtain-scene" class:top-down={revealFromTop} class:entering={phase === 'entering'} class:exiting={phase === 'exiting'} class:closed={phase === 'closed'}>
  <div class="scene-content" inert={phase !== 'open'}>{@render children()}</div>
  <div class="curtain top" aria-hidden="true" onanimationend={finished}></div>
  <div class="curtain bottom" aria-hidden="true"></div>
</div>

<style>
  .curtain-scene { position: relative; width: 100%; height: 100%; min-height: 0; overflow: hidden; background: #000; }
  .scene-content { width: 100%; height: 100%; min-height: 0; }
  .curtain { position: absolute; left: 0; right: 0; height: 50%; background: #000; transform: scaleY(0); z-index: 1; pointer-events: none; }
  .top { top: 0; transform-origin: top; }
  .bottom { bottom: 0; transform-origin: bottom; }
  /* 32 stepped bands echo desvanecimiento over the original 63-row console. */
  .entering .curtain { animation: curtain-open 1280ms steps(32) both; }
  .top-down.entering .top { height: 100%; transform-origin: bottom; }
  .top-down.entering .bottom { display: none; }
  .exiting .curtain { animation: curtain-close 1280ms steps(32) both; }
  .closed .curtain { transform: scaleY(1); }
  @keyframes curtain-open { from { transform: scaleY(1); } to { transform: scaleY(0); } }
  @keyframes curtain-close { from { transform: scaleY(0); } to { transform: scaleY(1); } }
  @media (prefers-reduced-motion: reduce) {
    .entering .curtain, .exiting .curtain { animation-duration: 1ms; }
  }
</style>
