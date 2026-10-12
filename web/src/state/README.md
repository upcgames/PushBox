# Shared web state

Import `GameState` from `./gameState.js` (or inspect `window.GameState` in the
browser). Snapshots are deeply immutable and detached from runtime arrays.
Consumers cannot publish state through this API. `sendInput(key)` sends commands
through the existing keyboard queue; received input is distinct from consumed
input and does not imply a successful move.

```js
import { GameState } from './state/gameState.js';
import { selectControlMode } from './shell/controlPolicy.js';

const stopBoard = GameState.select(state => state.game, game => {
  if (game) renderBoardHints(game.board, game.portal);
});
const stopControls = GameState.select(selectControlMode, mountControls);
const stopLives = GameState.select(state => state.game?.lives, renderLives);
const stopText = GameState.select(state => state.console, renderNativeTranscript);
const stopInput = GameState.on('input:consumed', ({ key, request }) => {
  // Observe input; gameplay still decides whether it changes the board.
});

GameState.sendInput('d');
// Call each stop function when its consumer unmounts.
```

`getSnapshot()` returns the current state. `subscribe(fn)` immediately delivers
it, then delivers `(next, previous, reason)` on each publication. `select` also
replays immediately, and uses `Object.is` to suppress unchanged selections;
provide a third equality argument for selectors constructing new objects.
`on(type, fn)` listens to future events. `on('*', fn)` receives envelopes with
`sequence`, `type`, `payload`, and `version`. Consumer exceptions are isolated.
There is no unbounded event history.

`pushBlocked` fires once when the runtime rejects a caja push, even with sound
disabled. Its payload contains `level`, `box`, unit `direction`, and `obstacle`
with `{ x, y, kind }` (`wall` or `box`). It does not fire for walking into a wall
or trying to move a hardened level 5 block. Visual reactions belong to consumers.

## Runtime facts and presentation policy

The runtime exposes **input requests**, not control layouts. Each request has a
`kind` (`key`, `confirmation`, or `text`) and a `consumer` (the canonical function
asking for input). Confirmation requests include their actual `key`; text
requests include `maxLength` from scanf's format and `choices` when the adjacent
validation loop explicitly requires particular single-character values.

`web/src/shell/controlPolicy.js` is the separate, explicit web presentation
policy: movement keys use the D-pad, menu keys use navigation controls,
congratulations keys use name/exit actions, confirmations use Continue, text
uses QWERTY, and the validated choices 1/2 use the existing choice buttons.
Unknown key contexts produce no controls. New game flows may need a policy
entry; the store does not pretend to infer UI intent automatically.

Requests are scoped to the actual input operation or interactive key loop. They
clear on completion, early return, break, or exception. When no request is active,
controls derive `none`. During nested screens, parent requests are suspended:
pause temporarily hides gameplay input, and exiting pause restores it. Key loops
retain their request between reads so held D-pad interactions remain stable.
Prompt typing and transitions outside those loops have no active request.

## Snapshot

| Field | Contents |
| --- | --- |
| `version` | Monotonic publication counter |
| `inputRequest` | Active request, or null; no UI-specific `inputMode` is stored |
| `game` | Null outside an active movement session; retained while paused |
| `game.level`, `nextLevel` | Board's level and runtime's current level (may differ during exit) |
| `game.player` | Current `{ x, y }` |
| `game.steps`, `lives`, `sound`, `undoAvailable` | Actual movement counter, lives, compatibility audio flag derived from shared mute, available undo |
| `game.board` | `boxes` with `index` and `onTarget`; `targets` with `covered`; `gaps`; `walls` |
| `game.portal` | `{ x, y, active }`, using canonical `PortalVisible`, including level 5 |
| `game.grid` | Coordinate grid and object dimensions |
| `screen` | Current `{ id, level? }`, or null; level comes from the original scene argument and nested screens restore their parent |
| `input` | Last `{ key, stage, request }`; stages: received, waiting, consumed |
| `audio.muted` | Single session mute state; canonical `game.sound` reads its inverse |
| `console` | `cols`, `rows`, `tileSize`, current `lines`, and `cells` with character and foreground/background colors |

Coordinates use the original **80 × 63 console cells**, not logical tile
indices. Objects occupy **2 × 2 cells**; multiply x/y by **14** for native canvas
pixels. Box indices are active array positions, **not persistent IDs**: bridge
creation removes a box and shifts the array. Only entries up to canonical active
counts are exposed. Steps include the canonical undo penalty.

Screen IDs are `launcher`, `main`, `gameplay`, and canonical function names such
as `Lore`, `InterfazPausa`, `InterfazInstructions`, or `MenuPrincipal`. Combine
screen context and input requests to choose native UI. The console transcript
retains actual visible glyphs, spaces, overwrites and colors, coalesced once per
animation frame. It includes decorative art and does **not** interpret semantic
prompts or turn bitmap lettering into text. Native UI can map known contexts to
its own layout and use readable transcript rows; richer semantic metadata can
be added at the same web integration boundary as needed.

## Integration boundary

`web/plugins/runtime-state.js` instruments served/bundled modules using Vite's
AST parser. It captures local gameplay state after movement initialization,
refreshes at input/asynchronous boundaries, and releases the reader on every
exit. Screen functions and input requests use balanced enter/leave scopes.
Input requests come from **actual key loops, esperartecla calls, and scanf
calls/validation**, independently of the old annotations.

The extractor strips all source comments. The transpiler only applies extracted
asset annotations; it does not emit web-state hooks or imports. Generated modules
contain canonical game logic, and the web adapter attaches observation when they
are served or bundled. There is no annotation migration shim or legacy emitter.

The adapter runs in development and production. Directly loading generated files
without Vite is unsupported for this state API. Incompatible movement/input
shapes fail transformation rather than silently dropping observation. Existing
scene-viewer generated modules are handled at the same integration boundary.

Input and console observation live in the web console shim. Only the main game
console has a transcript observer; gallery canvases do not publish their drawing
into that transcript. All mobile controllers share `sendInput` and the shared
store, with Svelte unmount cleanup.

Publication reasons include `gameStarted`, `gameChanged`, `gameEnded`,
`gameExited`, `screenChanged`, `inputRequestChanged`, `inputChanged`,
`audioChanged`, and `consoleChanged`. Input also emits `input:received`,
`input:waiting`, and `input:consumed`. `runtimeError` reports main-runtime
failures. Derive QOL events such as covered targets or portal activation from
previous/next snapshots instead of assuming an input succeeded.

Run `npm run test:web` from `web/` for store contracts, console/input integration,
and tests against fresh generated browser code. Regenerate artifacts through
the existing host pipeline before running adapter integration tests.


Audio ownership: the shared store's `audio.muted` is authoritative. The main
page and inspector use the same one-channel playback implementation. The web
adapter binds canonical `sonido` references to shared mute state; it does not
keep a separate gameplay sound toggle. F changes shared mute immediately,
including during animation, and is not buffered as a gameplay command. During
text input, F is a literal character. Pause may receive F to redraw its sound
label, but its old toggle is suppressed. UI mute controls update the same state
directly, without dispatching F. Changes also update retained `game.sound`.

Scene metadata: the web observer captures original `nivel` arguments for scene
functions such as Lore and MenuPrincipal. `screen.level` is detached scalar data,
not a mutable Ref or a level inferred from console text. Mobile lore uses this
metadata before the original scene has painted its heading.

Bobby presentation observes `playerDrawing` (original `PintarMovil` arguments) and
`playerAnimation` (named original routine scopes). Death and teleport retain
canonical ownership until a fresh player drawing; undo covers all of `Regresar`,
including board restoration. `setTrollActive` controls only the mobile troll
presentation and is cleared on controller disposal/game exit. The console keeps
canonical tagged cells while the mobile layer hides normal player glyphs; its
transcript and cursor remain canonical. Desktop does not enable this layer.

The console also retains terrain from original board/floor/target/portal/bridge
drawing scopes. Hidden player cells display that terrain while Bobby travels;
actor writes and animation effects do not overwrite the terrain cache. Canonical
player backgrounds remain in the original cells for animation handoff.

`movementBlocked` reports only canonical rejected-walk/push branches, including
level-5 hardened cajas. It carries the player, cardinal direction and structured
obstacle when available. Mobile Bobby uses it for contained tremble; mobile board
feedback uses actual wall obstacles for ripple. The existing `pushBlocked` event
remains available for desktop push-wall feedback. Neither event depends on audio.

`seenProgress.js` persists encountered features in `pushboxSeen`. Carita is earned
from three canonical `onTarget` cajas during visible level-4 mobile gameplay.
`trollReward` exposes unlocked/hinted presentation state; first use marks
`caritaUsed` so the hint does not return on refresh. Seeing level-4 lore does not
earn the reward. Inspector panels use independent in-memory progress across
session resets; they do not modify production persistence.

Mobile opening stores `warning` seen only when completed warning advances to
native names. The shared player profile stores Unicode display names separately
from seen flags. `playerNames` feeds an explicit adapter hook at original
ControlDeNiveles, after original main initializes Cantidades; supported accented
characters map to original signed CP850 glyph identifiers. Empty identity leaves
the original defaults intact, including desktop. Mobile opening composition uses
existing skip-intro settings; original main retains gameplay initialization.
