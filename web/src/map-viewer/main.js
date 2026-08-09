import App from './App.svelte';
import { mount } from 'svelte';
import { VirtualConsole } from '../shims/virtual_console.js';

// Preload Px437 glyphs before Svelte mounts canvas (fixes 176 half-width first paint)
const _vc = new VirtualConsole('dummy', 80, 63, 14);
await _vc.loadAssets();

const app = mount(App, { target: document.getElementById('app') });
export default app;
