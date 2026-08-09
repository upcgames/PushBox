import { defineConfig } from 'vite';
import { resolve } from 'path';
import eslint from 'vite-plugin-eslint';
import { svelte } from '@sveltejs/vite-plugin-svelte';

export default defineConfig({
  base: process.env.GITHUB_ACTIONS ? '/PushBox/' : '/',
  root: '.',
  publicDir: 'public',
  plugins: [
    svelte(),
    eslint({
      include: ['src/**/*.js', 'src/**/*.svelte']
    })
  ],
  server: {
    host: true, // Listens on all IP addresses (0.0.0.0) & checks IPv4/IPv6 port collisions
  },
  build: {
    outDir: 'dist',
    rollupOptions: {
      input: {
        main: resolve(import.meta.dirname, 'index.html'),
        mapViewer: resolve(import.meta.dirname, 'map-viewer.html'),
        sceneViewer: resolve(import.meta.dirname, 'scene-viewer.html')
      }
    }
  }
});
