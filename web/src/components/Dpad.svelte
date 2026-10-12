<script>
  import { onDestroy } from 'svelte';
  import PixelIcon from './PixelIcon.svelte';
  onDestroy(clearHold);
  let { verticalOnly = false, facelift = false, onDir, initialDelay = 320, repeatDelay = 320 } = $props();
  let activeDir = $state(null);
  let shellEl;
  let holdTimeout = null;
  let holdInterval = null;

  function clearHold() {
    if (holdTimeout) { clearTimeout(holdTimeout); holdTimeout = null; }
    if (holdInterval) { clearInterval(holdInterval); holdInterval = null; }
  }
  function startHold(dir) {
    clearHold();
    if (!dir) return;
    holdTimeout = setTimeout(() => {
      holdTimeout = null;
      // second move after initial delay
      if (activeDir) onDir?.(activeDir);
      holdInterval = setInterval(() => {
        if (activeDir) onDir?.(activeDir);
      }, repeatDelay);
    }, initialDelay);
  }

  function getDir(clientX, clientY) {
    if (!shellEl) return null;
    const rect = shellEl.getBoundingClientRect();
    const cx = rect.left + rect.width / 2;
    const cy = rect.top + rect.height / 2;
    const dx = clientX - cx;
    const dy = clientY - cy;
    const dist = Math.hypot(dx, dy);
    if (dist < 18) return null;
    const angle = Math.atan2(dy, dx) * 180 / Math.PI;
    let dir;
    if (angle >= -45 && angle < 45) dir = 'd';
    else if (angle >= 45 && angle < 135) dir = 's';
    else if (angle >= -135 && angle < -45) dir = 'w';
    else dir = 'a';
    if (verticalOnly) {
      if (dir === 'w' || dir === 's') return dir;
      return dy < 0 ? 'w' : 's';
    }
    return dir;
  }
  function handlePointerDown(e) {
    e.preventDefault();
    try { shellEl.setPointerCapture(e.pointerId); } catch {}
    const dir = getDir(e.clientX, e.clientY);
    if (dir) {
      activeDir = dir;
      onDir?.(dir);
      startHold(dir);
    }
  }
  function handlePointerMove(e) {
    let isActive = false;
    try { isActive = shellEl.hasPointerCapture(e.pointerId); } catch { isActive = e.buttons !== 0; }
    if (!isActive && e.type === 'pointermove' && e.buttons === 0) return;
    const dir = getDir(e.clientX, e.clientY);
    if (dir && dir !== activeDir) {
      const wasNull = activeDir === null;
      activeDir = dir;
      // uniform cadence: swaps highlight, keeps existing 640ms schedule
      // only restart window if coming from deadzone (was null)
      if (wasNull) startHold(dir);
    } else if (!dir && activeDir) {
      activeDir = null;
      clearHold();
    }
  }
  function handlePointerUp(e) {
    activeDir = null;
    clearHold();
    try { shellEl.releasePointerCapture(e.pointerId); } catch {}
  }
</script>

<div
  class="dpad-shell"
  class:facelift
  bind:this={shellEl}
  onpointerdown={handlePointerDown}
  onpointermove={handlePointerMove}
  onpointerup={handlePointerUp}
  onpointercancel={handlePointerUp}
  role="application"
  aria-label={verticalOnly ? 'Menu navigation' : 'Dpad'}
>
  <div class="dpad-grid" class:vertical-only={verticalOnly}>
    {#if !verticalOnly}
      <button class="dpad-btn up" class:active={activeDir==='w'} tabindex="-1" aria-label="Up">{#if facelift}<PixelIcon name="direction" />{:else}▲{/if}</button>
      <button class="dpad-btn left" class:active={activeDir==='a'} tabindex="-1" aria-label="Left">{#if facelift}<PixelIcon name="direction" />{:else}◀{/if}</button>
      <div class="dpad-center"></div>
      <button class="dpad-btn right" class:active={activeDir==='d'} tabindex="-1" aria-label="Right">{#if facelift}<PixelIcon name="direction" />{:else}▶{/if}</button>
      <button class="dpad-btn down" class:active={activeDir==='s'} tabindex="-1" aria-label="Down">{#if facelift}<PixelIcon name="direction" />{:else}▼{/if}</button>
    {:else}
      <button class="dpad-btn up" class:active={activeDir==='w'} tabindex="-1" aria-label="Up">{#if facelift}<PixelIcon name="direction" />{:else}▲{/if}</button>
      <div class="dpad-center vertical"></div>
      <button class="dpad-btn down" class:active={activeDir==='s'} tabindex="-1" aria-label="Down">{#if facelift}<PixelIcon name="direction" />{:else}▼{/if}</button>
    {/if}
  </div>
</div>

<style>
  .dpad-shell {
    padding: 20px;
    margin: -10px;
    touch-action: none;
    user-select: none;
    -webkit-user-select: none;
    display: flex;
    align-items: center;
    justify-content: center;
  }
  .dpad-grid {
    display: grid;
    grid-template-columns: 62px 62px 62px;
    grid-template-rows: 62px 62px 62px;
    gap: 0;
    align-items: center;
    justify-items: center;
    touch-action: none;
  }
  .dpad-grid .up { grid-column: 2; grid-row: 1; }
  .dpad-grid .down { grid-column: 2; grid-row: 3; }
  .dpad-grid.vertical-only { grid-template-columns: 62px; }
  .dpad-grid.vertical-only .up,
  .dpad-grid.vertical-only .down,
  .dpad-grid.vertical-only .dpad-center { grid-column: 1; }
  :global(.dpad-grid) .left { grid-column: 1; grid-row: 2; }
  :global(.dpad-grid) .right { grid-column: 3; grid-row: 2; }
  .dpad-center {
    grid-column: 2; grid-row: 2;
    width: 62px; height: 62px;
    background: var(--card-bg);
    border: none;
  }
  .dpad-center.vertical {
    border-left: 1px solid var(--accent);
    border-right: 1px solid var(--accent);
    border-top: none;
    border-bottom: none;
    box-sizing: border-box;
  }
  .dpad-btn {
    width: 62px; height: 62px;
    background: var(--card-bg);
    border: 1px solid var(--accent);
    color: var(--text);
    font-size: 1.35rem;
    cursor: pointer;
    display: flex; align-items: center; justify-content: center;
    touch-action: none;
    user-select: none;
    -webkit-user-select: none;
    transition: background 0.08s, filter 0.08s;
  }
  .dpad-btn.up { border-radius: 12px 12px 0 0; border-bottom: none; }
  .dpad-btn.down { border-radius: 0 0 12px 12px; border-top: none; }
  .dpad-btn.left { border-radius: 12px 0 0 12px; border-right: none; }
  .dpad-btn.right { border-radius: 0 12px 12px 0; border-left: none; }
  .dpad-btn.active { background: var(--accent); color: #0a0f1e; filter: brightness(1.15); }
  .facelift { padding: 0; margin: 0; }
  .facelift .dpad-btn { background: #334155; color: #fff0ba; border: 0; border-radius: 0; box-shadow: inset 3px 3px #64748b, inset -3px -3px #182333, 0 4px #000; }
  .facelift .dpad-center { background: #334155; }
  .facelift .dpad-center.vertical { border: 0; }
  .facelift .dpad-btn.active { background: #64748b; box-shadow: inset 3px 3px #182333, inset -3px -3px #64748b; }
  .facelift :global(svg) { width: 28px; height: 28px; fill: currentColor; shape-rendering: crispEdges; }
  .facelift .left :global(svg) { transform: rotate(-90deg); }
  .facelift .right :global(svg) { transform: rotate(90deg); }
  .facelift .down :global(svg) { transform: rotate(180deg); }
</style>
