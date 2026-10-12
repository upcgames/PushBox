<script>
  import { onMount, tick } from 'svelte';
  import NativeNameField from './NativeNameField.svelte';
  import ContinueButton from '../components/ContinueButton.svelte';
  let { flow, acceptKeyboard = () => true } = $props();
  let state = $state(flow.getSnapshot()), name = $state(''), field, dialog;
  function submit() { if (!flow.submit(name)) field?.focus(); }
  onMount(() => {
    const stop = flow.subscribe(next => {
      state = next;
      if (next.visible) { name = next.name; tick().then(() => { if (acceptKeyboard()) field?.focus(); }); }
    });
    const keyboard = event => {
      if (!state.visible || !acceptKeyboard()) return;
      event.stopImmediatePropagation();
      if (event.key === 'Tab') {
        const controls = [...dialog.querySelectorAll('input, button')];
        const index = controls.indexOf(document.activeElement);
        event.preventDefault();
        controls[(index + (event.shiftKey ? -1 : 1) + controls.length) % controls.length]?.focus();
      }
      if (event.key === 'Enter' && !event.isComposing) { event.preventDefault(); submit(); }
    };
    window.addEventListener('keydown', keyboard, true);
    return () => { stop(); window.removeEventListener('keydown', keyboard, true); };
  });
</script>

{#if state.visible}
  <div class="name-modal-backdrop">
    <section bind:this={dialog} role="dialog" aria-modal="true" aria-label="¿Cómo te llamas?" class="name-modal">
      <NativeNameField bind:this={field} bind:value={name} onsubmit={submit} />
      <ContinueButton onclick={submit} />
    </section>
  </div>
{/if}

<style>
  .name-modal-backdrop { width: 100%; height: 100%; display: flex; align-items: center; justify-content: center; overflow-y: auto; padding: 20px; box-sizing: border-box; background: #000b; }
  .name-modal { width: 100%; max-width: 340px; min-width: 0; padding: 24px 20px; box-sizing: border-box; background: #080914; color: #fff0ba; border: 2px solid #64748b; display: flex; flex-direction: column; align-items: center; gap: 24px; }
</style>
