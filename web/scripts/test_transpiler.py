import sys
from transpiler_core import transform_cpp_reference_params, transpile_cpp_to_js, resolve_async_functions

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
            "Console.Write(String.fromCharCode(219));",
            'Console.Write("Score: ");'
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
        "expected_contains": ["Escribir(Cadena, retraso = 0, sonido = 0)"]
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
            js_output = transpile_cpp_to_js(cpp, asset_replacements=asset_replacements)
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
