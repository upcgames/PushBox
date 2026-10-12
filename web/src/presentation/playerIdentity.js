// Matches BuscarLetra's letters/digits and accented CP850 glyphs.
const SUPPORTED = /^[a-zA-Z0-9ñÑáéíóúÁÉÍÓÚ]$/u;
export function parsePlayerNames(value) {
  return String(value).normalize('NFC').split(/\s+/u)
    .map(part => [...part].filter(character => SUPPORTED.test(character)).join('').slice(0, 8))
    .filter(Boolean).slice(0, 2);
}

// Original BuscarLetra expects signed CP850 values for these accented glyphs.
const ORIGINAL_CHARACTERS = { á: -96, é: -126, í: -95, ó: -94, ú: -93, ñ: -92, Ñ: -91,
  Á: -75, É: -112, Í: -42, Ó: -32, Ú: -23 };
export function encodePlayerName(name) { return [...name].map(character => ORIGINAL_CHARACTERS[character] ?? character); }
export function writePlayerIdentity(counts, names) {
  const parsed = parsePlayerNames(names.join(' '));
  if (!parsed.length) return;
  counts[8][0] = String(parsed.length);
  counts[8][1] = parsed[0].length;
  counts[8][2] = parsed[1]?.length || 0;
  for (let index = 0; index < 2; index++) {
    counts[6 + index].fill(undefined);
    [...(parsed[index] || '')].forEach((character, position) => {
      counts[6 + index][position] = ORIGINAL_CHARACTERS[character] ?? character;
    });
  }
}

export function createPlayerProfile({ storage, key = 'pushboxPlayerNames' } = {}) {
  if (storage === undefined) { try { storage = window.localStorage; } catch { storage = null; } }
  let names = [];
  try { const saved = JSON.parse(storage?.getItem(key) || '[]'); if (Array.isArray(saved)) names = parsePlayerNames(saved.join(' ')); } catch {}
  return {
    getNames: () => [...names],
    save(value) { names = parsePlayerNames(value.join(' ')); try { storage?.setItem(key, JSON.stringify(names)); } catch {} },
  };
}
