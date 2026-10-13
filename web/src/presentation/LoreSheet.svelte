<script>
  import { onMount } from 'svelte';
  import { lore } from './loreIllustrations.js';
  import PixelButton from '../components/PixelButton.svelte';
  import ContinueButton from '../components/ContinueButton.svelte';
  let { level, ready = true, rewardSeen = false, onContinue } = $props();
  let canvas;
  const captions = [null, 'Haz que cada movimiento cuente', 'Te reto a pisar la casilla blanca',
    '¿Y si esa caja sirve para algo más?', 'Presiona la carita si necesitas ayuda',
    'Hay paredes que esconden un secreto'];
  onMount(() => {
    const motion = window.matchMedia('(prefers-reduced-motion: reduce)');
    let frame = null, disposed = false, fontsReady = false;
    const started = performance.now();
    function paint(time) {
      frame = null;
      if (disposed || !fontsReady || document.hidden) return;
      if (!canvas.closest('[role=tabpanel]')?.hidden) {
        lore(canvas.getContext('2d'), motion.matches ? 0 : time - started, level);
      }
      frame = requestAnimationFrame(paint);
    }
    function resume() {
      if (frame !== null) cancelAnimationFrame(frame);
      frame = null;
      if (!disposed && fontsReady && !document.hidden) frame = requestAnimationFrame(paint);
    }
    document.fonts.load('14px Px437').then(() => { fontsReady = true; resume(); });
    document.addEventListener('visibilitychange', resume);
    return () => { disposed = true; if (frame !== null) cancelAnimationFrame(frame);
      document.removeEventListener('visibilitychange', resume); };
  });
</script>

<section class="lore-sheet" aria-label={`Nivel ${level}`}>
  <p class="kicker">NIVEL {String(level).padStart(2, '0')}</p>
  <div class="lore-art">
    <canvas bind:this={canvas} width={level === 5 ? 280 : 224} height={level === 5 ? 224 : 112} aria-label={captions[level]}></canvas>
    {#if level === 4}
      <div class="lore-grin"><PixelButton icon="troll" label="¿Premio?" variant="face" hinted /></div>
    {/if}
  </div>
  <h3>{level === 4 && rewardSeen ? 'Presiona la carita y celebra' : captions[level]}</h3>
  <div class="lore-continue"><ContinueButton disabled={!ready} onclick={onContinue} /></div>
</section>

<style>
  .lore-sheet { width: 100%; height: 100%; min-height: 0; box-sizing: border-box; padding: 26px 22px; display: flex; flex-direction: column; align-items: center; justify-content: center; background: #080914; color: #e9e7ef; font-family: 'Px437', monospace; text-align: center; overflow-y: auto; }
  .kicker { color: #eab308; font-size: 11px; letter-spacing: 2px; margin: 0 0 20px; }
  .lore-art { width: 280px; max-width: 100%; position: relative; flex: none; }
  .lore-sheet canvas { position: static; inset: auto; display: block; width: 100%; height: auto; image-rendering: pixelated; margin: 0; }
  .lore-grin { position: absolute; top: calc(50% - 38px); left: calc(50% - 38px); }
  h3 { font-size: 17px; font-weight: normal; line-height: 1.7; margin: 18px 0 28px; max-width: 340px; }
  .lore-continue { flex: none; }
  @media (max-height: 500px) { .lore-sheet { justify-content: flex-start; } }
</style>
