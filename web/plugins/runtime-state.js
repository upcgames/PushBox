// Web-only adapter. Runtime observation is independent of the C++ pipeline.
const MODULES = /\/(main|game_logic|interfaces|gui|world_objects|world_logic)\.js$/;
const LOOP_TYPES = new Set(['WhileStatement', 'DoWhileStatement', 'ForStatement', 'ForOfStatement', 'ForInStatement']);

function walk(node, visit, ancestors = []) {
  if (!node || typeof node !== 'object') return;
  if (visit(node, ancestors) === false) return;
  for (const value of Object.values(node)) {
    if (Array.isArray(value)) value.forEach(child => walk(child, visit, [...ancestors, node]));
    else if (value && typeof value === 'object') walk(value, visit, [...ancestors, node]);
  }
}

// Canonical markers delimit intent without depending on copy or input layout.
function markedSection(source, ast, fn, name) {
  const literals = [];
  walk(ast, node => { if (node.type === 'Literal' || node.type === 'TemplateLiteral') literals.push(node); });
  const markers = [...source.matchAll(/^\s*\/\/ @web:(begin|end) ([a-z][a-z0-9-]*)[ \t]*$/gm)]
    .filter(match => match[2] === name && !literals.some(node => match.index >= node.start && match.index < node.end));
  const [begin, end] = markers;
  if (markers.length !== 2 || begin[1] !== 'begin' || end[1] !== 'end' ||
      begin.index <= fn.body.start || end.index >= fn.body.end) {
    throw new Error(`Runtime adapter: invalid or missing @web section ${name}`);
  }
  const start = begin.index + begin[0].length, finish = end.index;
  let block;
  walk(fn.body, node => {
    if (node.type === 'BlockStatement' && node.start < start && node.end > finish) block = node;
  });
  if (!block || block.body.some(node =>
    (node.start < start && node.end > start) || (node.start < finish && node.end > finish))) {
    throw new Error(`Runtime adapter: @web section ${name} must delimit complete statements in one block`);
  }
  return { start, end: finish };
}

// Extract actual single-character choices from scanf's validation loop, rather
// than treating every one-character text input as a UI-specific numeric choice.
function textChoices(call, ancestors) {
  const target = call.arguments[1];
  const loop = ancestors.findLast(node => node.type === 'DoWhileStatement');
  if (target?.type !== 'Identifier' || !loop) return null;
  const choices = [];
  function validation(node) {
    if (node.type === 'LogicalExpression' && node.operator === '&&') {
      return validation(node.left) && validation(node.right);
    }
    if (node.type !== 'BinaryExpression' || !['!=', '!=='].includes(node.operator)) return false;
    const member = node.left;
    if (member.type !== 'MemberExpression' || member.object.name !== target.name ||
        member.property.value !== 0 || typeof node.right.value !== 'string') return false;
    choices.push(node.right.value);
    return true;
  }
  return validation(loop.test) ? choices : null;
}

export function runtimeStatePlugin() {
  return {
    name: 'pushbox-runtime-state', enforce: 'pre',
    transform(source, id) {
      const path = id.split('?')[0];
      if (!/\/src\/generated(?:_anim)?\//.test(path) || !MODULES.test(path)) return;
      const ast = this.parse(source), edits = [];
      const insert = (position, text) => edits.push({ start: position, end: position, text });
      const playerHooks = new Set();
      let movementFound = false, blockedPushFound = false, blockedWalkFound = false, bridgeUsed = false, scopeId = 0;

      for (const entry of ast.body) {
        const fn = entry.type === 'ExportNamedDeclaration' && entry.declaration;
        if (fn?.type !== 'FunctionDeclaration') continue;
        const name = fn.id.name;
        if (name === 'CuadroDeVidas') {
          insert(fn.body.start + 1, "\nconst _webHud = Console.enterDrawScope('canonical-hud'); try {\n");
          insert(fn.body.end - 1, '\n} finally { _webHud(); }\n');
          bridgeUsed = true;
          let warningFound = false;
          walk(fn.body, node => {
            if (node.type !== 'IfStatement' || node.test.name !== 'aviso') return;
            if (node.consequent.type !== 'BlockStatement') throw new Error('Runtime adapter: steps warning branch changed');
            insert(node.consequent.start + 1, '\nconst _webWarning = enterStepsWarning(nivel, restantes); try {\n');
            insert(node.consequent.end - 1, '\n} finally { _webWarning(); }\n');
            warningFound = true;
          });
          if (!warningFound) throw new Error('Runtime adapter: steps warning branch missing');
        }
        if (name === 'InterfazCongratulations') {
          // Observe the original prompt section; no copied name-entry logic.
          const section = markedSection(source, ast, fn, 'congratulations-prompts');
          insert(section.start, "\nconst _webPrompts = Console.enterDrawScope('winner-prompts'); try {\n");
          insert(section.end, '\n} finally { _webPrompts(); }\n');
          bridgeUsed = true;
          walk(fn.body, node => {
            if (node.type !== 'CallExpression' || node.callee.name !== 'Escribir' ||
                node.start < section.start || node.end > section.end) return;
            const text = source.slice(node.arguments[0].start, node.arguments[0].end);
            insert(node.start, "presentPrompt('InterfazCongratulations', () => ");
            insert(node.end, `, () => Console.Write(${text}))`);
          });
        }
        if (name === 'InterfazInstructions') {
          bridgeUsed = true;
          walk(fn.body, node => {
            if (/Function/.test(node.type || '')) return false;
            if (node.type !== 'CallExpression') return;
            const callee = node.callee.name;
            if (!['Escribir', 'Sleep', 'runAnim'].includes(callee)) return;
            let immediate;
            if (callee === 'Escribir') {
              immediate = `Console.Write(${source.slice(node.arguments[0].start, node.arguments[0].end)})`;
            } else if (callee === 'Sleep') immediate = 'undefined';
            else immediate = `drawImmediately(${node.arguments.map(arg => source.slice(arg.start, arg.end)).join(', ')})`;
            insert(node.start, "presentScene('InterfazInstructions', () => ");
            insert(node.end, `, () => ${immediate})`);
          });
        }
        if (name === 'ControlDeNiveles') {
          if (!fn.params.some(parameter => parameter.name === 'Cantidades')) throw new Error('Runtime adapter: identity argument changed');
          bridgeUsed = true; insert(fn.body.start + 1, '\nbindPlayerIdentity(Cantidades);\n');
        }
        if (name === 'PintarMovil') {
          const parameters = fn.params.map(parameter => parameter.name || parameter.left?.name);
          if (parameters.join(',') !== 'nivel,x,y,cf,cl') throw new Error('Runtime adapter: player drawing arguments changed');
          playerHooks.add(name);
          bridgeUsed = true;
          insert(fn.body.start + 1, "\nconst _webDraw = Console.enterDrawScope('player'); try {\n");
          insert(fn.body.end - 1, '\n} finally { _webDraw(); reportPlayerDraw(nivel, x, y, cf, cl); }\n');
        } else if (['PintarMuerte', 'Teletransporte', 'Regresar', 'TeclasOcultas', 'Endurecimiento'].includes(name)) {
          playerHooks.add(name);
          bridgeUsed = true;
          insert(fn.body.start + 1, `\nconst _webAnimation = enterPlayerAnimation('${name}'); try {\n`);
          insert(fn.body.end - 1, '\n} finally { _webAnimation(); }\n');
        }
        // Keep terrain drawn by the original routines beneath a traveling player.
        // Actors and animation effects never replace this presentation backdrop.
        if (name === 'ColocarEscenario' || ['PBorrar', 'PintarHueco', 'PintarPuente', 'PintarPortal', 'DestruirPuente'].includes(name)) {
          const scope = name === 'ColocarEscenario' ? 'board' : 'terrain';
          insert(fn.body.start + 1, `\nconst _webTerrain = Console.enterDrawScope('${scope}'); try {\n`);
          insert(fn.body.end - 1, '\n} finally { _webTerrain(); }\n');
        }
        if (name === 'ControlDeMovimiento' || name === 'InterfazPausa') {
          if (!fn.params.some(parameter => parameter.name === 'sonido')) throw new Error('Runtime adapter: sound reference changed');
          bridgeUsed = true;
          insert(fn.body.start + 1, '\nbindSound(sonido);\n');
          // F is applied immediately by the platform input adapter. The pause
          // loop may still receive F to repaint its sound label, without retoggling.
          let toggleFound = false;
          walk(fn.body, (node, ancestors) => {
            if (node.type !== 'IfStatement' || !ancestors.some(parent => parent.type === 'SwitchCase' && parent.test?.value === 'F')) return;
            const assignments = [];
            walk(node, child => { if (child.type === 'AssignmentExpression' && child.left.type === 'MemberExpression' && child.left.object.name === 'sonido') assignments.push(child); });
            if (!assignments.length) return;
            edits.push({ start: node.start, end: node.end, text: '/* F already updated shared audio state. */' });
            toggleFound = true; return false;
          });
          if (!toggleFound) throw new Error('Runtime adapter: sound toggle changed');
        }
        if (name === 'ControlDeMovimiento') {
          movementFound = true; bridgeUsed = true;
          const initialization = fn.body.body.find(node => node.type === 'VariableDeclaration' &&
            node.declarations.some(declaration => declaration.id.name === 'posicion'));
          if (!initialization) throw new Error('Runtime adapter: movement initialization changed');
          insert(initialization.end, `
const _webLevel = nivel.v;
const _webStop = observeGame(() => boardSnapshot(_webLevel, { x, y }, cantmovs, vidas.v, sonido.v,
  { Cajas, Paredes, Vacios, Huecos, Cantidades },
  { x: xportal, y: yportal, active: PortalVisible(_webLevel, Cajas, Huecos, Cantidades) }, nivel.v, posicion,
  { remaining: limiteMovimientos - cantmovs, nextCost: costoRegreso,
    charge: posicion > 1 ? CostoDeRegreso(limiteMovimientos - cantmovs, costoRegreso) : 0,
    affordableDepth: RegresosDisponibles(limiteMovimientos - cantmovs, costoRegreso, posicion) }));
const _webLeave = enterScreen('gameplay');
try {`);
          insert(fn.body.end - 1, '\n} finally { _webStop(); _webLeave(); }\n');
          walk(fn.body, node => {
            if (/Function/.test(node.type || '')) return false;
            if (node.type === 'IfStatement' && node.test.type === 'UnaryExpression' &&
                node.test.operator === '!' && node.test.argument.type === 'CallExpression' &&
                node.test.argument.callee.name === 'CajaLugarPermitido') {
              if (node.consequent.type !== 'BlockStatement') {
                throw new Error('Runtime adapter: rejected-push branch changed');
              }
              insert(node.consequent.start + 1, '\nreportBlockedPush(mov, caja);\n');
              blockedPushFound = true;
            }
            if (node.type === 'IfStatement' && node.test.type === 'CallExpression' &&
                node.test.callee.name === 'MovilDentroDeMapa') {
              if (node.alternate?.type !== 'BlockStatement') throw new Error('Runtime adapter: rejected-walk branch changed');
              insert(node.alternate.start + 1, '\nreportBlockedMove(mov);\n');
              blockedWalkFound = true;
            }
            if (node.type === 'IfStatement' && node.test.type === 'BinaryExpression' &&
                node.test.operator === '<' && node.test.left.name === 'caja' && node.test.right.value === 10) {
              if (node.alternate?.type !== 'BlockStatement') throw new Error('Runtime adapter: hardened-caja rejection changed');
              insert(node.alternate.start + 1, '\nreportBlockedPush(mov, caja);\n');
            }
            if (node.type === 'AwaitExpression') {
              insert(node.argument.start, 'observeAwait('); insert(node.argument.end, ')');
            }
          });
        } else if (/^(Interfaz|MenuPrincipal$|Lore$|main$)/.test(name)) {
          bridgeUsed = true;
          // Structured facts from original scene arguments, independent of UI.
          const hasLevel = fn.params.some(parameter => parameter.type === 'Identifier' && parameter.name === 'nivel');
          const context = name === 'InterfazPausa' ? ', { exit: () => ({ option: opcion.v }) }'
            : hasLevel ? ', { level: nivel }' : '';
          insert(fn.body.start + 1, `\nconst _webLeave = enterScreen('${name}'${context}); try {\n`);
          insert(fn.body.end - 1, '\n} finally { _webLeave(); }\n');
        }

        const inputLoops = new Set();
        walk(fn.body, (node, ancestors) => {
          if (/Function/.test(node.type || '')) return false;
          if (node.type !== 'AwaitExpression' || node.argument.type !== 'CallExpression') return;
          const call = node.argument, callee = call.callee.name;
          if (callee === '_getch') {
            if (name === 'InterfazPausa') {
              insert(call.start, 'readPauseKey(() => ');
              insert(call.end, ', opcion)');
            }
            const loop = ancestors.findLast(parent => LOOP_TYPES.has(parent.type));
            if (!loop) throw new Error(`Runtime adapter: unscoped key input in ${name}`);
            inputLoops.add(loop);
          } else if (callee === 'scanf' || callee === 'esperartecla') {
            bridgeUsed = true;
            let request;
            if (callee === 'scanf') {
              const format = call.arguments[0]?.value;
              const match = typeof format === 'string' && format.match(/^%(\d+)s$/);
              if (!match) throw new Error(`Runtime adapter: unsupported text input in ${name}`);
              request = JSON.stringify({ kind: 'text', consumer: name,
                maxLength: Number(match[1]), choices: textChoices(call, ancestors) });
            } else {
              const key = call.arguments[0];
              request = `{ kind: 'confirmation', consumer: '${name}', key: ${key ? source.slice(key.start, key.end) : "'E'"} }`;
            }
            insert(call.start, `withInput(${request}, () => `);
            insert(call.end, callee === 'scanf' ? `, ${source.slice(call.arguments[1].start, call.arguments[1].end)})` : ')');
          }
        });
        for (const loop of inputLoops) {
          bridgeUsed = true;
          const token = `_webInput${scopeId++}`;
          insert(loop.start, `{ const ${token} = enterInput({ kind: 'key', consumer: '${name}' }); try {\n`);
          insert(loop.end, `\n} finally { ${token}(); } }`);
        }
      }
      if (path.endsWith('/game_logic.js') && !movementFound) {
        throw new Error('Runtime adapter: ControlDeMovimiento is missing');
      }
      if (movementFound && !blockedPushFound) {
        throw new Error('Runtime adapter: rejected-push branch is missing');
      }
      if (movementFound && !blockedWalkFound) throw new Error('Runtime adapter: rejected-walk branch is missing');
      const requiredPlayerHooks = path.endsWith('/world_objects.js')
        ? ['PintarMovil', 'PintarMuerte', 'Teletransporte', 'TeclasOcultas', 'Endurecimiento']
        : path.endsWith('/world_logic.js') ? ['Regresar'] : [];
      for (const name of requiredPlayerHooks) {
        if (!playerHooks.has(name)) throw new Error(`Runtime adapter: player routine ${name} is missing`);
      }
      if (!edits.length) return;
      // Apply source insertions from right to left to preserve AST offsets.
      for (const edit of edits.sort((a, b) => b.start - a.start || b.end - a.end)) {
        source = source.slice(0, edit.start) + edit.text + source.slice(edit.end);
      }
      const imports = bridgeUsed ? "import { observeGame, boardSnapshot, enterScreen, observeAwait, enterInput, withInput, readPauseKey, presentPrompt, presentScene, drawImmediately, reportBlockedPush, reportBlockedMove, bindSound, reportPlayerDraw, enterPlayerAnimation, enterStepsWarning, bindPlayerIdentity } from '../state/runtimeBridge.js';\n" : '';
      const undoImport = movementFound ? "import { RegresosDisponibles } from './world_logic.js';\n" : '';
      return { code: imports + undoImport + source, map: null };
    },
  };
}
