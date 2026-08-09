// Win32 Multimedia API Shims (1-Channel Audio Architecture)
window.TEXT = (str) => str;
window.SND_SYNC = 0;
window.SND_ASYNC = 1;
window.SND_NODEFAULT = 2;
window.SND_MEMORY = 4;
window.SND_LOOP = 8;
window.SND_NOSTOP = 16;

let currentAudio = null;

export function PlaySound(soundFile, reserved, flags) {
  // Stop any currently playing 1-channel audio track immediately
  if (currentAudio) {
    currentAudio.pause();
    currentAudio = null;
  }

  // PlaySound(null) or null filename stops audio playback
  if (!soundFile) return;

  try {
    const filename = (typeof soundFile === 'string') ? soundFile.split('/').pop() : '';
    if (!filename) return;

    const audioPath = `${import.meta.env.BASE_URL}audio/${filename}`;
    const audio = new Audio(audioPath);
    
    if ((flags & window.SND_LOOP) !== 0) {
      audio.loop = true;
    }

    currentAudio = audio;
    audio.play().catch((err) => {
      console.warn(`[Audio] PlaySound play() rejected for ${filename}:`, err);
    });
  } catch (err) {
    console.warn(`[Audio] Audio playback warning for ${soundFile}:`, err);
  }
}

export function StopSound() {
  if (currentAudio) {
    currentAudio.pause();
    currentAudio = null;
  }
}

window.PlaySound = PlaySound;
window.StopSound = StopSound;
