import js from "@eslint/js";

export default [
  js.configs.recommended,
  {
    files: ["src/**/*.js"],
    languageOptions: {
      ecmaVersion: 2022,
      sourceType: "module",
      globals: {
        // Browser Globals
        window: "readonly",
        document: "readonly",
        console: "readonly",
        setTimeout: "readonly",
        clearTimeout: "readonly",
        requestAnimationFrame: "readonly",
        performance: "readonly",
        Audio: "readonly",
        fetch: "readonly",

        // Extracted Asset Globals
        letras: "readonly",
        arr: "readonly",
        matrizint: "readonly",

        // Platform & Console Shims
        Console: "readonly",
        ConsoleColor: "readonly",
        Sleep: "readonly",
        _kbhit: "readonly",
        _getch: "readonly",
        scanf: "readonly",
        strlen: "readonly",
        toupper: "readonly",
        system: "readonly",
        Convert: "readonly",
        PlaySound: "readonly",
        Random: "readonly",
        CONSOLE_SCREEN_BUFFER_INFO: "readonly",
        SetConsoleTextAttribute: "readonly",
        GetStdHandle: "readonly",
        FlushConsoleInputBuffer: "readonly",
        fflush: "readonly",
        GetConsoleScreenBufferInfo: "readonly",
        Ref: "readonly",

        // Win32 Constants & Macros
        TEXT: "readonly",
        SND_SYNC: "readonly",
        SND_ASYNC: "readonly",
        SND_NODEFAULT: "readonly",
        SND_MEMORY: "readonly",
        SND_LOOP: "readonly",
        SND_NOSTOP: "readonly",
        STD_OUTPUT_HANDLE: "readonly",
        STD_INPUT_HANDLE: "readonly",
        stdin: "readonly"
      }
    },
    rules: {
      "no-undef": "error",
      "no-unused-vars": "off",
      "no-constant-condition": "off",
      "no-unreachable": "off",
      "no-empty": "off"
    }
  }
];
