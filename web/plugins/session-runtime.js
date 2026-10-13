import { build } from 'vite-plus';
import { resolve } from 'node:path';
import { runtimeStatePlugin } from './runtime-state.js';

const BRIDGE = ['observeGame', 'boardSnapshot', 'enterScreen', 'observeAwait', 'enterInput', 'withInput', 'readPauseKey', 'presentPrompt', 'presentScene', 'drawImmediately', 'reportBlockedPush', 'reportBlockedMove', 'bindSound', 'reportPlayerDraw', 'enterPlayerAnimation', 'enterStepsWarning', 'bindPlayerIdentity'];
const GLOBALS = ['Ref', 'Random', 'CONSOLE_SCREEN_BUFFER_INFO', 'SetConsoleTextAttribute',
  'GetStdHandle', 'system', 'FlushConsoleInputBuffer', 'fflush', 'STD_OUTPUT_HANDLE',
  'STD_INPUT_HANDLE', 'stdin', 'toupper', 'Convert', '_kbhit', '_getch', 'scanf', 'strlen',
  'Sleep', 'GetConsoleScreenBufferInfo', 'PlaySound', 'TEXT', 'SND_SYNC', 'SND_ASYNC',
  'SND_NODEFAULT', 'SND_MEMORY', 'SND_LOOP', 'SND_NOSTOP'];

// Build an ordinary JavaScript factory, never eval/new Function. Rolldown keeps
// module scopes/circular imports intact; every invocation gets its own runtime.
// Generated files remain untouched. The existing state instrumentation is reused.
export async function compileSessionRuntime(root, parse) {
  const adapter = runtimeStatePlugin();
  const watchFiles = new Set();
  const output = await build({
    configFile: false, root, publicDir: false, logLevel: 'silent',
    build: { write: false, minify: false, emptyOutDir: false,
      lib: { entry: resolve(root, 'src/runtime/originalRuntime.js'), name: 'PushBoxRuntime', formats: ['iife'] },
    },
    plugins: [{
      name: 'pushbox-session-bindings',
      enforce: 'pre',
      resolveId(id) {
        if (id.endsWith('/shims/gameConsole.js')) return '\0session-console';
        if (id.endsWith('/state/runtimeBridge.js')) return '\0session-bridge';
        if (id.endsWith('/animationDriver.js')) return '\0session-animation';
      },
      load(id) {
        if (!id.startsWith('\0')) watchFiles.add(id);
        if (id === '\0session-console') return 'export const Console = __pushboxEnvironment.console; export const ConsoleColor = __pushboxEnvironment.consoleColor;';
        if (id === '\0session-bridge') return BRIDGE.map(name => `export const ${name} = __pushboxEnvironment.bridge.${name};`).join('\n');
        if (id === '\0session-animation') return 'export const runAnim = __pushboxEnvironment.runAnim;';
      },
      transform(source, id) {
        return adapter.transform.call({ parse }, source, id);
      },
    }],
  });
  const result = Array.isArray(output) ? output[0] : output;
  return { watchFiles: [...watchFiles],
    code: `export function createRuntime(__pushboxEnvironment) {\nconst { ${GLOBALS.join(', ')} } = __pushboxEnvironment.shims;\nconst window = __pushboxEnvironment.window;\n${result.output[0].code}\nreturn PushBoxRuntime;\n}\n` };
}

export function sessionRuntimePlugin() {
  let root;
  return {
    name: 'pushbox-session-runtime',
    configResolved(config) { root = config.root; },
    resolveId(id) { if (id === 'virtual:pushbox-session-runtime') return '\0pushbox-session-runtime'; },
    async load(id) {
      if (id !== '\0pushbox-session-runtime') return;
      const result = await compileSessionRuntime(root, source => this.parse(source));
      result.watchFiles.forEach(file => this.addWatchFile(file));
      return result.code;
    },
  };
}
