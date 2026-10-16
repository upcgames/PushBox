<script>
  import { onMount, tick } from 'svelte';
  import ContinueButton from '../components/ContinueButton.svelte';
  let { destinations, onChoose, onClose, acceptKeyboard = () => true } = $props();
  let dialog;
  onMount(() => {
    const previous = document.activeElement;
    tick().then(() => { if (acceptKeyboard()) dialog?.querySelector('button')?.focus(); });
    function keyboard(event) {
      if (!acceptKeyboard()) return;
      event.stopImmediatePropagation();
      if (event.key === 'Escape') { event.preventDefault(); onClose(); }
      else if (event.key === 'Tab') {
        const buttons = [...dialog.querySelectorAll('button')];
        const index = buttons.indexOf(document.activeElement);
        event.preventDefault();
        buttons[(index + (event.shiftKey ? -1 : 1) + buttons.length) % buttons.length]?.focus();
      }
    }
    window.addEventListener('keydown', keyboard, true);
    return () => { window.removeEventListener('keydown', keyboard, true); if (previous?.isConnected && acceptKeyboard()) previous.focus(); };
  });
</script>

<div class="destination-backdrop">
  <section class="destination-dialog" bind:this={dialog} role="dialog" aria-modal="true" aria-label="Saltar directo a">
    <h3>Saltar directo a</h3>
    <div class="destinations">
      {#each destinations as destination (destination.id)}
        <button type="button" onclick={() => onChoose(destination.id)}>{destination.label}</button>
      {/each}
    </div>
    <ContinueButton label="Cerrar" onclick={onClose} />
  </section>
</div>

<style>
  .destination-backdrop { position: absolute; inset: 0; z-index: 1; padding: 20px; box-sizing: border-box; background: #000b; display: flex; align-items: center; justify-content: center; }
  .destination-dialog { width: 100%; max-width: 340px; min-height: 0; max-height: 100%; box-sizing: border-box; display: flex; flex-direction: column; align-items: center; gap: 20px; background: #000; border: 2px solid #64748b; padding: 20px 16px; color: #fff0ba; font-family: Px437, monospace; }
  .destination-dialog h3 { flex: none; margin: 0; max-width: 100%; text-align: center; font: normal 17px/1.6 Px437, monospace; }
  .destinations { display: flex; flex-direction: column; width: 100%; min-height: 0; overflow-y: auto; overscroll-behavior: contain; gap: 10px; padding: 3px; box-sizing: border-box; }
  .destinations button { flex: none; width: 100%; min-width: 0; min-height: 48px; border: 0; border-radius: 0; padding: 12px 16px; background: #334155; color: #fff0ba; font: 12px/1.5 Px437, monospace; box-shadow: inset 2px 2px #64748b, inset -2px -2px #182333; overflow-wrap: break-word; cursor: pointer; touch-action: manipulation; }
  button:focus-visible { outline: 2px solid #fff0ba; outline-offset: 2px; }
  button:active { background: #182333; }
</style>
