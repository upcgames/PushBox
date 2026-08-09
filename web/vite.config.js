import { defineConfig } from 'vite';
import { resolve } from 'path';
import eslint from 'vite-plugin-eslint';

export default defineConfig({
  root: '.',
  publicDir: 'public',
  plugins: [
    eslint({
      include: ['src/**/*.js']
    })
  ],
  server: {
    host: true, // Listens on all IP addresses (0.0.0.0) & checks IPv4/IPv6 port collisions
  },
  build: {
    outDir: 'dist',
    rollupOptions: {
      input: {
        main: resolve(__dirname, 'index.html'),
        mapViewer: resolve(__dirname, 'map-viewer.html'),
        sceneViewer: resolve(__dirname, 'scene-viewer.html')
      }
    }
  }
});
