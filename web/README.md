# PushBox Web

Browser port of **Retro Push Box** (2014 C++ DOS game, ~12k lines in a single `Source Code.cpp`). The port preserves original game logic by transpiling C++ to JavaScript rather than rewriting it.

## What This Is

- Original: DOS console game (80×63 grid, DOS 16-color palette, CP437 extended chars) with hardcoded level matrices, sprites, and animation routines.
- Web: same logic running in the browser on a single canonical canvas (`80 × 63` cells, `14px` per cell) with identical colors/glyphs. Gameplay, animations, and audio are driven by the transpiled code.

## How It Works

```
Retro Push Box/Source Code.cpp
        │
        ▼
pushbox_modules/*.cpp + maps_json/*.json   ← build_pushbox_modules.py (extract + normalize)
        │
        ▼
src/generated/*.js + src/generated_anim/*.js ← transpile_modules.py + ast_transpiler.py
        │
        ▼
VirtualConsole (src/shims/virtual_console.js) + animationDriver.js
        │
        ▼
index.html / scene-viewer.html / map-viewer.html  (Vite 8)
```

- **Single canonical console** — `src/shims/gameConsole.js` exports `gameConsole = new VirtualConsole('gameCanvas', 80, 63, 14)`. Every generated module does `import { Console, ConsoleColor } from '../shims/gameConsole.js'`.
- **VirtualConsole** — emulates the DOS console API (`ir`, `colorfondo`/`colorletra`, `Console.Write`, `Clear`, `paint_cost`). CP437 glyphs and the `Px437_IBM_CGA` font are preloaded via `VirtualConsole.loadAssets()` — callers must `await gameConsole.loadAssets()` before first paint (see `src/game.js`).
- **Animation driver** — `src/animationDriver.js` (`runAnim` + `CELL_PAINT_COST`) drives `async function*` generators produced from C++ functions that used `Sleep`/`yield`. `GIF(matriz, ya, yb, xa, xb, …)` is the blitting primitive.
- **Transpile** — `modules_manifest.txt` assigns functions to modules (`#animation`/`#gallery` tags); `scripts/build_pushbox_modules.py` extracts, `scripts/ast_transpiler.py` + `scripts/transpile_modules.py` (via `scripts/dag.py`) emit the two generated trees and validate with `node --check`.

## Working Directions

- **Prefer not to edit `Source Code.cpp`** — treat it as frozen source of truth. Fixes to logic should go through the transpile layer when possible; only patch the C++ file for canonical data bugs (e.g., matrix dimension fixes) and re-extract.
- **Avoid reading `Source Code.cpp` directly** — it is large and mostly hardcoded matrices. Use the extracted `pushbox_modules/` files and `src/generated/` outputs instead. Use `modules_manifest.txt` to find which module owns a function.
- **Keep generated code as build artifact** — do not hand-edit `src/generated/*.js` or `src/generated_anim/*.js`; edit the transpile toolchain (`scripts/ast_transpiler.py`, `scripts/transpile_modules.py`, `scripts/dag.py`) or the manifest.
- **Naming** — `pushbox_modules/` (extracted C++ modules), `maps_json/` (extracted matrices), `src/generated/` (game runtime), `src/generated_anim/` (gallery isolation, same import as generated). `public/pushbox_modules/` is a `rsync` mirror for Vite's `publicDir`.

## Generate & Build

```bash
# from web/
make generate        # 1) extract modules → pushbox_modules/  2) transpile → src/generated{,_anim}/  3) rsync → public/pushbox_modules/
pnpm run dev         # generate + vite dev server
pnpm run build       # generate + vite build (outputs dist/)
pnpm run generate    # alias for make generate
```

`Makefile` is incremental (`MODULES_STAMP`, `JS_STAMP`/`ANIM_STAMP`, `PUBLIC_MODULES_STAMP`) and CI-safe — `public/pushbox_modules` is rebuilt via rsync so Vite serves JSON assets.

## Test & Lint

The [mobile inspector](src/inspector/README.md) at `mobile-inspector.html`
runs three independent original-runtime sessions, with simulated phone
viewports and optional linked input. It preserves the console rendering and hints.

The separate [level 1 POC](src/level1-poc/README.md) is at
`level1-poc.html`: headless gameplay rules with a Phaser renderer and converted
Tiled assets. It stops at portal completion and excludes scene animations.

The [shared web-state API](src/state/README.md) supports controls and future QOL
consumers (board overlays, lives/steps UI, input events, and console text).
Run `pnpm run test:web` for its web-only tests; it does not run generation.

```bash
make test            # Python transpiler unit tests (ast_transpiler) + eslint src/
.venv/bin/python scripts/test_transpiler.py   # 25 tests, includes int-division flooring
pnpm exec eslint src/ # JS lint (vite-plugin-eslint also runs on build)
```

Python deps must use `.venv` (`python3 -m venv .venv && .venv/bin/pip install tree_sitter` etc. — do not use global pip).

## Sandbox checks

The bridge registry is `../sbx-here/bridge/registry.json`. On the host, prepare
the Python dependencies once:

```sh
# from web/
python3 -m venv .venv
.venv/bin/python -m pip install tree_sitter tree_sitter_cpp
```

The repo-root `package.json` exposes these commands through `vpr` (shorthand
for `vp run`). `web/` is registered in `pnpm-workspace.yaml`; run `vp install`
from the PushBox root to install the task runner and web dependencies for both
macOS and the Linux sandbox. From the host, `vpr dev` in the PushBox root
forwards to `pushbox-web#dev`, which generates assets and starts the web dev
server. You can also target it directly with `vpr pushbox-web#dev`.
From the PushBox root on the host, start `sbx-here bridge`,
then run `sbx-here` in another terminal. Inside the sandbox, from the repo root:

```sh
vpr pipeline  # make generate: extraction, transpilation, validation, assets
vpr test      # make test: transpiler unit tests + ESLint
vpr lint      # ESLint only
```

Each route runs in `web/` on the host and accepts no extra arguments. ESLint is
the static check for this JavaScript repo; no TypeScript check is configured.
Build, serving/dev, and deployment remain owner workflows.

