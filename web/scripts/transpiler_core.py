import re

REF_VARS_SET = {"nivel", "opcion", "sonido"}

TRANSPILE_RULES = [
    # C++ Option A: new int**[N] / new int*[N] / new int [N] -> JS new Array(N)
    (re.compile(r'\bnew\s+(?:int|bool|char|float|double|long|short)\s*\*+\s*\[\s*([^\]]+)\s*\]'), r'new Array(\1)'),
    (re.compile(r'\bnew\s+(?:int|bool|char|float|double|long|short)\s*\[\s*([^\]]+)\s*\]'), r'new Array(\1)'),

    # Mechanical C++ scope operator :: -> JS object property .
    (re.compile(r'::'), r'.'),

    # C++ manual memory deallocations -> valid empty statement for JS Garbage Collector
    (re.compile(r'\bdelete\s*\[\s*\]\s*([A-Za-z0-9_]+(?:\s*\[\s*[^\]]+\s*\])?)\s*;'), r'; /* delete[] \1 */'),

    # Strip C++ address-of operator & in function call argument lists (&csbi -> csbi)
    (re.compile(r'(?<=[(,\s])&([A-Za-z0-9_]+)'), r'\1'),

    # Convert C++ Octal escape sequences (e.g. \242 -> \xA2) for JS ES module strict mode
    (re.compile(r'\\([0-7]{3})'), lambda m: f'\\x{int(m.group(1), 8):02x}'),

    # Mechanical type conversions int(x) -> Number(x)
    (re.compile(r'\bint\s*\(\s*([A-Za-z0-9_]+(?:\[[^\]]+\])*)\s*\)'), r'Number(\1)'),

    # Class instantiation: Random r; -> let r = new Random();
    (re.compile(r'\bRandom\s+([A-Za-z0-9_]+)\s*;'), r'let \1 = new Random();'),

    # Array and Pointer variable declarations: int **var -> let var, int *var -> let var (avoid matching type cast int(x))
    (re.compile(r'\b(?:int|bool|char|float|double|long|short|WORD|CONSOLE_SCREEN_BUFFER_INFO)\s*\*+\s*([A-Za-z0-9_]+)'), r'let \1'),
    (re.compile(r'\b(?:int|bool|char|float|double|long|short|WORD|CONSOLE_SCREEN_BUFFER_INFO)\s+([A-Za-z0-9_]+)\s*\[\s*\d*\s*\]\s*=\s*\{'), r'const \1 = ['),
    (re.compile(r'\b(?:int|bool|char|float|double|long|short|WORD|CONSOLE_SCREEN_BUFFER_INFO)\s+([A-Za-z0-9_]+)\b(?!\s*\()'), r'let \1'),
    (re.compile(r'\bstring\s+([A-Za-z0-9_]+)\s*='), r'const \1 ='),
    
    # Stream I/O & string properties
    (re.compile(r'\bletras\.length\s*\(\s*\)'), r'letras.length'),
    (re.compile(r'\bcout\s*<<\s*char\s*\(\s*(\d+|[A-Za-z0-9_]+)\s*\)\s*;'), r'Console.Write(String.fromCharCode(\1));'),
    (re.compile(r'\bcout\s*<<\s*(.*?)\s*;'), r'Console.Write(\1);'),

    # Win32 constants
    (re.compile(r'\bFALSE\b'), r'false'),
    (re.compile(r'\bTRUE\b'), r'true'),
    (re.compile(r'\bNULL\b'), r'null'),
    (re.compile(r'\bnullptr\b'), r'null'),
]

def resolve_async_functions(cpp_code, base_async=None):
    if base_async is None:
        base_async = {"Sleep", "_getch", "esperartecla", "scanf"}

    func_bodies = {}
    func_matches = re.finditer(r'(?:void|int|bool|char)\s+([A-Za-z0-9_]+)\s*\(([^)]*)\)\s*\{', cpp_code)
    for m in func_matches:
        func_name = m.group(1)
        start = m.end()
        depth = 1
        end = start
        while end < len(cpp_code) and depth > 0:
            if cpp_code[end] == '{': depth += 1
            elif cpp_code[end] == '}': depth -= 1
            end += 1
        func_bodies[func_name] = cpp_code[start:end]

    async_set = set(base_async)
    for fn, body in func_bodies.items():
        if any(trig in body for trig in base_async):
            async_set.add(fn)

    changed = True
    while changed:
        changed = False
        for fn, body in func_bodies.items():
            if fn not in async_set:
                for async_fn in list(async_set):
                    pattern = re.compile(rf'(?<![A-Za-z0-9_]){re.escape(async_fn)}\s*\(')
                    if pattern.search(body):
                        async_set.add(fn)
                        changed = True
                        break
    return async_set

def clean_param_types(param_str):
    if not param_str.strip():
        return ""
    params = param_str.split(',')
    clean_params = []
    for p in params:
        p_clean = re.sub(r'\b(?:const|string|int|bool|char|float|double)\s*', '', p.strip())
        p_clean = re.sub(r'^\*+\s*', '', p_clean.strip())
        clean_params.append(p_clean.strip())
    return ", ".join(clean_params)

def add_await_to_calls(line, all_async_funcs):
    stripped = line.strip()
    if stripped.startswith("export async function") or stripped.startswith("export function") or stripped.startswith("function ") or stripped.startswith("async function"):
        return line

    def await_replacer(match):
        prefix = match.group(1) or ""
        func_name = match.group(2)
        args = match.group(3)
        if func_name in all_async_funcs:
            return f"{prefix}await {func_name}({args})"
        return match.group(0)

    pattern = re.compile(r'(?<!export\s)(?<!function\s)(?<!async\s)(?<!await\s)\b(?:([A-Za-z0-9_]+\s*=\s*))?([A-Za-z0-9_]+)\s*\(([^;{}]*)\)')
    return pattern.sub(await_replacer, line)

def transform_cpp_reference_params(cpp_code):
    ref_params_by_func = {}
    func_matches = re.finditer(r'(?:void|int|bool)\s+(\w+)\s*\(([^)]+)\)', cpp_code)
    
    for match in func_matches:
        func_name, param_list = match.groups()
        ref_vars = set()
        for p in param_list.split(','):
            p_strip = p.strip()
            ref_match = re.search(r'(?:int|bool|char|float|double)\s*&\s*(\w+)', p_strip)
            if ref_match:
                ref_vars.add(ref_match.group(1))
        if ref_vars:
            ref_params_by_func[func_name] = ref_vars

    lines = cpp_code.splitlines()
    js_lines = []
    current_func = None
    func_ref_vars = set()

    for line in lines:
        stripped = line.strip()
        
        header_match = re.search(r'\b(?:void|int|bool)\s+([A-Za-z0-9_]+)\s*\(([^)]*)\)', stripped)
        if header_match:
            func_name = header_match.group(1)
            current_func = func_name
            func_ref_vars = ref_params_by_func.get(func_name, set())
            js_lines.append(line)
            continue

        modified_line = line

        if current_func and func_ref_vars:
            for var in func_ref_vars:
                modified_line = re.sub(rf'\b{var}\s*(\+=|-=|\*=|\/=)\s*', f'{var}.v \\1 ', modified_line)
                modified_line = re.sub(rf'\b{var}\+\+', f'{var}.v++', modified_line)
                modified_line = re.sub(rf'\b{var}--\b', f'{var}.v--', modified_line)
                modified_line = re.sub(rf'\+\+\b{var}\b', f'++{var}.v', modified_line)
                modified_line = re.sub(rf'--\b{var}\b', f'--{var}.v', modified_line)
                modified_line = re.sub(rf'\b{var}\s*=\s*(?!=)', f'{var}.v = ', modified_line)
                
                def replace_ref(m):
                    start = m.start()
                    end = m.end()
                    l_str = m.string
                    prefix = l_str[:start].rstrip()
                    suffix = l_str[end:].lstrip()
                    if (prefix.endswith('(') or prefix.endswith(',')) and (suffix.startswith(',') or suffix.startswith(')')) and not (prefix.endswith('if (') or prefix.endswith('while (')):
                        return var
                    return f'{var}.v'

                modified_line = re.sub(rf'\b{var}\b(?!\.v)', replace_ref, modified_line)
        else:
            for ref_var in REF_VARS_SET:
                modified_line = re.sub(rf'\b{ref_var}\s*=\s*([0-9]+)\s*;', f'{ref_var} = new Ref(\\1);', modified_line)

        js_lines.append(modified_line)

    return "\n".join(js_lines)

def transpile_cpp_to_js(code, asset_replacements=None, all_async_funcs=None):
    if asset_replacements is None:
        asset_replacements = {}
    if all_async_funcs is None:
        all_async_funcs = resolve_async_functions(code)

    code = transform_cpp_reference_params(code)
    lines = code.splitlines()
    transpiled_lines = []

    for line_idx, line in enumerate(lines):
        if any(unsupported in line for unsupported in ['class ', 'template', 'std::vector', 'goto ']):
            raise ValueError(f"Unsupported C++ construct found at line {line_idx+1}: {line}")

        header_match = re.search(r'\b(?:void|int|bool|char)\s+([A-Za-z0-9_]+)\s*\(([^)]*)\)', line)
        if header_match:
            fname = header_match.group(1)
            raw_params = header_match.group(2)
            clean_p = clean_param_types(raw_params)
            export_kw = "export async function" if fname in all_async_funcs else "export function"
            line = re.sub(r'\b(?:void|int|bool|char)\s+([A-Za-z0-9_]+)\s*\([^)]*\)', f'{export_kw} {fname}({clean_p})', line)

        stripped_line = line.strip()
        if stripped_line in asset_replacements:
            line = asset_replacements[stripped_line]

        for pattern, replacement in TRANSPILE_RULES:
            line = pattern.sub(replacement, line)

        if all_async_funcs:
            line = add_await_to_calls(line, all_async_funcs)

        transpiled_lines.append(line)

    return "\n".join(transpiled_lines)
