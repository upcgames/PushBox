const letters = {
  P: ['11110', '10001', '10001', '11110', '10000', '10000', '10000'],
  U: ['10001', '10001', '10001', '10001', '10001', '10001', '01110'],
  S: ['01111', '10000', '10000', '01110', '00001', '00001', '11110'],
  H: ['10001', '10001', '10001', '11111', '10001', '10001', '10001'],
  B: ['11110', '10001', '10001', '11110', '10001', '10001', '11110'],
  O: ['01110', '10001', '10001', '10001', '10001', '10001', '01110'],
  X: ['10001', '10001', '01010', '00100', '01010', '10001', '10001'],
};

export const TITLE_STUDIES = ['Golden arcade', 'Stacked crates', 'Box-letter badge'];

function word(ctx, text, x, y, size, color) {
  ctx.fillStyle = color;
  [...text].forEach((letter, index) => letters[letter].forEach((row, py) => [...row].forEach((pixel, px) => {
    if (pixel === '1') ctx.fillRect(x + (index * 6 + px) * size, y + py * size, size, size);
  })));
}

export function drawTitle(canvas, variant) {
  const ctx = canvas.getContext('2d');
  ctx.clearRect(0, 0, 256, 112);
  if (variant === 0) {
    word(ctx, 'PUSHBOX', 28, 42, 5, '#854d0e');
    word(ctx, 'PUSHBOX', 24, 37, 5, '#eab308');
    ctx.fillStyle = '#fff0ba';
    ctx.fillRect(24, 29, 205, 2); ctx.fillRect(24, 80, 205, 2);
  } else if (variant === 1) {
    word(ctx, 'PUSH', 63, 12, 6, '#155e75');
    word(ctx, 'PUSH', 59, 8, 6, '#67e8f9');
    word(ctx, 'BOX', 81, 64, 6, '#854d0e');
    word(ctx, 'BOX', 77, 60, 6, '#eab308');
  } else {
    ctx.fillStyle = '#334155'; ctx.fillRect(14, 22, 228, 66);
    ctx.fillStyle = '#080914'; ctx.fillRect(18, 26, 220, 58);
    word(ctx, 'PUSHBOX', 24, 38, 5, '#fff0ba');
    // The O is a caja, retaining the letter's place and size.
    const x = 24 + 5 * 6 * 5;
    ctx.fillStyle = '#080914'; ctx.fillRect(x, 38, 25, 35);
    ctx.fillStyle = '#eab308'; ctx.fillRect(x, 43, 25, 25);
    ctx.fillStyle = '#854d0e'; ctx.fillRect(x + 4, 47, 17, 17);
    ctx.fillStyle = '#fff0ba';
    for (let i = 0; i < 5; i++) { ctx.fillRect(x + 4 + i * 3, 47 + i * 3, 3, 3); ctx.fillRect(x + 16 - i * 3, 47 + i * 3, 3, 3); }
  }
}
