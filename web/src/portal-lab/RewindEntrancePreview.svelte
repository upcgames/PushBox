<script>
  import { onMount } from 'svelte';
  import GameplayDeck from '../presentation/GameplayDeck.svelte';
  import PixelIcon from '../components/PixelIcon.svelte';
  import PreviewPixelButton from './PreviewPixelButton.svelte';
  import { sampleRewindEntrance } from '../presentation/rewindEntrance.js';
  import { drawBobby } from '../presentation/bobby.js';
  let { kind = 'rewind' } = $props();
  const carita = $derived(kind === 'troll');

  let stage, board;
  let rewindVisible = $state(false), cueVisible = $state(false);
  let cueX = $state(0), cueY = $state(0), cueSize = $state(12);
  let cueRotation = $state(0);
  let message = $state('Press the trigger to replay the entrance.');
  let frame = null, disposed = false, geometry = null;
  let recovered = $state(false), earned = $state(false);
  let motion;
  const SIZE = 28, WIDTH = 336, HEIGHT = 224;
  const trapped = { x: 2, y: 2 }, previous = { x: 3, y: 2 };

  function draw(time = 0, glowOpacity = 1) {
    if (!board) return;
    const ctx = board.getContext('2d');
    ctx.fillStyle = '#080914'; ctx.fillRect(0, 0, WIDTH, HEIGHT);
    for (let y = 0; y < 8; y++) for (let x = 0; x < 12; x++) {
      const wall = x === 0 || x === 11 || y === 0 || y === 7 || (!carita && ((y === 1 && x >= 1 && x <= 4) || (x === 1 && y <= 3)));
      ctx.fillStyle = wall ? '#334155' : '#d946ef';
      ctx.fillRect(x * SIZE, y * SIZE, SIZE, SIZE);
      if (wall) {
        ctx.fillStyle = '#64748b'; ctx.fillRect(x * SIZE, y * SIZE, SIZE, 2);
      }
    }
    if (carita) {
      for (const tileX of [2, 5, 8]) {
        ctx.fillStyle = '#eab308'; ctx.fillRect(tileX * SIZE, 2 * SIZE, SIZE, SIZE);
        if (tileX !== 2) {
          ctx.fillStyle = '#854d0e'; ctx.fillRect(tileX * SIZE + 3, 2 * SIZE + 3, SIZE - 6, SIZE - 6);
        }
      }
    }
    ctx.strokeStyle = '#fff0ba'; ctx.lineWidth = 2;
    ctx.strokeRect(7 * SIZE + 5, 5 * SIZE + 5, SIZE - 10, SIZE - 10);
    const box = carita ? (earned ? trapped : previous) : recovered ? previous : trapped;
    ctx.fillStyle = '#701a75'; ctx.fillRect(box.x * SIZE, box.y * SIZE, SIZE, SIZE);
    drawBobby(ctx, (recovered ? 4 : 3) * SIZE, (carita ? 3 : 2) * SIZE, {});
    if (time > 0 && !recovered) {
      ctx.save(); ctx.globalAlpha = glowOpacity;
      ctx.strokeStyle = '#fff0ba'; ctx.lineWidth = 3;
      const inset = Math.round(2 + Math.sin(time / 100) * 2);
      ctx.strokeRect(trapped.x * SIZE - inset, trapped.y * SIZE - inset, SIZE + inset * 2, SIZE + inset * 2);
      ctx.restore();
    }

  }
  function measure() {
    if (!stage || !board) return;
    const bounds = stage.getBoundingClientRect(), canvas = board.getBoundingClientRect();
    const slot = stage.querySelector(`[data-action-slot="${kind}"]`).getBoundingClientRect();
    const scale = canvas.width / WIDTH;
    geometry = {
      x: canvas.left - bounds.left + (trapped.x + 0.5) * SIZE * scale,
      y: canvas.top - bounds.top + (trapped.y + 0.5) * SIZE * scale,
      top: canvas.top - bounds.top,
      right: bounds.width - 36,
      endX: slot.left - bounds.left + slot.width / 2,
      endY: slot.top - bounds.top + slot.height / 2,
    };
  }
  function stop() { if (frame !== null) cancelAnimationFrame(frame); frame = null; }
  function trigger() {
    stop(); recovered = false; earned = true; rewindVisible = false; cueVisible = false; draw(); measure();
    if (!geometry || disposed) return;
    if (motion?.matches) {
      rewindVisible = true;
      message = carita ? 'Carita earned. Press it to celebrate.' : 'Rewind is available. Press it to recover the caja.';
      return;
    }
    const started = performance.now();
    cueX = geometry.x; cueY = geometry.y;
    cueVisible = true; cueSize = 12; cueRotation = 0;
    message = carita ? 'The third placed caja earns the carita.' : 'The hourglass pops out of the trapped caja.';
    const tick = now => {
      frame = null;
      if (disposed || document.hidden || stage.closest('[role=tabpanel]')?.hidden) { cueVisible = false; draw(); return; }
      const elapsed = now - started;
      const pose = sampleRewindEntrance(elapsed, geometry);
      cueX = pose.x; cueY = pose.y; cueSize = pose.size; cueRotation = pose.rotation;
      const icon = carita ? 'carita' : 'hourglass';
      message = pose.flying ? `The spinning ${icon} curves back into its slot.` : `The ${icon} pops up and holds above the caja.`;
      draw(pose.glowOpacity === 0 ? 0 : elapsed, pose.glowOpacity);
      if (pose.complete) {
        cueVisible = false; rewindVisible = true; draw();
        message = carita ? 'Carita earned. Press it to celebrate.' : 'Rewind is available. Press it to recover the caja.';
      } else frame = requestAnimationFrame(tick);
    };
    frame = requestAnimationFrame(tick);
  }
  function rewind() {
    recovered = true; draw();
    message = 'Caja recovered: a simulated one-step rewind.';
  }
  onMount(() => {
    motion = window.matchMedia('(prefers-reduced-motion: reduce)');
    document.fonts.load('14px Px437').then(() => { if (!disposed) draw(); });
    const resize = new ResizeObserver(measure); resize.observe(stage);
    draw();
    return () => { disposed = true; stop(); resize.disconnect(); };
  });
</script>

<div class="entrance-scroll">
  <div class="entrance-stage" bind:this={stage}>
    <div class="board-caption">GAME CANVAS · {carita ? 'THIRD CAJA REWARD' : 'DEADLOCK STUDY'}</div>
    <canvas bind:this={board} width="336" height="224" aria-label={carita ? 'Static board preview with three caja targets and Bobby' : 'Static board with a caja trapped in a corner, Bobby to its right, and a target below'}></canvas>
    <GameplayDeck rewindVisible={!carita && rewindVisible} trollVisible={carita && rewindVisible} onDir={() => message = 'The D-pad stays in place during the entrance.'}>
      {#snippet rewind()}
        <PreviewPixelButton icon="hourglass" label="Retroceder" variant="rewind-hourglass" hinted={!recovered} onPress={rewind} />
      {/snippet}
      {#snippet troll()}
        <PreviewPixelButton icon="troll" label="¿Premio?" variant="face reward-arrival" hinted onPress={() => message = 'Carita celebration button pressed. Preview only.'} />
      {/snippet}
    </GameplayDeck>
    {#if cueVisible}
      <div class="flying-cue" aria-hidden="true" style:left={`${cueX}px`} style:top={`${cueY}px`} style:width={`${cueSize}px`} style:height={`${cueSize}px`} style:transform={`translate(-50%, -50%) rotate(${cueRotation}deg)`}>
        <PixelIcon name={carita ? 'troll' : 'hourglass'} />
      </div>
    {/if}
  </div>
</div>
<button class="sample-action" onclick={trigger}>{carita ? 'Place third caja · Replay carita' : 'Trigger deadlock hint'}</button>
<p class="entrance-message" aria-live="polite">{message}</p>

<style>
  .entrance-scroll { overflow-x: auto; padding: 4px 0; }
  .entrance-stage { position: relative; width: 360px; min-width: 360px; background: #080914; }
  .board-caption { padding: 14px 12px 12px; color: #94a3b8; font: 9px Px437, monospace; }
  canvas { display: block; margin: 0 12px 16px; width: 336px; max-width: none; height: 224px; image-rendering: pixelated; }
  .flying-cue { position: absolute; display: grid; place-items: center; color: #fff0ba; filter: drop-shadow(2px 2px 0 #080914); pointer-events: none; z-index: 2; }
  .flying-cue :global(svg) { width: 100%; height: auto; fill: currentColor; shape-rendering: crispEdges; }
  .entrance-message { min-height: 42px; }
</style>
