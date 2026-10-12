<script>
  import { onMount } from 'svelte';
  import ContinueButton from '../components/ContinueButton.svelte';
  import { drawTitle } from './titleArt.js';
  import linkData from '../../pushbox_modules/maps_json/LinkSprite.json';
  import warningData from '../../pushbox_modules/maps_json/Warning.json';
  import { BOBBY_PALETTE } from './bobby.js';
  import './mobileOpening.css';
  let { flow, enabled = () => true, acceptKeyboard = enabled, onMute = () => {} } = $props();
  let state = $state(flow.getSnapshot()), title, link, heading, alien, input;
  let name = $state('');
  const parts = [];
  let offset = 0;
  for (const text of state.message.split(/(\s+)/u)) { parts.push({ text, offset }); offset += text.length; }
  const ready = $derived(state.phase === 'loading' ? state.ready : state.phase === 'complete' ? false : state.phase !== 'typing' || state.seen);
  function continueOpening() {
    if (state.phase === 'name') { if (!flow.submit(name)) input?.focus(); }
    else flow.continue();
  }
  function warningArt() {
    if (!heading || !alien) return;
    for (const canvas of [heading, alien]) canvas.getContext('2d').clearRect(0, 0, canvas.width, canvas.height);
    (warningData.matrix || warningData).forEach((row, y) => row.forEach((value, x) => {
      if (!value) return;
      if (y < 5) { const ctx = heading.getContext('2d'); ctx.fillStyle = '#ef4444'; ctx.fillRect(x * 4, y * 4, 4, 4); }
      else if (x >= 5 && x <= 25) { const ctx = alien.getContext('2d'); ctx.fillStyle = '#fff0ba'; ctx.fillRect((x - 5) * 4, (y - 5) * 4, 4, 4); }
    }));
  }
  $effect(() => {
    if (state.phase === 'name' || state.phase === 'complete') {
      name = state.name;
      if (state.phase === 'name') Promise.resolve().then(() => input?.focus());
    }
    if (state.phase === 'loading' && title) drawTitle(title, 0);
    if (state.phase !== 'loading') warningArt();
  });
  onMount(() => {
    let frame = null;
    const motion = window.matchMedia('(prefers-reduced-motion: reduce)');
    const stop = flow.subscribe(next => {
      state = next;
      if (next.phase !== 'loading') { cancelAnimationFrame(frame); frame = null; }
      else if (frame === null && !document.hidden) frame = requestAnimationFrame(tick);
    });
    function tick(time) {
      frame = null;
      if (state.phase !== 'loading' || document.hidden) return;
      if (state.phase === 'loading' && link && !document.hidden) {
        const ctx = link.getContext('2d'); ctx.clearRect(0, 0, 56, 76);
        const matrix = linkData.matrix || linkData;
        const frameOffset = [0, 17, 34, 17][motion.matches ? 1 : Math.floor(time / 80) % 4];
        for (let y = 0; y < 19; y++) for (let x = 0; x < 14; x++) {
          const color = matrix[y][frameOffset + x];
          if (color) { ctx.fillStyle = BOBBY_PALETTE[color]; ctx.fillRect(x * 4, y * 4, 4, 4); }
        }
      }
      frame = requestAnimationFrame(tick);
    }
    function keyboard(event) {
      if (!acceptKeyboard() || ['hidden', 'complete'].includes(state.phase)) return;
      if (event.ctrlKey || event.metaKey || event.altKey) return;
      event.stopImmediatePropagation();
      if (event.target?.closest?.('input')) {
        if (event.key === 'Enter' && !event.isComposing) { event.preventDefault(); continueOpening(); }
        return;
      }
      if (event.key === 'Enter' || event.key.toLowerCase() === 'e') { event.preventDefault(); continueOpening(); }
      else if (event.key.toLowerCase() === 'f') onMute();
    }
    const visibility = () => {
      flow.pause(document.hidden);
      if (!document.hidden && state.phase === 'loading' && frame === null) frame = requestAnimationFrame(tick);
    };
    window.addEventListener('keydown', keyboard, true);
    document.addEventListener('visibilitychange', visibility);
    return () => { stop(); cancelAnimationFrame(frame); window.removeEventListener('keydown', keyboard, true); document.removeEventListener('visibilitychange', visibility); };
  });
</script>

<div class="opening-sheet">
  {#if state.phase === 'loading'}
    <div class="opening-loading">
      <canvas bind:this={title} class="opening-title" width="256" height="112" aria-label="PushBox"></canvas>
      <h3>Loading</h3>
      <canvas bind:this={link} class="opening-link" width="56" height="76" aria-label="Link loading animation"></canvas>
      <div class="opening-meter" role="progressbar" aria-label="Loading" aria-valuemin="0" aria-valuemax="100" aria-valuenow={state.percent}><span style:width={`${state.percent}%`}></span></div>
      <p>{state.percent}%</p>
    </div>
  {:else}
    <div class="opening-warning">
      <canvas bind:this={heading} class="opening-warning-title" width="128" height="20" aria-label="Warning"></canvas>
      <canvas bind:this={alien} class="opening-alien" width="84" height="64" aria-label="Original space invader"></canvas>
      <div class="opening-content">
        {#if state.phase === 'name' || state.phase === 'complete'}
          <form onsubmit={event => { event.preventDefault(); continueOpening(); }}>
            <h3>¿Cómo te llamas?</h3>
            <input bind:this={input} bind:value={name} disabled={state.phase === 'complete'} type="text" autocomplete="name" autocapitalize="words" spellcheck="false" enterkeyhint="done" aria-label="¿Cómo te llamas?">
          </form>
        {:else}
          <p class="opening-copy">{#each parts as part}{#if /^\s+$/u.test(part.text)}{part.text}{:else}<span class="opening-word">{#each [...part.text] as character, index}<span style:visibility={part.offset + index < state.position ? 'visible' : 'hidden'}>{character}</span>{/each}</span>{/if}{/each}</p>
        {/if}
      </div>
    </div>
  {/if}
  {#if state.phase !== 'loading' || state.ready}
    <div class="opening-continue"><ContinueButton label={state.phase === 'loading' ? 'Enter' : 'Continue'} disabled={!ready} onclick={continueOpening} /></div>
  {/if}
</div>
