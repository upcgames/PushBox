# Level 1 proof of concept

Open `/level1-poc.html` using the normal web dev server. This is a separate
implementation; the original game remains available at `/index.html`.

- `session.js` owns level-one rules and immutable state. It has no browser,
  Phaser, generated-runtime, keyboard, or timer dependency. Each `createSession`
  call owns independent player/box state, lives, and undo history.
- `level.js` converts standard Tiled map objects/properties into a session definition.
- `renderer.js` loads the Tiled tile layer in Phaser 3, then draws actors from
  session snapshots. Camera zoom and character bobbing are presentation only.
- `main.js` connects controls and state/event inspection to one session.
- `scripts/export_level1_poc.mjs` converts pipeline `mapa01.json` and level-one
  `collision_data.json` into `public/level1-poc/level1.tmj` and `colors.png`.
  These generated assets are rebuilt by `make generate`. No new Python deps.

Coordinates retain console cells (80 × 60, actor size/movement 2 cells). The
Tiled tile size is 16px. Actor textures approximate the original simple
level-one glyphs/colors; they are not a pixel-exact CP437 recreation. The
decorative ASCII backdrop, audio, lore, teleport, victory, and other scene
animations are outside this POC. Entering an active portal ends in `completed`
at level 1, without progressing or scheduling a presentation sequence.

Canonical rules preserved: four boxes/targets; walls; move limit 150; five
lives; at most five undo entries; undo adds three steps without subtracting the
original move. Blocked commands cost no steps. As in the port, undo doesn't
perform the death check, and portal completion precedes the move-budget check.
On budget loss the POC waits in `lifeLost`; `retry` resets the board and steps
while preserving remaining lives. `restart` starts a fresh five-life session.

Session interface:

```js
const session = createSession(levelFromTiled(map));
const stopState = session.subscribe(snapshot => render(snapshot));
const stopEvents = session.onEvent(event => inspect(event));
session.command({ type: 'move', direction: 'up' });
session.command({ type: 'undo' });
session.command({ type: 'pause' }); // toggle
session.command({ type: 'retry' });
session.command({ type: 'restart' });
stopState(); stopEvents(); session.dispose();
```

Subscriptions immediately replay the snapshot. Events observe committed state;
blocked moves emit an event without a state publication. Commands return
whether they were accepted. Observers cannot synchronously dispatch nested
commands. `window.level1POC` exposes this page's session for dev inspection.

After generating assets, `pnpm run test:web` includes POC coverage. Differential
tests execute the existing generated movement loop with drawing/audio no-ops
and compare player, boxes, steps, and undo depth after each command.
