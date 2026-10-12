import { createPreloadedAudio } from '../audio/preloadAudio.js';
import { createAudioChannel } from '../audio/audioChannel.js';

export function createSessionAudio(store, baseUrl) {
  return createAudioChannel(store, { baseUrl, initialMuted: true, createAudio: createPreloadedAudio });
}
