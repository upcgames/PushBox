export const START_POINTS = [
  { value: '0', label: 'Standard intro' },
  { value: '-1', label: 'Skip entering name' },
  { value: 'menu', label: 'Menu' },
  { value: 'instructions', label: 'Instructions' },
  ...[1, 2, 3, 4, 5].map(level => ({ value: String(level), label: `Level ${level}` })),
  { value: '6', label: 'Congratulations' },
];

export function populateStartPoints(select, defaultPoint = '0') {
  select.innerHTML = START_POINTS.map(({ value, label }) => `<option value="${value}">${label}</option>`).join('');
  select.value = defaultPoint;
}

export function startPointSettings(value, skipLore) {
  if (value === 'menu' || value === 'instructions') {
    return { entry: value, skipIntro: true, startLevel: 0, skipLore };
  }
  const level = Number(value);
  return { entry: 'main', skipIntro: level !== 0, startLevel: level > 0 ? level : 0, skipLore };
}
