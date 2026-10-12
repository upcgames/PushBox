<script>
  import { controllerServices } from './services.js';
  import MenuControls from '../presentation/MenuControls.svelte';
  const { sendInput } = controllerServices();
</script>

<MenuControls onInput={sendInput} />
