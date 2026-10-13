<script>
  let { name, muted = false } = $props();
</script>

<svg viewBox={name === 'undo' ? '0 0 32 24' : '0 0 24 24'} aria-hidden="true">
  {#if name === 'direction'}
    <path d="M10 3h4v3h3v3h3v3H4V9h3V6h3V3ZM9 12h6v9H9Z" />
  {:else if name === 'undo'}
    <path class="cue-chevron" d="M12 5h4l-7 7 7 7h-4L5 12l7-7Z" />
    <g transform="translate(12 0)"><path class="cue-chevron second" d="M12 5h4l-7 7 7 7h-4L5 12l7-7Z" /></g>
  {:else if name === 'hourglass'}
    <path fill-rule="evenodd" d="M5 2H19V6L14 11V13L19 18V22H5V18L10 13V11L5 6V2ZM8 5V6L12 10L16 6V5H8ZM12 14L8 18V19H16V18L12 14Z" />
    <path d="M9 6h6l-3 3-3-3Zm1 11h4v2h-4v-2Z" />
  {:else if name === 'troll'}
    <path d="M5 3h14v3h3v12h-3v3H5v-3H2V6h3V3Zm3 4v3h3V7H8Zm6 0v3h3V7h-3Zm-7 7v3h3v2h5v-2h3v-3h-3v2h-5v-2H7Z" />
  {:else if name === 'pause'}
    <path d="M5 3h5v18H5V3Zm9 0h5v18h-5V3Z" />
  {:else if name === 'portal'}
    <path d="M4 2h16v20H4V2Z" />
    <path fill="#182333" d="M7 5h10v17H7V5Z" />
    <path fill="#b77935" d="M8 6h8v15H8V6Z" />
    <path fill="#854d0e" d="M10 8h4v4h-4V8Zm0 7h4v4h-4v-4Z" />
    <path d="M14 13h2v2h-2v-2ZM2 22h20v2H2v-2Z" />
  {:else if name === 'sound'}
    <path d="M3 9h5l6-5v16l-6-5H3V9Z" />
    {#if muted}
      <path fill="#ef4444" d="M18 2h4v4h-3v3h-3v3h-3v3h-3v3H7v3H3v-4h3v-3h3v-3h3V8h3V5h3V2Z" />
    {:else}
      <path d="M17 7h3v10h-3V7Z" />
    {/if}
  {/if}
</svg>
