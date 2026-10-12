<script>
  import { controllerServices } from './services.js';
  import WinnerControls from '../presentation/WinnerControls.svelte';
  const { sendInput } = controllerServices();
</script>

<WinnerControls onInput={sendInput} />
