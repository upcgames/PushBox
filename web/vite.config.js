import { defineConfig } from "vite-plus";
import { resolve } from "path";
import eslint from "vite-plugin-eslint";
import { svelte } from "@sveltejs/vite-plugin-svelte";
import { runtimeStatePlugin } from './plugins/runtime-state.js';
import { availablePortPlugin } from './plugins/available-port.js';
import { sessionRuntimePlugin } from './plugins/session-runtime.js';

export default defineConfig({
  base: process.env.GITHUB_ACTIONS ? "/PushBox/" : "/",
  root: ".",
  publicDir: "public",
  plugins: [
    availablePortPlugin(),
    sessionRuntimePlugin(),
    runtimeStatePlugin(),
    svelte(),
    eslint({
      include: ["src/**/*.js", "src/**/*.svelte"],
    }),
  ],
  server: {
    // Keep LAN access; availablePortPlugin checks loopback and wildcard
    // occupancy at listen time. Vite manages the default and restart ports.
    host: true,
  },
  build: {
    outDir: "dist",
    rollupOptions: {
      input: {
        main: resolve(import.meta.dirname, "index.html"),
        mapViewer: resolve(import.meta.dirname, "map-viewer.html"),
        sceneViewer: resolve(import.meta.dirname, "scene-viewer.html"),
        mobileInspector: resolve(import.meta.dirname, "mobile-inspector.html"),
        portalLab: resolve(import.meta.dirname, "portal-lab.html"),
      },
    },
  },
});
