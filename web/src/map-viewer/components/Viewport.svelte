<script>
  import { onMount } from 'svelte';
  let { matrix, rows, cols, zoomScale, selections, isDrawMode, toggleVisual, toggleWalls, toggleHoles, toggleBoxes, toggleGrid, collisionData, currentMode, getLevelIndex, onCoords, onSelection } = $props();
  let canvas;
  const TILE_SIZE = 14;
  const DOS_COLORS = {0:'#0f172a',1:'#ffffff',2:'#ef4444',3:'#22c55e',4:'#3b82f6',5:'#06b6d4',6:'#d946ef',7:'#eab308',8:'#94a3b8',9:'#1e293b',10:'#991b1b',11:'#166534',12:'#1e3a8a',13:'#155e75',14:'#701a75',15:'#854d0e',16:'#334155'};
  let dragStart=null, dragCurrent=null;

  export function getCanvas(){ return canvas; }

  function getCoords(e){
    const r=canvas.getBoundingClientRect(), s=TILE_SIZE*zoomScale;
    return { x:Math.floor((e.clientX-r.left)/s), y:Math.floor((e.clientY-r.top)/s), s };
  }
  export function draw(){
    if(!canvas||!matrix) return;
    const ctx=canvas.getContext('2d'), s=TILE_SIZE*zoomScale;
    canvas.width=cols*s; canvas.height=rows*s;
    ctx.clearRect(0,0,canvas.width,canvas.height);
    const lvl=getLevelIndex(), lvlCol=collisionData?.[lvl];
    if(toggleVisual){
      for(let r=0;r<rows;r++) for(let c=0;c<cols;c++){ const v=matrix[r][c]; ctx.fillStyle=DOS_COLORS[v]||DOS_COLORS[0]; ctx.fillRect(c*s,r*s,s,s); }
    } else { ctx.fillStyle='#0f172a'; ctx.fillRect(0,0,canvas.width,canvas.height); }
    const LOGICAL=s*2, show=currentMode==='maps';
    if(show&&toggleWalls&&lvlCol?.walls){ ctx.fillStyle='rgba(239,68,68,0.55)'; ctx.strokeStyle='#ef4444'; ctx.lineWidth=1; lvlCol.walls.forEach(([wx,wy])=>{ ctx.fillRect(wx*s,wy*s,LOGICAL,LOGICAL); ctx.strokeRect(wx*s,wy*s,LOGICAL,LOGICAL); }); }
    if(show&&toggleHoles&&lvlCol?.holes){ ctx.fillStyle='rgba(192,132,252,0.6)'; ctx.strokeStyle='#c084fc'; ctx.lineWidth=1; lvlCol.holes.forEach(([hx,hy])=>{ ctx.fillRect(hx*s,hy*s,LOGICAL,LOGICAL); ctx.strokeRect(hx*s,hy*s,LOGICAL,LOGICAL); }); }
    if(show&&toggleBoxes&&lvlCol?.boxes){ ctx.fillStyle='rgba(250,204,21,0.7)'; ctx.strokeStyle='#facc15'; ctx.lineWidth=1.5; lvlCol.boxes.forEach(([bx,by])=>{ ctx.fillRect(bx*s+2,by*s+2,LOGICAL-4,LOGICAL-4); ctx.strokeRect(bx*s+1,by*s+1,LOGICAL-2,LOGICAL-2); }); }
    if(toggleGrid){ ctx.strokeStyle='rgba(255,255,255,0.05)'; ctx.lineWidth=1; for(let c=0;c<=cols;c++){ ctx.beginPath(); ctx.moveTo(c*s,0); ctx.lineTo(c*s,canvas.height); ctx.stroke(); } for(let r=0;r<=rows;r++){ ctx.beginPath(); ctx.moveTo(0,r*s); ctx.lineTo(canvas.width,r*s); ctx.stroke(); } }
    ctx.lineWidth=2;
    selections.forEach((sel,idx)=>{
      ctx.strokeStyle=idx%2===0?'#38bdf8':'#c084fc'; ctx.fillStyle=idx%2===0?'rgba(56,189,248,0.15)':'rgba(192,132,252,0.15)';
      ctx.fillRect(sel.x1*s,sel.y1*s,(sel.x2-sel.x1+1)*s,(sel.y2-sel.y1+1)*s);
      ctx.strokeRect(sel.x1*s+0.5,sel.y1*s+0.5,(sel.x2-sel.x1+1)*s-1,(sel.y2-sel.y1+1)*s-1);
      ctx.fillStyle=ctx.strokeStyle; ctx.font=`${Math.max(10,s*0.6)}px monospace`; ctx.fillText(String(idx+1), sel.x1*s+4, sel.y1*s+14);
    });
    if(dragStart&&dragCurrent){
      const x1=Math.min(dragStart.x,dragCurrent.x), y1=Math.min(dragStart.y,dragCurrent.y), x2=Math.max(dragStart.x,dragCurrent.x), y2=Math.max(dragStart.y,dragCurrent.y);
      ctx.strokeStyle='#facc15'; ctx.setLineDash([6,4]); ctx.strokeRect(x1*s+0.5,y1*s+0.5,(x2-x1+1)*s-1,(y2-y1+1)*s-1); ctx.setLineDash([]); ctx.fillStyle='rgba(250,204,21,0.12)'; ctx.fillRect(x1*s,y1*s,(x2-x1+1)*s,(y2-y1+1)*s);
    }
  }
  function handleDown(e){
    if(!isDrawMode) return;
    const {x,y}=getCoords(e); if(x<0||x>=80||y<0||y>=63) return;
    dragStart={x,y}; dragCurrent={x,y}; e.preventDefault();
  }
  function handleMove(e){
    if(dragStart){ const {x,y}=getCoords(e); dragCurrent={x:Math.max(0,Math.min(79,x)), y:Math.max(0,Math.min(62,y))}; draw(); return; }
    if(isDrawMode) return;
    const {x,y}=getCoords(e);
    if(x>=0&&x<80&&y>=0&&y<63){
      const tile=matrix?.[y]?.[x];
      let col=currentMode==='sprites'?'— (Sprite)':'None (Empty)';
      if(currentMode==='maps'){
        const lvl=getLevelIndex();
        const hit=arr=>arr.some(([px,py])=> x>=px&&x<px+2&&y>=py&&y<py+2);
        if(collisionData?.[lvl]?.walls?.some&&hit(collisionData[lvl].walls)) col='🧱 Wall (Pared)';
        else if(collisionData?.[lvl]?.holes?.some&&hit(collisionData[lvl].holes)) col='🕳️ Hole / Pit (Hueco)';
        else if(collisionData?.[lvl]?.boxes?.some&&hit(collisionData[lvl].boxes)) col='📦 Box Spawn (Caja)';
      }
      onCoords?.({x,y,tile,col});
    }
  }
  function handleUp(){
    if(!dragStart||!dragCurrent) return;
    const x1=Math.min(dragStart.x,dragCurrent.x), y1=Math.min(dragStart.y,dragCurrent.y), x2=Math.max(dragStart.x,dragCurrent.x), y2=Math.max(dragStart.y,dragCurrent.y);
    onSelection?.({x1,y1,x2,y2});
    dragStart=null; dragCurrent=null; draw();
  }
  $effect(()=>{ void matrix; void zoomScale; void toggleVisual; void toggleWalls; void toggleHoles; void toggleBoxes; void toggleGrid; void selections; if(matrix) draw(); });
</script>

<canvas bind:this={canvas} width="1280" height="960" onmousemove={handleMove} onmousedown={handleDown} onmouseup={handleUp} onmouseleave={()=>{dragStart=null; dragCurrent=null; draw();}}></canvas>

<style>
  canvas { border-radius:8px; border:1px solid var(--bg-panel-border); cursor:crosshair; }
</style>
