<script>
  let { value = $bindable(''), disabled = false, onsubmit = () => {} } = $props();
  let input;
  export function focus() { input?.focus(); }
</script>

<form class="native-name-field" onsubmit={event => { event.preventDefault(); onsubmit(); }}>
  <h3>¿Cómo te llamas?</h3>
  <input bind:this={input} bind:value {disabled} type="text" autocomplete="name" autocapitalize="words" spellcheck="false" enterkeyhint="done" aria-label="¿Cómo te llamas?">
</form>

<style>
  .native-name-field { width: 100%; }
  h3 { font: normal 17px/1.6 Px437, monospace; margin: 0 0 24px; text-align: center; }
  input { box-sizing: border-box; min-width: 0; width: 100%; border: 2px solid #64748b; border-bottom: 4px solid #eab308; border-radius: 0; color: #fff0ba; background: #151725; padding: 12px; min-height: 48px; font: 16px Px437, monospace; }
  input:focus { outline: 2px solid #fff0ba; outline-offset: 2px; }
</style>
