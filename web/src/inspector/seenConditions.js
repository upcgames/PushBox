import { DESTINATIONS } from '../presentation/seenDestinations.js';
import { REWIND_UNLOCKED, REWIND_RECOVERED } from '../presentation/rewindDiscovery.js';

const CONDITIONS = { warning: 'Warning completed', carita: 'Carita unlocked', caritaUsed: 'Carita used',
  [REWIND_UNLOCKED]: 'Rewind unlocked', [REWIND_RECOVERED]: 'Rewind used successfully' };
const LABELS = { ...Object.fromEntries(DESTINATIONS.map(destination => [destination.flag, destination.label])), ...CONDITIONS };

export function mountSeenConditions(root, sources) {
  function render() {
    const names = [...new Set([...Object.keys(CONDITIONS), ...DESTINATIONS.map(destination => destination.flag),
      ...sources.flatMap(source => Object.keys(source.progress.getSnapshot()))])];
    const table = document.createElement('table');
    const head = table.createTHead().insertRow();
    const corner = document.createElement('th'); corner.scope = 'col'; corner.textContent = 'Condition'; head.append(corner);
    for (const source of sources) {
      const cell = document.createElement('th'); cell.scope = 'col';
      const label = document.createElement('span'); label.textContent = source.label; cell.append(label);
      const button = document.createElement('button'); button.type = 'button'; button.textContent = 'Clear all';
      button.disabled = !Object.values(source.progress.getSnapshot()).some(value => value === true);
      button.setAttribute('aria-label', `Clear all seen conditions · ${source.label}`);
      button.addEventListener('click', () => source.clear()); cell.append(button); head.append(cell);
    }
    const body = table.createTBody();
    for (const name of names) {
      const row = body.insertRow();
      const label = document.createElement('th'); label.scope = 'row'; label.textContent = LABELS[name] || name; row.append(label);
      for (const source of sources) {
        const cell = row.insertCell(), active = source.progress.has(name);
        const status = document.createElement('span'); status.textContent = active ? 'Seen' : 'Not seen';
        status.className = active ? 'seen-active' : ''; cell.append(status);
        if (active) {
          const button = document.createElement('button'); button.type = 'button'; button.textContent = 'Clear';
          button.setAttribute('aria-label', `Clear ${LABELS[name] || name} · ${source.label}`);
          button.addEventListener('click', () => source.clear(name === 'carita' ? ['carita', 'caritaUsed']
            : name === REWIND_UNLOCKED ? [REWIND_UNLOCKED, REWIND_RECOVERED] : name));
          cell.append(button);
        }
      }
    }
    root.replaceChildren(table);
  }
  const stops = sources.map(source => source.progress.subscribe(render));
  render();
  return () => { stops.forEach(stop => stop()); root.replaceChildren(); };
}
