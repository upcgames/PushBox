<script>
  import PixelIcon from './PixelIcon.svelte';
  import '../styles/pixelControls.css';
  let { icon, label, variant = '', active = false, hinted = false, pressed = undefined, disabled = false, onclick } = $props();
</script>

<button type="button" class="pixel-control {variant}" class:activated={active} class:hinted
  aria-label={label} aria-pressed={pressed} {disabled} onclick={onclick}>
  <PixelIcon name={icon} muted={icon === 'sound' && pressed === true} />
</button>
