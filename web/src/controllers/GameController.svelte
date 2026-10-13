<script>
  import { onMount } from 'svelte';
  import { controllerServices } from './services.js';
  import PixelButton from '../components/PixelButton.svelte';
  import GameplayDeck from '../presentation/GameplayDeck.svelte';
  const { store: GameState, sendInput: dispatch, audio } = controllerServices();
  let reward = $state(GameState.getSnapshot().trollReward);
  let undoHint = $state(GameState.getSnapshot().undoHint);
  let entranceActive = $state(!!GameState.getSnapshot().rewindEntranceActive);
  let rewindDiscovery = $state(GameState.getSnapshot().rewindDiscovery);
  let trolling = $state(false);
  let undoing = $state(false);
  let undoTimer;
  let trollTimer;
  let stopTroll = () => {};
  let disposed = false;
  let trollRequest = 0;

  function dispatchUndo() {
    // Always let the original runtime handle unavailable undo, including its sound.
    dispatch('r');
  }
  async function dispatchTroll() {
    if (!GameState.getSnapshot().trollReward.unlocked) return;
    GameState.useTrollReward();
    const request = ++trollRequest;
    stopTroll();
    GameState.setTrollActive(true);
    await audio.playTrollSound();
    const current = await audio.getCurrentAudio();
    if (disposed || request !== trollRequest) return;
    trolling = !!current && !current.ended;
    const clear = () => {
      trolling = false;
      GameState.setTrollActive(false);
      clearTimeout(trollTimer);
      current?.removeEventListener('ended', clear);
      current?.removeEventListener('pause', clear);
    };
    stopTroll = clear;
    current?.addEventListener('ended', clear, { once: true });
    current?.addEventListener('pause', clear, { once: true });
    if (!trolling) clear();
    else trollTimer = setTimeout(clear, 4000);
  }
  onMount(() => {
    const stopReward = GameState.select(state => state.trollReward, next => reward = next);
    const stopEntrance = GameState.select(state => !!state.rewindEntranceActive, next => entranceActive = next);
    const stopDiscovery = GameState.select(state => state.rewindDiscovery, next => rewindDiscovery = next);
    const stopUndoHint = GameState.select(state => state.undoHint, next => undoHint = next);
    const off = GameState.on('input:consumed', ({ key }) => {
      if (key.toLowerCase() !== 'r' || !GameState.getSnapshot().game?.undoAvailable) return;
      undoing = true;
      clearTimeout(undoTimer);
      undoTimer = setTimeout(() => undoing = false, 1800);
    });
    return () => { stopReward(); stopUndoHint(); stopDiscovery(); stopEntrance(); GameState.setTrollActive(false); disposed = true; off(); clearTimeout(undoTimer); stopTroll(); };
  });
</script>

<GameplayDeck onDir={dispatch} rewindVisible={rewindDiscovery.visible && !entranceActive} trollVisible={reward.unlocked}>
  {#snippet rewind()}
      <PixelButton icon="hourglass" label="Retroceder" variant="rewind-hourglass" hinted={undoHint} active={undoing} onclick={dispatchUndo} />
  {/snippet}
  {#snippet troll()}
      <PixelButton icon="troll" label="¿Premio?" variant="face" hinted={reward.hinted} active={trolling} onclick={dispatchTroll} />
  {/snippet}
</GameplayDeck>
