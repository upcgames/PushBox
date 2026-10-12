// Explicit exports of original routines. This is the browser entry boundary,
// not replacement gameplay or a copied version of main's initialization.
import PushBoxData from '../../pushbox_modules/maps_json/PushBox.json';
export { main } from '../generated/main.js';
export { MenuPrincipal, InterfazInstructions } from '../generated/interfaces.js';
export { desvanecimiento } from '../generated/world_objects.js';

export function createMenuContext() {
  const matrix = PushBoxData.matrix || PushBoxData;
  return { matrix: matrix.map(row => row.slice()), level: new Ref(0) };
}
