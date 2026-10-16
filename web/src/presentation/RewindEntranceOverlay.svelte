<script>
  import { onMount } from 'svelte';
  import PixelIcon from '../components/PixelIcon.svelte';
  import { createRewindEntranceDriver, rewindEntranceGeometry } from './rewindEntrance.js';
  import { createPreloadedAudio } from '../audio/preloadAudio.js';
  let { root, surface, store, enabled = () => true, kind = 'rewind' } = $props();
  let pose = $state(null), box = $state(null), inset = $state(0);
  onMount(() => {
    const motion = window.matchMedia('(prefers-reduced-motion: reduce)');
    // Companion cue preserves the canonical placement sound and music.
    let track = null;
    const stopMute = store.select(state => state.audio.muted, muted => {
      if (track) track.volume = muted ? 0 : 1;
    });
    const driver = createRewindEntranceDriver(store, {
      kind, enabled, reducedMotion: () => motion.matches,
      onStart() {
        try {
          track ||= createPreloadedAudio(`${import.meta.env.BASE_URL}audio/Gameboy.mp3`);
          track.currentTime = 0;
          track.volume = store.getSnapshot().audio.muted ? 0 : 1;
          track.play()?.catch(error => console.warn('[Entrance sound] Playback rejected:', error));
        } catch (error) { console.warn('[Entrance sound] Playback failed:', error); }
      },
      measure(source) {
        const slot = root.querySelector(`[data-action-slot="${kind}"]`);
        const frame = root.querySelector('.console-frame');
        if (!slot || !frame || !surface.canvas.isConnected) return null;
        const canvas = surface.canvas.getBoundingClientRect(), destination = slot.getBoundingClientRect();
        const viewport = root.getBoundingClientRect(), board = frame.getBoundingClientRect();
        const game = store.getSnapshot().game;
        return rewindEntranceGeometry(source, game, surface, { canvas, slot: destination, viewport, board });
      },
      render(next, geometry, elapsed) {
        pose = next; box = geometry.sourceBox;
        inset = Math.round(2 + Math.sin(elapsed / 100) * 2);
      },
      clear() { pose = box = null; },
    });
    const refresh = driver.refresh;
    document.addEventListener('visibilitychange', refresh);
    motion.addEventListener('change', refresh);
    return () => { driver.dispose(); stopMute(); track?.pause(); document.removeEventListener('visibilitychange', refresh); motion.removeEventListener('change', refresh); };
  });
</script>

{#if pose}
  <div class="hourglass-flight" aria-hidden="true" style:left={`${pose.x}px`} style:top={`${pose.y}px`}
    style:width={`${pose.size}px`} style:height={`${pose.size}px`}
    style:transform={`translate(-50%, -50%) rotate(${pose.rotation}deg)`}><PixelIcon name={kind === 'troll' ? 'troll' : 'hourglass'} /></div>
  <div class="caja-glow" aria-hidden="true" style:left={`${box.x - inset}px`} style:top={`${box.y - inset}px`}
    style:width={`${box.width + inset * 2}px`} style:height={`${box.height + inset * 2}px`} style:opacity={pose.glowOpacity}></div>
{/if}

<style>
  .hourglass-flight, .caja-glow { position: fixed; pointer-events: none; z-index: 80; }
  .hourglass-flight { color: #fff0ba; filter: drop-shadow(2px 2px 0 #000); display: grid; place-items: center; }
  .hourglass-flight :global(svg) { width: 100%; height: 100%; fill: currentColor; shape-rendering: crispEdges; }
  .caja-glow { border: 3px solid #fff0ba; box-sizing: border-box; }
</style>
