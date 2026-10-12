// Matches BuscarLetra's letters/digits and accented CP850 glyphs.
const SUPPORTED = /^[a-zA-Z0-9ñÑáéíóúÁÉÍÓÚ]$/u;
export function parsePlayerNames(value) {
  return String(value).normalize('NFC').split(/\s+/u)
    .map(part => [...part].filter(character => SUPPORTED.test(character)).join('').slice(0, 8))
    .filter(Boolean).slice(0, 2);
}
