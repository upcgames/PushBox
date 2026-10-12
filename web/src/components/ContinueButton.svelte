<script>
  import '../styles/confirmationButton.css';
  let { disabled = false, onclick, label = 'Continue', className = '' } = $props();
</script>

<button type="button" class="pixel-confirmation {className}" {disabled} {onclick}>{label}</button>
