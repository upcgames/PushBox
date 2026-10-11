export function createSessionAudio(store, baseUrl) {
  let current = null, muted = true;
  function setWebMuted(value) {
    muted = !!value;
    if (current) current.volume = muted ? 0 : 1;
    store.publish({ audio: { muted } }, 'audioChanged');
  }
  function stop() { if (current) current.pause(); current = null; }
  function play(filename, reserved, flags) {
    stop();
    if (!filename) return;
    const file = String(filename).split(/[\\/]/).pop();
    current = new Audio(`${baseUrl}audio/${file}`);
    current.loop = !!(flags & 8); current.volume = muted ? 0 : 1;
    current.play().catch(() => {});
  }
  setWebMuted(true);
  return { play, stop, setWebMuted, isWebMuted: () => muted, getCurrentAudio: () => current,
    playTrollSound: () => play(['Sabe.wav', 'Terroristas.wav', 'Despierta.wav', 'Rbr.wav'][Math.floor(Math.random() * 4)], null, 1) };
}
