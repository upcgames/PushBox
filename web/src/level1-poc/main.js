import { levelFromTiled } from './level.js';
import { createSession } from './session.js';
import { mountRenderer } from './renderer.js';
import './page.css';

const status = document.getElementById('status');
async function start() {
  const response = await fetch(`${import.meta.env.BASE_URL}level1-poc/level1.tmj`);
  if (!response.ok) throw new Error(`Level data failed to load (${response.status}); run make generate`);
  const session = createSession(levelFromTiled(await response.json()));
  const renderer = mountRenderer(document.getElementById('board'), session);
  const undo = document.getElementById('undo');
  const pause = document.getElementById('pause');
  const retry = document.getElementById('retry');
  const events = [], eventList = document.getElementById('events');
  const buttons = [...document.querySelectorAll('[data-direction]')];
  const stop = session.subscribe(state => {
    document.getElementById('moves').textContent = `${state.steps} / ${state.moveLimit}`;
    document.getElementById('lives').textContent = String(state.lives);
    document.getElementById('targets').textContent = `${state.targets.filter(target => target.covered).length} / ${state.targets.length}`;
    status.textContent = ({ playing: state.portal.active ? 'Portal open. Return to your starting point.' : 'Push all four boxes onto the targets.',
      paused: 'Paused', completed: 'Level 1 complete', lifeLost: 'Move limit reached. Try again with your remaining lives.',
      gameOver: 'No lives left. Restart to play again.' })[state.phase];
    undo.disabled = state.phase !== 'playing' || !state.undoAvailable;
    undo.textContent = `Undo (${state.undoAvailable})`;
    pause.disabled = !['playing', 'paused'].includes(state.phase);
    pause.textContent = state.phase === 'paused' ? 'Resume' : 'Pause';
    retry.hidden = state.phase !== 'lifeLost';
    buttons.forEach(button => { button.disabled = state.phase !== 'playing'; });
    document.getElementById('snapshot').textContent = JSON.stringify({ level: state.level, phase: state.phase,
      player: state.player, boxes: state.boxes, portal: state.portal, steps: state.steps,
      lives: state.lives, undoAvailable: state.undoAvailable }, null, 2);
  });
  const stopEvents = session.onEvent(event => {
    events.unshift(JSON.stringify(event)); events.length = Math.min(events.length, 12);
    eventList.textContent = events.join('\n');
  });
  const listeners = [];
  function listen(target, type, callback) {
    target.addEventListener(type, callback);
    listeners.push(() => target.removeEventListener(type, callback));
  }
  buttons.forEach(button => listen(button, 'click', () => session.command({ type: 'move', direction: button.dataset.direction })));
  listen(undo, 'click', () => session.command({ type: 'undo' }));
  listen(pause, 'click', () => session.command({ type: 'pause' }));
  listen(retry, 'click', () => session.command({ type: 'retry' }));
  listen(document.getElementById('restart'), 'click', () => session.command({ type: 'restart' }));
  listen(document.getElementById('boardOnly'), 'change', event => renderer.setBoardOnly(event.target.checked));
  listen(document.getElementById('motion'), 'change', event => renderer.setMotion(event.target.checked));
  const keys = { w: 'up', ArrowUp: 'up', s: 'down', ArrowDown: 'down', a: 'left', ArrowLeft: 'left', d: 'right', ArrowRight: 'right' };
  listen(window, 'keydown', event => {
    if (event.ctrlKey || event.metaKey || event.altKey || event.target.matches('input, select, textarea, [contenteditable]')) return;
    const key = event.key.length === 1 ? event.key.toLowerCase() : event.key;
    const command = keys[key] ? { type: 'move', direction: keys[key] }
      : key === 'r' ? { type: 'undo' } : key === 'p' ? { type: 'pause' } : null;
    if (command) { event.preventDefault(); if (key !== 'p' || !event.repeat) session.command(command); }
  });
  // Developer entry point; session commands do not depend on this window property.
  window.level1POC = session;
  const dispose = () => {
    listeners.forEach(remove => remove()); stop(); stopEvents(); renderer.dispose(); session.dispose();
    delete window.level1POC;
  };
  if (import.meta.hot) import.meta.hot.dispose(dispose);
}
start().catch(error => { status.textContent = error.message; console.error(error); });
