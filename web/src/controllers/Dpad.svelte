<script>
  import Button from './Button.svelte';
  import { playTrollSound, isWebMuted, setWebMuted } from '../shims/audio_shim.js';
  let trolling = $state(false);
  let muted = $state(false);
  let trollTimer = null;
  function dispatch(key) {
    const evt = new window.KeyboardEvent('keydown', { key, bubbles: true });
    window.dispatchEvent(evt);
  }
  function dispatchTroll() {
    if (muted) {
      // Gated: tap unmutes instead of trolling
      setWebMuted(false);
      // Also sync canonical via F
      const evt = new window.KeyboardEvent('keydown', { key: 'f', bubbles: true });
      window.dispatchEvent(evt);
      return;
    }
    playTrollSound();
    trolling = true;
    if (trollTimer) clearTimeout(trollTimer);
    // Tie cringe to actual audio ended, not fixed 2200ms (Despierta is longer)
    import('../shims/audio_shim.js').then(m => {
      const audio = m.getCurrentAudio && m.getCurrentAudio();
      if (audio) {
        const clear = () => { trolling = false; audio.removeEventListener('ended', clear); audio.removeEventListener('pause', clear); };
        audio.addEventListener('ended', clear, { once: true });
        audio.addEventListener('pause', clear, { once: true });
        // Fallback: if ended doesn't fire (e.g. loop), clear after 4s max
        trollTimer = setTimeout(clear, 4000);
      } else {
        trollTimer = setTimeout(() => trolling = false, 2200);
      }
    });
  }
  // Keep muted in sync with top mute button
  if (typeof window !== 'undefined') {
    window.addEventListener('webMuteChanged', (e) => { muted = !!e.detail; });
    // Init
    try { muted = isWebMuted(); } catch {}
  }
</script>

<div class="ctrl dpad">
  <div class="dpad-grid">
    <button class="dpad-btn up" onclick={() => dispatch('w')}>▲</button>
    <button class="dpad-btn left" onclick={() => dispatch('a')}>◀</button>
    <div class="dpad-center"></div>
    <button class="dpad-btn right" onclick={() => dispatch('d')}>▶</button>
    <button class="dpad-btn down" onclick={() => dispatch('s')}>▼</button>
  </div>
  <div class="dpad-actions">
    <Button icon="⏸" label="Pause" onclick={() => dispatch('p')} />
    <Button icon="⏪" label="Undo" onclick={() => dispatch('r')} />
    <span class:trolling={trolling} class="troll-wrap">
      {#if muted}
        <Button icon="🔊" label="Unmute" onclick={dispatchTroll} />
      {:else}
        <Button icon="🤡" variant="troll" onclick={dispatchTroll} />
      {/if}
    </span>
  </div>
</div>

<style>
  .ctrl {
    background: rgba(22, 30, 46, 0.9);
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 12px;
    display: flex;
    flex-direction: column;
    gap: 12px;
    align-items: center;
    justify-content: center;
    min-height: 160px;
    height: 160px;
    box-sizing: border-box;
  }
  .dpad { flex-direction: row; justify-content: space-around; }
  .dpad-grid {
    display: grid;
    grid-template-columns: 48px 48px 48px;
    grid-template-rows: 48px 48px 48px;
    gap: 4px;
    align-items: center;
    justify-items: center;
  }
  .dpad-grid .up { grid-column: 2; grid-row: 1; }
  .dpad-grid .left { grid-column: 1; grid-row: 2; }
  .dpad-grid .right { grid-column: 3; grid-row: 2; }
  .dpad-grid .down { grid-column: 2; grid-row: 3; }
  .dpad-center { grid-column: 2; grid-row: 2; width: 32px; height: 32px; background: var(--border); border-radius: 50%; }
  .dpad-btn { width: 48px; height: 48px; background: var(--card-bg); border: 1px solid var(--accent); color: var(--text); border-radius: 8px; font-size: 1.2rem; cursor: pointer; }
  .dpad-actions { display: flex; flex-direction: column; gap: 8px; }
  .troll-wrap { display: inline-flex; align-items: center; gap: 4px; position: relative; }
  .troll-wrap.trolling { animation: troll-shake 0.12s infinite, troll-rainbow 0.6s infinite; }
  .troll-wrap.trolling :global(.btn) { animation: troll-wobble 0.18s infinite; background: hotpink !important; color: yellow !important; border: 2px dashed lime !important; font-family: 'Comic Sans MS', cursive !important; transform: rotate(-1deg); }

  @keyframes troll-shake { 0% { transform: translateX(0) } 25% { transform: translateX(-2px) rotate(1deg) } 50% { transform: translateX(2px) rotate(-1deg) } 75% { transform: translateX(-1px) rotate(1deg) } 100% { transform: translateX(0) } }
  @keyframes troll-rainbow { 0% { filter: hue-rotate(0deg) } 100% { filter: hue-rotate(360deg) } }
  @keyframes troll-wobble { 0% { transform: scale(1) rotate(0) } 25% { transform: scale(1.15) rotate(3deg) } 50% { transform: scale(0.95) rotate(-3deg) } 75% { transform: scale(1.1) rotate(2deg) } 100% { transform: scale(1) rotate(0) } }

</style>
