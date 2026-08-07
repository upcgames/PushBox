import sys
from ast_transpiler import CppToJsAST
from transpile_dsl_to_js import resolve_async_functions

TEST_CASES = [
    {
        "name": "Dynamic Array Allocation",
        "cpp": "int **matriz = new int*[136]; int *row = new int[80];",
        "expected_contains": ["let matriz = new Array(136);", "let row = new Array(80);"]
    },
    {
        "name": "Memory Deallocation",
        "cpp": "delete[] matriz; delete[] row;",
        "expected_contains": ["; /* delete[] matriz */", "; /* delete[] row */"]
    },
    {
        "name": "Octal Escape Conversion",
        "cpp": 'Escribir("M\\242vil", 1);',
        "expected_contains": ['"M\\xa2vil"']
    },
    {
        "name": "Class Instantiation",
        "cpp": "Random r;",
        "expected_contains": ["let r = new Random();"]
    },
    {
        "name": "Pointer / Variable Declarations",
        "cpp": "int **matriz; char *n1; string s = \"hello\";",
        "expected_contains": ["let matriz;", "let n1;", 'const s = "hello";']
    },
    {
        "name": "cout Stream I/O",
        "cpp": "cout << char(219); cout << \"Score: \";",
        "expected_contains": [
            'Console.Write( String.fromCharCode(219));',
            'Console.Write( "Score: ");'
        ]
    },
    {
        "name": "String Length Conversion",
        "cpp": "if (i < letras.length()) { letras.length(); }",
        "expected_contains": [
            "if (i < letras.length) { letras.length; }"
        ]
    },
    {
        "name": "Constants & Type Casts",
        "cpp": "int val = int(matriz[0][0]); bool flag = TRUE; char* p = NULL;",
        "expected_contains": ["Number(matriz[0][0])", "true", "null"]
    },
    {
        "name": "Parameter Type Cleaning",
        "cpp": "void Escribir(char *Cadena, int retraso = 0, int sonido = 0) {}",
        "expected_contains": [
            'export function Escribir( Cadena,  retraso = 0,  sonido = 0)'
        ]
    },
    {
        "name": "Nested Pointer Parameter Cleaning",
        "cpp": "void dibuja_mapa(int **matriz, char *Cadena) {}",
        "expected_contains": [
            'export function dibuja_mapa( matriz,  Cadena)'
        ]
    },
    {
        "name": "Pass-by-Reference (& -> Ref.v)",
        "cpp": """void MenuPrincipal(int &nivel) {
    if (nivel == 0) {
        nivel = 1;
    }
}""",
        "expected_contains": ["nivel.v == 0", "nivel.v = 1"]
    },
    {
        "name": "Pass Ref Object as Function Argument",
        "cpp": """void ControlDeNiveles(int &nivel) {
    if (nivel == 0) {
        MenuPrincipal(nivel, matriz);
    }
}""",
        "expected_contains": ["if (nivel.v == 0)", "MenuPrincipal(nivel, matriz)"]
    },
    {
        "name": "Value-Result Wrapper for Primitive to Reference",
        "cpp": """void MovilyCaja(int mx, int my, int mov) {
    movi(mx, my, mov);
}""",
        "expected_contains": ["(() => { let _r0 = new Ref(mx); let _r1 = new Ref(my); movi(_r0, _r1, mov); mx = _r0.v; my = _r1.v; })()"]
    },
    {
        "name": "Matrix Annotation Unpacking",
        "cpp": "// @DSL_EXTRACTED_MATRIX matrizint maps_json/PushBox.json",
        "asset_replacements": {
            "// @DSL_EXTRACTED_MATRIX matrizint maps_json/PushBox.json": "const matrizint = PushBoxData.matrix || PushBoxData;"
        },
        "expected_contains": ["const matrizint = PushBoxData.matrix || PushBoxData;"]
    },
    {
        "name": "Background Annotation Unpacking",
        "cpp": "// @DSL_EXTRACTED_BACKGROUND Fondo01 backgrounds_json/Fondo01.json",
        "asset_replacements": {
            "// @DSL_EXTRACTED_BACKGROUND Fondo01 backgrounds_json/Fondo01.json": "const letras = Fondo01Data.letras; const arr = Fondo01Data.colors || Fondo01Data.arr;"
        },
        "expected_contains": ["const letras = Fondo01Data.letras; const arr = Fondo01Data.colors || Fondo01Data.arr;"]
    },
    # 100% Self-Contained DAG Async Resolution Test:
    {
        "name": "DAG Async Resolution (Automatic Sync vs Async Detection)",
        "cpp": """
void foo() {
    Sleep(1000);
}
void bar() {
    ir(10, 20);
    foo();
}
""",
        "expected_contains": [
            "export async function foo()", # 👈 Contains Sleep, so export async!
            "export async function bar()", # 👈 Calls foo(), so export async!
            "ir(10, 20);",                 # 👈 Sync function: NO await!
            "await foo();"                 # 👈 Transitive async: HAS await!
        ]
    }
]

def run_tests():
    print("==================================================")
    print("🧪 Running 100% Self-Contained Transpiler Unit Test Suite")
    print("==================================================")
    
    passed = 0
    failed = 0

    for test in TEST_CASES:
        name = test["name"]
        cpp = test["cpp"]
        asset_replacements = test.get("asset_replacements", {})
        expected = test["expected_contains"]
        
        print(f"\n▶ Testing: {name}")
        try:
            # Apply asset replacements before AST parsing (orchestrator behavior)
            cpp_input = cpp
            for k, v in asset_replacements.items():
                cpp_input = cpp_input.replace(k, v)
                
            all_async_funcs = resolve_async_functions(cpp_input)
            ast_engine = CppToJsAST()
            js_output = ast_engine.parse(cpp_input, all_async_funcs=all_async_funcs)
            
            all_found = True
            for exp in expected:
                if exp not in js_output:
                    print(f"  ❌ FAIL: Expected '{exp}' in generated JS output:")
                    print(js_output)
                    all_found = False
                    failed += 1
                    break
            if all_found:
                print(f"  ✅ PASS: Output matches specification.")
                passed += 1
        except Exception as e:
            print(f"  ❌ HARD FAIL: {e}")
            failed += 1

    print("\n==================================================")
    if failed == 0:
        print(f"🎉 ALL {passed} TRANSPILER UNIT TESTS PASSED SUCCESSFULLY!")
        print("==================================================")
        sys.exit(0)
    else:
        print(f"❌ {failed} TESTS FAILED!")
        print("==================================================")
        sys.exit(1)

if __name__ == "__main__":
    run_tests()
