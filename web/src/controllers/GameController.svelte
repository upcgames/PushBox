<script>
  import { onMount } from 'svelte';
  import { controllerServices } from './services.js';
  import PixelButton from '../components/PixelButton.svelte';
  import GameplayDeck from '../presentation/GameplayDeck.svelte';
  const { store: GameState, sendInput: dispatch, audio } = controllerServices();
  let reward = $state(GameState.getSnapshot().trollReward);
  let undoHint = $state(GameState.getSnapshot().undoHint);
  let undoAvailable = $state(!!GameState.getSnapshot().game?.undoAvailable);
  let entranceActive = $state(!!GameState.getSnapshot().rewindEntranceActive);
  let trollEntranceActive = $state(GameState.getSnapshot().trollEntrance.active);
  let trollLandingAt = $state(GameState.getSnapshot().trollEntrance.landedAt ?? null);
  let rewindDiscovery = $state(GameState.getSnapshot().rewindDiscovery);
  let trolling = $state(false);
  let undoing = $state(false);
  let undoTimer;
  let trollTimer;
  let stopTroll = () => {};
  let disposed = false;
  let trollRequest = 0;

  function dispatchUndo() {
    if (GameState.getSnapshot().game?.undoAvailable) dispatch('r');
  }
  async function dispatchTroll() {
    if (!GameState.getSnapshot().trollReward.unlocked) return;
    GameState.useTrollReward();
    const request = ++trollRequest;
    stopTroll();
    GameState.setTrollActive(true);
    const current = await audio.playTrollSound();
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
    const stopTrollEntrance = GameState.select(state => state.trollEntrance.active, next => trollEntranceActive = next);
    const stopTrollLanding = GameState.select(state => state.trollEntrance.landedAt ?? null, next => trollLandingAt = next);
    const stopDiscovery = GameState.select(state => state.rewindDiscovery, next => rewindDiscovery = next);
    const stopUndoHint = GameState.select(state => state.undoHint, next => undoHint = next);
    const stopUndoAvailable = GameState.select(state => !!state.game?.undoAvailable, next => undoAvailable = next);
    const off = GameState.on('input:consumed', ({ key }) => {
      if (key.toLowerCase() !== 'r' || !GameState.getSnapshot().game?.undoAvailable) return;
      undoing = true;
      clearTimeout(undoTimer);
      undoTimer = setTimeout(() => undoing = false, 1800);
    });
    return () => { stopReward(); stopUndoHint(); stopUndoAvailable(); stopDiscovery(); stopEntrance(); stopTrollEntrance(); stopTrollLanding(); GameState.setTrollActive(false); disposed = true; off(); clearTimeout(undoTimer); stopTroll(); };
  });
</script>

<GameplayDeck onDir={dispatch} rewindVisible={rewindDiscovery.visible && !entranceActive} trollVisible={reward.unlocked && !trollEntranceActive}>
  {#snippet rewind()}
      <PixelButton icon="hourglass" label="Retroceder" variant="rewind-hourglass" disabled={!undoAvailable} hinted={undoHint && undoAvailable} active={undoing && undoAvailable} onclick={dispatchUndo} />
  {/snippet}
  {#snippet troll()}
      <PixelButton icon="troll" label="¿Premio?" variant={trollLandingAt !== null && performance.now() - trollLandingAt < 400 ? 'face reward-arrival' : 'face'} hinted={reward.hinted} active={trolling} onclick={dispatchTroll} />
  {/snippet}
</GameplayDeck>
