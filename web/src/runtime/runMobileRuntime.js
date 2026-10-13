import { startRuntime } from './startRuntime.js';

// The mobile opening composes before original main; main still initializes and
// runs all gameplay. Exit returns to the warning without replaying asset loading.
export async function runMobileRuntime(runtime, { settings, configure, runAnim, opening, setPlayerNames }) {
  if (!opening?.enabled()) return startRuntime(runtime, { entry: settings.entry, configure, runAnim });
  const destination = opening.takeDestination?.(settings.skipLore);
  if (destination) { settings = { ...settings, ...destination }; configure(destination); }
  setPlayerNames(opening.getNames());
  let entry = settings.entry;
  if (entry === 'main' && !settings.skipIntro && settings.startLevel === 0) {
    setPlayerNames(await opening.begin());
    configure({ skipIntro: true });
  }
  while (true) {
    await startRuntime(runtime, { entry, configure, runAnim });
    setPlayerNames(await opening.begin({ afterExit: true }));
    configure({ skipIntro: true, startLevel: 0 }); entry = 'main';
  }
}
