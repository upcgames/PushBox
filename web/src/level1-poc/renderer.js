import Phaser from 'phaser';

// Phaser consumes a session. Rendering never advances the level or changes rules.
export function mountRenderer(parent, session) {
  const cell = 16, actorSize = cell * 2;
  let scene, boardOnly = true, motion = true;
  const base = `${import.meta.env.BASE_URL}level1-poc/`;
  class LevelScene extends Phaser.Scene {
    preload() {
      this.load.tilemapTiledJSON('level1', `${base}level1.tmj`);
      this.load.image('colors', `${base}colors.png`);
    }
    create() {
      scene = this;
      const map = this.make.tilemap({ key: 'level1' });
      const tiles = map.addTilesetImage('DOS Colors', 'colors');
      map.createLayer('Artwork', tiles);
      const graphics = this.make.graphics({ x: 0, y: 0 }, false);
      const texture = (name, paint) => {
        graphics.clear(); paint(graphics);
        graphics.generateTexture(name, actorSize, actorSize);
      };
      texture('player', g => {
        g.fillStyle(0x000000).fillRect(0, 0, 32, 32);
        g.lineStyle(2, 0xffffff).strokeRect(4, 4, 24, 24).strokeRect(8, 8, 16, 16);
        g.fillStyle(0x000000).fillRect(12, 0, 8, 32).fillRect(0, 12, 32, 8);
      });
      texture('box', g => {
        g.fillStyle(0x701a75).fillRect(0, 0, 32, 32);
        g.lineStyle(1, 0xe5b1e8, 0.6).strokeRect(3, 3, 26, 26);
      });
      texture('target', g => {
        g.lineStyle(2, 0x701a75).strokeRect(3, 3, 26, 26);
      });
      texture('portal', g => {
        g.fillStyle(0x3b82f6, 0.9);
        for (let y = 0; y < 32; y += 4) {
          for (let x = (y % 8 ? 2 : 0); x < 32; x += 4) g.fillRect(x, y, 2, 3);
        }
      });
      graphics.destroy();
      const state = session.getSnapshot();
      this.targets = state.targets.map(target => this.add.image(target.x * cell, target.y * cell, 'target').setOrigin(0));
      this.portal = this.add.image(state.portal.x * cell, state.portal.y * cell, 'portal').setOrigin(0);
      this.boxes = state.boxes.map(box => this.add.image(box.x * cell, box.y * cell, 'box').setOrigin(0));
      this.player = this.add.image(state.player.x * cell, state.player.y * cell, 'player').setOrigin(0);
      const points = [...state.walls, ...state.targets, ...state.boxes, state.player, state.portal];
      this.board = { left: Math.min(...points.map(p => p.x)) - 2,
        top: Math.min(...points.map(p => p.y)) - 2,
        right: Math.max(...points.map(p => p.x)) + 4,
        bottom: Math.max(...points.map(p => p.y)) + 4 };
      this.mapSize = { width: map.widthInPixels, height: map.heightInPixels };
      const stop = session.subscribe(state => {
        this.state = state;
        this.boxes.forEach((sprite, id) => {
          const box = state.boxes.find(box => box.id === id);
          sprite.setPosition(box.x * cell, box.y * cell);
          sprite.setTint(state.targets.some(target => target.covered && target.x === box.x && target.y === box.y) ? 0xa4f0bf : 0xffffff);
        });
        this.targets.forEach((sprite, i) => sprite.setVisible(!state.targets[i].covered));
        this.portal.setVisible(state.portal.active);
        this.player.setPosition(state.player.x * cell, state.player.y * cell);
        this.player.setAlpha(state.phase === 'completed' ? 0.45 : 1);
      });
      this.scale.on('resize', this.fit, this);
      this.events.once('shutdown', () => { stop(); this.scale.off('resize', this.fit, this); scene = null; });
      this.fit();
    }
    fit() {
      const b = this.board;
      const width = boardOnly ? (b.right - b.left) * cell : this.mapSize.width;
      const height = boardOnly ? (b.bottom - b.top) * cell : this.mapSize.height;
      this.cameras.main.setZoom(Math.min(this.scale.width / width, this.scale.height / height));
      this.cameras.main.centerOn(boardOnly ? (b.left + b.right) * cell / 2 : width / 2,
        boardOnly ? (b.top + b.bottom) * cell / 2 : height / 2);
    }
    update(time) {
      if (!this.state) return;
      this.player.y = this.state.player.y * cell + (motion && this.state.phase === 'playing' ? Math.sin(time / 220) * 1.5 : 0);
    }
  }
  const game = new Phaser.Game({
    type: Phaser.AUTO, parent, width: parent.clientWidth, height: parent.clientHeight,
    backgroundColor: '#20101f', pixelArt: true, scene: LevelScene,
    scale: { mode: Phaser.Scale.NONE },
    input: { keyboard: false }, audio: { noAudio: true },
    banner: false,
  });
  const observer = new ResizeObserver(entries => {
    const { width, height } = entries[0].contentRect;
    if (width > 0 && height > 0) game.scale.resize(Math.round(width), Math.round(height));
  });
  observer.observe(parent);
  return {
    setBoardOnly(value) { boardOnly = value; scene?.fit(); },
    setMotion(value) { motion = value; },
    dispose() { observer.disconnect(); game.destroy(true); },
  };
}
