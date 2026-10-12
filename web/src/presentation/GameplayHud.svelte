<script>
  import PixelButton from '../components/PixelButton.svelte';
  let { lives, remaining, muted = false, jolt = 0, onMute, onPause } = $props();
</script>

  <div class="game-hud" class:critical={remaining !== null && remaining < 20}>
    <span class="lives" aria-label={`${lives} vidas`}>
      {#each Array.from({ length: 5 }) as _, index}
        <span class:lost={index >= lives} aria-hidden="true">♥</span>
      {/each}
    </span>
    {#key jolt}
      <span class="steps" class:jolt={jolt > 0} aria-label={remaining === null ? 'Movimientos' : `${remaining} movimientos restantes`}>
        <small>PASOS</small><strong>{remaining === null ? '—' : String(remaining).padStart(3, '0')}</strong>
      </span>
    {/key}
    <div class="utilities">
      <PixelButton icon="sound" label={muted ? 'Activar sonido' : 'Silenciar'} variant={muted ? 'utility muted' : 'utility'}
        pressed={muted} onclick={onMute} />
      <PixelButton icon="pause" label="Pausar" variant="utility" onclick={onPause} />
    </div>
  </div>

<style>
  .game-hud { display: flex; align-items: center; justify-content: space-between; gap: 10px; padding: 12px; padding-top: calc(12px + env(safe-area-inset-top, 0px)); background: #080914; border-bottom: 4px solid #334155; font-family: 'Px437', monospace; }
  .lives { display: flex; gap: 2px; color: #ef4444; font-size: 20px; white-space: nowrap; }
  .lost { color: #334155; }
  .steps { display: flex; flex-direction: column; gap: 4px; color: #fff0ba; }
  .steps small { font-size: 10px; }
  .steps strong { font-size: 27px; font-weight: normal; font-variant-numeric: tabular-nums; }
  .utilities { display: flex; gap: 10px; }
  .critical { border-color: #991b1b; }
  .critical .steps { color: #ef4444; }
  .jolt { animation: hud-jolt 420ms steps(1); }
  @keyframes hud-jolt { 0%, 40% { transform: translate(-3px, 2px); } 20%, 60% { transform: translate(3px, -2px); } 80% { transform: translate(-1px, 0); } 100% { transform: none; } }
  @media (prefers-reduced-motion: reduce) { .jolt { animation: none; } }
</style>
