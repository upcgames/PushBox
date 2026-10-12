// Named launcher entry points compose original routines. They do not simulate
// key presses, parse console text, or recreate gameplay initialization.
export async function startRuntime(runtime, { entry = 'main', configure, runAnim }) {
  if (entry === 'main') return runtime.main();
  let nextLevel;
  if (entry === 'menu') {
    const context = runtime.createMenuContext();
    await runtime.MenuPrincipal(context.level, context.matrix);
    nextLevel = context.level.v;
  } else if (entry === 'instructions') {
    await runtime.InterfazInstructions();
    // The original menu owns this exit after its instruction call.
    await runAnim(runtime.desvanecimiento, 9);
    nextLevel = 1;
  } else throw new Error(`Unknown runtime entry: ${entry}`);
  if (nextLevel === 9) return;
  configure({ skipIntro: true, startLevel: nextLevel });
  return runtime.main();
}
