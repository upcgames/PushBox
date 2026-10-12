// Web-only adapter. Runtime observation is independent of the C++ pipeline.
const MODULES = /\/(main|game_logic|interfaces|gui)\.js$/;
const LOOP_TYPES = new Set(['WhileStatement', 'DoWhileStatement', 'ForStatement', 'ForOfStatement', 'ForInStatement']);

function walk(node, visit, ancestors = []) {
  if (!node || typeof node !== 'object') return;
  if (visit(node, ancestors) === false) return;
  for (const value of Object.values(node)) {
    if (Array.isArray(value)) value.forEach(child => walk(child, visit, [...ancestors, node]));
    else if (value && typeof value === 'object') walk(value, visit, [...ancestors, node]);
  }
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
      let movementFound = false, blockedPushFound = false, bridgeUsed = false, scopeId = 0;

      for (const entry of ast.body) {
        const fn = entry.type === 'ExportNamedDeclaration' && entry.declaration;
        if (fn?.type !== 'FunctionDeclaration') continue;
        const name = fn.id.name;
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
  { x: xportal, y: yportal, active: PortalVisible(_webLevel, Cajas, Huecos, Cantidades) }, nivel.v, posicion));
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
            if (node.type === 'AwaitExpression') {
              insert(node.argument.start, 'observeAwait('); insert(node.argument.end, ')');
            }
          });
        } else if (/^(Interfaz|MenuPrincipal$|Lore$|main$)/.test(name)) {
          bridgeUsed = true;
          insert(fn.body.start + 1, `\nconst _webLeave = enterScreen('${name}'); try {\n`);
          insert(fn.body.end - 1, '\n} finally { _webLeave(); }\n');
        }

        const inputLoops = new Set();
        walk(fn.body, (node, ancestors) => {
          if (/Function/.test(node.type || '')) return false;
          if (node.type !== 'AwaitExpression' || node.argument.type !== 'CallExpression') return;
          const call = node.argument, callee = call.callee.name;
          if (callee === '_getch') {
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
            insert(call.start, `withInput(${request}, () => `); insert(call.end, ')');
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
      if (!edits.length) return;
      // Apply source insertions from right to left to preserve AST offsets.
      for (const edit of edits.sort((a, b) => b.start - a.start || b.end - a.end)) {
        source = source.slice(0, edit.start) + edit.text + source.slice(edit.end);
      }
      const imports = bridgeUsed ? "import { observeGame, boardSnapshot, enterScreen, observeAwait, enterInput, withInput, reportBlockedPush, bindSound } from '../state/runtimeBridge.js';\n" : '';
      return { code: imports + source, map: null };
    },
  };
}
