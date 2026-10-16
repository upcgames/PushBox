<script>
  import { onMount } from 'svelte';
  import ContinueButton from '../components/ContinueButton.svelte';
  import { lesson } from './instructionIllustrations.js';
  let { ready = true, onContinue } = $props();
  let sheet;
  const lessons = [
    { kind: 'push', label: 'Empuja las cajas a su sitio' },
    { kind: 'danger', label: 'No te caigas.' },
    { kind: 'exit', label: 'Pasa al siguiente nivel' },
  ];
  onMount(() => {
    const canvases = [...sheet.querySelectorAll('canvas')];
    const motion = window.matchMedia('(prefers-reduced-motion: reduce)');
    let frame = null, disposed = false, fontsReady = false;
    const started = performance.now();
    function paint(time) {
      frame = null;
      if (disposed || !fontsReady || document.hidden) return;
      if (!sheet.closest('[role=tabpanel]')?.hidden) {
        canvases.forEach((canvas, index) => lesson(canvas.getContext('2d'),
          motion.matches ? 0 : time - started, lessons[index].kind, true));
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
    return () => {
      disposed = true;
      if (frame !== null) cancelAnimationFrame(frame);
      document.removeEventListener('visibilitychange', resume);
    };
  });
</script>

<section class="instruction-sheet" bind:this={sheet} aria-label="Instrucciones">
  <h3>Instrucciones</h3>
  {#each lessons as item, index}
    <div class="lesson">
      <span class="number">{String(index + 1).padStart(2, '0')}</span>
      <div class="lesson-content">
        <canvas width="224" height="112" class:danger={item.kind === 'danger'} aria-label={item.label}></canvas>
        <h4>{item.label}</h4>
      </div>
    </div>
  {/each}
  <div class="instruction-continue"><ContinueButton disabled={!ready} onclick={onContinue} /></div>
</section>

<style>
  .instruction-sheet { width: 100%; height: 100%; min-height: 0; box-sizing: border-box; padding: 16px 20px; display: flex; flex-direction: column; background: #000; color: #e9e7ef; font-family: 'Px437', monospace; overflow-y: auto; }
  h3 { margin: 4px 0 12px; font-size: 18px; font-weight: normal; line-height: 1.6; text-align: center; flex: none; }
  .lesson { position: relative; flex: 1 0 auto; min-height: 120px; border-top: 2px solid #334155; padding: 8px 0; display: flex; align-items: center; justify-content: center; }
  .number { position: absolute; top: 8px; left: 0; font-size: 12px; color: #94a3b8; }
  .lesson-content { display: flex; flex-direction: column; align-items: center; gap: 6px; max-width: 100%; }
  .instruction-sheet canvas { position: static; inset: auto; display: block; width: 252px; max-width: 100%; height: auto; max-height: 126px; object-fit: contain; image-rendering: pixelated; flex: none; margin-bottom: -36px; }
  .instruction-sheet canvas.danger { margin-bottom: 0; }
  h4 { margin: 0; font-size: 11px; font-weight: normal; text-align: center; flex: none; }
  .instruction-continue { align-self: center; flex: none; margin: 16px 0 4px; }
</style>
