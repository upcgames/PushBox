<script>
  import { onDestroy } from 'svelte';
  import PixelButton from '../components/PixelButton.svelte';
  let { icon, label, variant = '', hinted = false, active = false, onPress = () => {} } = $props();
  let activated = $state(false);
  let muted = $state(false);
  let timer;
  function press() {
    if (icon === 'sound') muted = !muted;
    if (icon === 'undo' || icon === 'hourglass' || icon === 'troll') {
      activated = true;
      clearTimeout(timer);
      timer = setTimeout(() => activated = false, 1800);
    }
    onPress(icon === 'sound' ? (muted ? 'Muted preview' : 'Unmuted preview') : label);
  }
  onDestroy(() => clearTimeout(timer));
</script>

<PixelButton {icon} label={icon === 'sound' && muted ? 'Unmute' : label}
  variant={`${variant}${muted ? ' muted' : ''}`} {hinted} active={active || activated}
  pressed={icon === 'sound' ? muted : undefined} onclick={press} />
