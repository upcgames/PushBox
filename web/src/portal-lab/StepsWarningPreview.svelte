<script>
  import { onMount } from 'svelte';
  import GameplayHud from '../presentation/GameplayHud.svelte';
  import GameplayDeck from '../presentation/GameplayDeck.svelte';
  import { BOBBY_PALETTE, drawBobby, sampleBobby } from '../presentation/bobby.js';
  import { drawStepsWarningBobby, STEPS_WARNING_DURATION } from '../presentation/stepsWarning.js';
  import { createGameState } from '../state/gameState.js';
  import { createAudioChannel } from '../audio/audioChannel.js';
  import map from '../../pushbox_modules/maps_json/mapa01.json';

  // Presentation study only. Match CuadroDeVidas's 25 × 100 ms pause.
  const WIDTH = 336, HEIGHT = 224;
  let board, audio, motion, observer;
  let frame = null, startedAt = null, disposed = false;
  let remaining = $state(20), warning = $state(null);
  let muted = $state(true), paused = $state(false), reduced = $state(false);
  let message = $state('Trigger the warning to preview 20 → 19 remaining steps.');

  function draw(time = 0, elapsed = null) {
    if (!board) return;
    const ctx = board.getContext('2d');
    for (let y = 0; y < 16; y++) for (let x = 0; x < 24; x++) {
      ctx.fillStyle = BOBBY_PALETTE[map.matrix[24 + y][24 + x]] || '#000000';
      ctx.fillRect(x * 14, y * 14, 14, 14);
    }
    // Level-1 player position, within the static canonical crop.
    const x = 168, y = 112;
    ctx.fillStyle = '#000000'; ctx.fillRect(x, y, 28, 28);
    if (elapsed !== null) {
      drawStepsWarningBobby(ctx, x, y, elapsed, {}, reduced);
    } else {
      const pose = sampleBobby(time, { reducedMotion: reduced });
      drawBobby(ctx, x - Math.round((pose.width - 28) / 2), y + 28 - pose.height, pose);
    }
  }
  function cancel() {
    if (frame !== null) cancelAnimationFrame(frame);
    frame = null;
  }
  function finish() {
    cancel(); startedAt = null; warning = null;
    audio?.stop(); draw();
  }
  function trigger() {
    finish(); paused = false; remaining = 19;
    message = 'Steps warning — movement waits until the warning finishes.';
    startedAt = performance.now();
    warning = { startedAt };
    audio?.play('HurryUp.mp3', null, 1);
    const tick = now => {
      frame = null;
      const elapsed = now - startedAt;
      if (disposed || document.hidden || board.closest('[role=tabpanel]')?.hidden) { finish(); return; }
      if (elapsed >= STEPS_WARNING_DURATION) {
        finish(); message = 'Warning finished. Try a direction, or replay the warning.'; return;
      }
      draw(now, elapsed);
      frame = requestAnimationFrame(tick);
    };
    tick(startedAt);
  }
  function direction(key) {
    if (warning) { message = 'Movement is waiting for the steps warning to finish.'; return; }
    message = paused ? 'Preview paused.' : `${{ w: 'Up', a: 'Left', s: 'Down', d: 'Right' }[key]} accepted — controls preview only; the board is static.`;
  }
  function toggleMute() { muted = !muted; audio?.setWebMuted(muted); }
  function togglePause() {
    finish(); paused = !paused;
    message = paused ? 'Preview paused.' : 'Preview resumed. Replay the steps warning.';
  }
  function reset() {
    finish(); remaining = 20; paused = false;
    message = 'Trigger the warning to preview 20 → 19 remaining steps.';
  }
  onMount(() => {
    audio = createAudioChannel(createGameState(), { baseUrl: import.meta.env.BASE_URL, initialMuted: true });
    motion = window.matchMedia('(prefers-reduced-motion: reduce)');
    const refreshMotion = () => { reduced = motion.matches; draw(performance.now(), startedAt === null ? null : performance.now() - startedAt); };
    refreshMotion(); motion.addEventListener('change', refreshMotion);
    const visibility = () => { if (document.hidden) { finish(); message = 'Preview stopped. Replay the warning when ready.'; } };
    document.addEventListener('visibilitychange', visibility);
    observer = new MutationObserver(() => {
      if (board.closest('[role=tabpanel]')?.hidden) { finish(); message = 'Preview stopped. Replay the warning when ready.'; }
    });
    observer.observe(board.closest('[role=tabpanel]'), { attributes: true, attributeFilter: ['hidden'] });
    document.fonts.load('14px Px437').then(() => { if (!disposed && !warning) draw(); });
    return () => {
      disposed = true; cancel(); audio.dispose(); observer.disconnect();
      motion.removeEventListener('change', refreshMotion);
      document.removeEventListener('visibilitychange', visibility);
    };
  });
</script>

<div class="warning-stage">
  <GameplayHud lives={5} {remaining} {muted} {paused} {warning} canResume={true} onMute={toggleMute} onPause={togglePause} />
  <canvas bind:this={board} width={WIDTH} height={HEIGHT} aria-label="Static level-1 crop with Bobby reacting to the steps warning"></canvas>
  <GameplayDeck onDir={direction} />
</div>
<div class="preview-actions">
  <button class="sample-action" onclick={trigger}>Replay warning · 20 → 19</button>
  <button class="sample-action" onclick={reset}>Reset</button>
</div>
<p class="warning-message" role="status">{message}</p>
<p>Use the speaker button to hear the original warning. Reduced motion keeps both warning colors steady.</p>

<style>
  .warning-stage { width: 360px; max-width: 100%; background: #080914; }
  canvas { width: calc(100% - 24px); max-width: none; height: auto; margin: 12px; image-rendering: pixelated; }
  .preview-actions { display: flex; flex-wrap: wrap; gap: 10px; }
  .warning-message { min-height: 42px; }
</style>
