<script>
  import Button from './Button.svelte';
  import Dpad from '../components/Dpad.svelte';
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
      setWebMuted(false);
      const evt = new window.KeyboardEvent('keydown', { key: 'f', bubbles: true });
      window.dispatchEvent(evt);
      return;
    }
    playTrollSound();
    trolling = true;
    if (trollTimer) clearTimeout(trollTimer);
    import('../shims/audio_shim.js').then(m => {
      const audio = m.getCurrentAudio && m.getCurrentAudio();
      if (audio) {
        const clear = () => { trolling = false; audio.removeEventListener('ended', clear); audio.removeEventListener('pause', clear); };
        audio.addEventListener('ended', clear, { once: true });
        audio.addEventListener('pause', clear, { once: true });
        trollTimer = setTimeout(clear, 4000);
      } else {
        trollTimer = setTimeout(() => trolling = false, 2200);
      }
    });
  }
  if (typeof window !== 'undefined') {
    window.addEventListener('webMuteChanged', (e) => { muted = !!e.detail; });
    try { muted = isWebMuted(); } catch {}
  }
</script>

<div class="ctrl game-ctrl">
  <Dpad onDir={dispatch} />
  <div class="ctrl-actions">
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
    gap: 12px;
    align-items: center;
    justify-content: space-between;
    min-height: 184px;
    height: 184px;
    box-sizing: border-box;
  }
  .game-ctrl { flex-direction: row; }
  .ctrl-actions { display: flex; flex-direction: column; gap: 8px; }
  .troll-wrap { display: inline-flex; align-items: center; gap: 4px; position: relative; }
  .troll-wrap.trolling { animation: troll-shake 0.12s infinite, troll-rainbow 0.6s infinite; }
  .troll-wrap.trolling :global(.btn) { animation: troll-wobble 0.18s infinite; background: hotpink !important; color: yellow !important; border: 2px dashed lime !important; font-family: 'Comic Sans MS', cursive !important; transform: rotate(-1deg); }
  @keyframes troll-shake { 0% { transform: translateX(0) } 25% { transform: translateX(-2px) rotate(1deg) } 50% { transform: translateX(2px) rotate(-1deg) } 75% { transform: translateX(-1px) rotate(1deg) } 100% { transform: translateX(0) } }
  @keyframes troll-rainbow { 0% { filter: hue-rotate(0deg) } 100% { filter: hue-rotate(360deg) } }
  @keyframes troll-wobble { 0% { transform: scale(1) rotate(0) } 25% { transform: scale(1.15) rotate(3deg) } 50% { transform: scale(0.95) rotate(-3deg) } 75% { transform: scale(1.1) rotate(2deg) } 100% { transform: scale(1) rotate(0) } }
</style>
