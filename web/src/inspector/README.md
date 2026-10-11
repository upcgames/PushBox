# Mobile inspector

Open `/mobile-inspector.html` on the normal dev server. The original game page
and the parked Phaser level-one experiment remain separate.

Three previews use 360 × 800, 393 × 852, and 430 × 932 CSS-pixel screens.
The simulated status bar uses 24px; browser top and bottom bars default to
56px and 48px and are adjustable. These are approximations, not claims about
specific phones or Chrome versions. The web viewport subtracts those bars.
Preview scale changes the on-page size, not the underlying CSS viewport size.

Each preview mounts the original console renderer, hints, and existing Svelte
controls directly in the document. There are no iframes. This first version
zooms gameplay to fixed bounds derived from reachable map tiles, plus a one-cell
margin. Those bounds set scale and center; console and hints can overflow them
to fill the surrounding game viewport. Only the outer console frame clips the
layers, keeping them clear of the controls. The original bottom stats
bar falls outside it. Pause, lore and other scenes retain full-console framing.
The same presentation module is used on the original mobile page. Semantic
mobile text presentation and a replacement stats HUD are future work.

The inspector's Crop framing selector compares Reachable area (the default) and Full console
(no crop). It applies immediately to all previews, independently of input linking,
and survives session resets without changing gameplay state. The original mobile
page also uses Reachable area for mobile gameplay.

Reachable-area framing flood-fills nonzero static-map tiles from the initial
player position using two-cell cardinal moves and canonical walls as blockers.
At level entry, gaps with a cardinally adjacent box are treated as potentially
paved, allowing the flood to continue through them. Other adjacent gaps are
included as danger boundaries but stop the flood. This is a camera heuristic,
not a simulation of legal pushes or box consumption. The resulting bounds,
plus a one-cell margin, stay fixed for the run, including after bridge creation.
All five levels use the same algorithm; there are no per-level rectangles.

Quick level in the toolbar resets and starts all previews at the chosen level in
one action, independently of input linking. It preserves crop framing and each
preview's skip-lore setting. Selecting the same level again restarts that level.

Inputs are linked initially. Click a preview to select keyboard focus. With
Link inputs enabled, keyboard and controller keys fan out once to all running
sessions. Start-point and skip-lore changes also propagate while linked; when
unlinked, each preview keeps its own settings. These settings apply on the next
start, without interrupting running games. Clicking Start game starts all previews
while linked, or just that preview while unlinked. Already running games are left
running. Linking does not copy state or reset games. Reset all remains an explicit
control; each preview also has its own start point and reset.
The comparison label reports differing screen/input/game snapshots. Async
scenes can reach input at different times, so shared keys are not a lockstep
simulation. Audio is muted initially and controlled per preview.

## Runtime boundary

`runtime/createGameSession.js` owns the console surface, command queue,
immutable state store, runtime bridge, audio channel, animation clock and
abort lifecycle for one game. It installs no window keyboard listener.
`sessionShims.js` implements the existing platform functions with those owned
dependencies. `sessionAnimation.js` preserves the original generator delay and
per-cell paint budget using an abortable clock.

`plugins/session-runtime.js` bundles the generated runtime into an ordinary
JavaScript factory, using the already installed Vite+ bundler. It replaces the
console, bridge, animation and ambient shim bindings with session dependencies
and reuses the existing runtime-state AST instrumentation. Generated gameplay,
matrices, glyph rendering and scene choreography are not hand-edited. No eval,
runtime recompilation, alternate rules engine, or hidden canonical game is used.
The factory is built during Vite serving/building. Each invocation owns its
runtime module locals and assets; all original levels and scenes remain usable.

`consoleSurface.js` contains the unchanged console drawing implementation,
without the original window shim installation. The original page still imports
`virtual_console.js` for its compatibility setup. The runtime bridge and state
store now also support independent instances. Controller services come from
Svelte mount context; the original page retains its default services.

Reset aborts pending input/timers/animation frames, stops audio and unsubscribes
controls/hints/transcript observers before creating another session. HMR also
disposes the previews. `window.PushBoxInspector.getSessions()` exposes the
current session objects for inspection; each provides `state`, `console`,
`audio`, `sendInput`, `start`, `loadAssets`, and `dispose`.

`pnpm run test:web` includes tests that run three actual compiled runtimes with
test canvas/audio/clock backends. They exercise isolation, pause, command
fan-out, unlinking, disposal, and replacement alongside legacy regression tests.
