import os
import re
import shutil
import sys
import subprocess
from ast_transpiler import CppToJsAST

script_dir = os.path.dirname(os.path.abspath(__file__))
web_dir = os.path.dirname(script_dir)
repo_root = os.path.dirname(web_dir)

dsl_dir = os.path.join(web_dir, "pushbox_dsl")
js_dir = os.path.join(web_dir, "src", "dsl")
rules_file = os.path.join(repo_root, "dsl_module_manifest.txt")

os.makedirs(js_dir, exist_ok=True)

# Copy asset JSON directories to web/src/dsl/
for asset_dir in ["maps_json", "backgrounds_json"]:
    src_json = os.path.join(dsl_dir, asset_dir)
    dst_json = os.path.join(js_dir, asset_dir)
    if os.path.exists(src_json):
        shutil.copytree(src_json, dst_json, dirs_exist_ok=True)

# Load function owner rules from dsl_module_manifest.txt
func_to_module = {}
module_to_funcs = {}
current_mod = None
current_mod = None
gallery_registry = {}
animation_registry = set()
animation_dep_registry = set()

with open(rules_file, 'r', encoding='utf-8') as f:
    for line in f:
        line_str = line.strip()
        if not line_str:
            continue
        if line_str.startswith("#"):
            current_mod = line_str[1:].strip().replace('.cpp', '.js')
            if current_mod not in module_to_funcs:
                module_to_funcs[current_mod] = set()
        elif current_mod:
            # Check for #gallery / #animation / #animation-dep tags
            parts = line_str.split('#')
            func_name = parts[0].strip()
            
            func_to_module[func_name] = current_mod
            module_to_funcs[current_mod].add(func_name)
            
            if len(parts) > 1:
                for tag in parts[1:]:
                    tag_clean = tag.strip().lower()
                    if 'gallery' in tag_clean:
                        gallery_registry[func_name] = current_mod
                    if tag_clean == 'animation':
                        animation_registry.add(func_name)
                    elif tag_clean == 'animation-dep':
                        animation_dep_registry.add(func_name)

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

def detect_called_functions(cpp_code, current_mod_name):
    called_funcs_by_mod = {}
    for func, owner_mod in func_to_module.items():
        if owner_mod == current_mod_name:
            continue
        pattern = re.compile(rf'(?<![A-Za-z0-9_]){re.escape(func)}\s*\(')
        if pattern.search(cpp_code):
            if owner_mod not in called_funcs_by_mod:
                called_funcs_by_mod[owner_mod] = set()
            called_funcs_by_mod[owner_mod].add(func)
    return called_funcs_by_mod

def validate_js_syntax(js_path):
    result = subprocess.run(["node", "--check", js_path], capture_output=True, text=True)
    if result.returncode != 0:
        print(f"❌ JS SYNTAX VALIDATION ERROR in {js_path}:")
        print(result.stderr)
        sys.exit(1)
    else:
        print(f"  ✓ Syntax check passed (`node --check`) for {os.path.basename(js_path)}")

def check_circular_dependencies(dep_map, details_map):
    def dfs(node, visited, stack, path):
        visited.add(node)
        stack.add(node)
        path.append(node)
        for neighbor in dep_map.get(node, []):
            if neighbor not in visited:
                if dfs(neighbor, visited, stack, path):
                    return True
            elif neighbor in stack:
                cycle_start_idx = path.index(neighbor)
                cycle_path = path[cycle_start_idx:] + [neighbor]
                print("\n❌ FATAL CIRCULAR DEPENDENCY DETECTED:")
                print(f"   Cycle Path: {' ➔ '.join(cycle_path)}")
                print("\n   🔍 Function-Level Trigger Details:")
                for i in range(len(cycle_path) - 1):
                    src = cycle_path[i]
                    dst = cycle_path[i+1]
                    funcs = sorted(list(details_map.get(src, {}).get(dst, [])))
                    print(f"   • {src} calls in {dst}: {', '.join(funcs)}")
                print("")
                return True
        stack.remove(node)
        path.pop()
        return False

    visited = set()
    stack = set()
    for mod in dep_map:
        if mod not in visited:
            if dfs(mod, visited, stack, []):
                sys.exit(1)
    print("  ✓ Dependency DAG check passed (0 circular dependencies detected)")

def transpile_cpp_file(cpp_path, all_async_funcs, output_dir, generator_funcs=None):
    current_mod_name = os.path.basename(cpp_path).replace('.cpp', '.js')
    js_path = os.path.join(output_dir, current_mod_name)

    with open(cpp_path, 'r', encoding='utf-8') as f:
        code = f.read()

    top_imports = []
    seen_imports = set()
    asset_replacements = {}

    # Extract asset annotations (@DSL_EXTRACTED_MATRIX and @DSL_EXTRACTED_BACKGROUND)
    for line in code.splitlines():
        line_s = line.strip()
        if line_s.startswith("// @DSL_EXTRACTED_MATRIX"):
            parts = line_s.split()
            if len(parts) >= 4:
                var_name = parts[2]
                json_rel_path = parts[3]
                basename = os.path.basename(json_rel_path).replace('.json', '')
                import_alias = f"{basename}Data"
                
                import_stmt = f"import {import_alias} from './{json_rel_path}';"
                if import_stmt not in seen_imports:
                    seen_imports.add(import_stmt)
                    top_imports.append(import_stmt)
                
                asset_replacements[line_s] = f"const {var_name} = {import_alias}.matrix || {import_alias};"

        elif line_s.startswith("// @DSL_EXTRACTED_BACKGROUND"):
            parts = line_s.split()
            if len(parts) >= 4:
                bg_func = parts[2]
                json_rel_path = parts[3]
                basename = os.path.basename(json_rel_path).replace('.json', '')
                import_alias = f"{basename}Data"

                import_stmt = f"import {import_alias} from './{json_rel_path}';"
                if import_stmt not in seen_imports:
                    seen_imports.add(import_stmt)
                    top_imports.append(import_stmt)

                asset_replacements[line_s] = f"const letras = {import_alias}.letras; const arr = {import_alias}.colors || {import_alias}.arr;"

    called_mods = detect_called_functions(code, current_mod_name)
    for target_mod, funcs in called_mods.items():
        sorted_funcs = ", ".join(sorted(list(funcs)))
        top_imports.append(f"import {{ {sorted_funcs} }} from './{target_mod}';")

    # Isolated consoles: dsl -> gameConsole, dsl_gen -> animConsole (gallery overlay)
    if output_dir.endswith('dsl_gen'):
        console_import = "import { Console, ConsoleColor } from '../shims/animConsole.js';"
    else:
        console_import = "import { Console, ConsoleColor } from '../shims/gameConsole.js';"
    if console_import not in seen_imports:
        top_imports.append(console_import)
        seen_imports.add(console_import)

    # Apply asset replacements before AST parsing
    for k, v in asset_replacements.items():
        code = code.replace(k, v)
        
    js_code = CppToJsAST().parse(code, all_async_funcs=all_async_funcs, generator_funcs=generator_funcs)

    # For dsl/main, keep it as async (await runAnim) not async function* (yield*) for two-driver model
    if output_dir.endswith('/dsl') and current_mod_name == 'main.js' and 'export async function* main' in js_code:
        js_code = js_code.replace('export async function* main', 'export async function main')

    # If this file now needs runAnim (async caller calling generator), add import
    if "runAnim" in js_code and not any("runAnim" in imp for imp in top_imports):
        # Both src/dsl and src/dsl_gen are one level under src/, animationDriver is at src/animationDriver.js
        top_imports.append("import { runAnim } from '../animationDriver.js';")

    if top_imports:
        header_imports = "\n".join(top_imports) + "\n\n"
        js_code = header_imports + js_code

    with open(js_path, 'w', encoding='utf-8') as out_f:
        out_f.write(js_code + "\n")

    print(f"✅ Transpiled {os.path.basename(cpp_path)} ➔ web/src/{os.path.basename(output_dir)}/{os.path.basename(js_path)}")
    validate_js_syntax(js_path)
    return called_mods

def main():
    print("==================================================")
    print("🚀 Transpiling C++ DSL ➔ JavaScript ES Modules")
    print("==================================================")

    target_files = sorted([f for f in os.listdir(dsl_dir) if f.endswith('.cpp')])
    
    # 1. Combine all C++ code to resolve DAG async functions globally across all modules
    combined_cpp = []
    for f in target_files:
        with open(os.path.join(dsl_dir, f), 'r', encoding='utf-8') as cpp_f:
            combined_cpp.append(cpp_f.read())
    all_async_funcs = resolve_async_functions("\n".join(combined_cpp))
    print(f"▶ Resolved {len(all_async_funcs)} async functions across 14 DSL modules.")

    dep_map = {}
    details_map = {}

    for f in target_files:
        cpp_path = os.path.join(dsl_dir, f)
        mod_name = f.replace('.cpp', '.js')
        # dsl/main should stay async (await runAnim), not async function* (yield*), so exclude main from generator defs for dsl
        # Keep callees as generators for runAnim detection
        dsl_gen_for_calls = animation_registry
        dsl_gen_for_defs = set(x for x in animation_registry if x != "main")
        # For dsl, pass full set for call detection, but definitions for main stay async
        # Achieve by passing full set but handling main specially in transpiler via output_dir check
        called_mods = transpile_cpp_file(cpp_path, all_async_funcs, js_dir, generator_funcs=animation_registry)
        dep_map[mod_name] = list(called_mods.keys())
        details_map[mod_name] = called_mods

    check_circular_dependencies(dep_map, details_map)

    # 3. Second pass: Transpile only tagged modules to src/dsl_gen/ with generators
    js_gen_dir = os.path.join(web_dir, "src", "dsl_gen")
    # Wipe old _gen to remove previously generated unused modules
    if os.path.exists(js_gen_dir):
        shutil.rmtree(js_gen_dir)
    os.makedirs(js_gen_dir, exist_ok=True)
    
    for asset_dir in ["maps_json", "backgrounds_json"]:
        src_json = os.path.join(dsl_dir, asset_dir)
        dst_json = os.path.join(js_gen_dir, asset_dir)
        if os.path.exists(src_json):
            shutil.copytree(src_json, dst_json, dirs_exist_ok=True)

    # Only emit modules that have ≥1 #animation or #animation-dep (+ transitive deps)
    tagged_modules = set()
    for func in animation_registry.union(animation_dep_registry):
        mod = func_to_module.get(func)
        if mod:
            tagged_modules.add(mod)
    for mod in gallery_registry.values():
        if mod in tagged_modules or any(f in animation_registry for f in module_to_funcs.get(mod, [])):
            tagged_modules.add(mod)
    # Expand to include transitive dependencies of tagged modules
    # Use dep_map built for dsl (same imports)
    expanded = set(tagged_modules)
    queue = list(tagged_modules)
    while queue:
        cur = queue.pop()
        for dep in dep_map.get(cur, []):
            if dep not in expanded:
                expanded.add(dep)
                queue.append(dep)
    tagged_modules = expanded

    print(f"\n🚀 Transpiling Generator sandbox ➔ web/src/dsl_gen/ ({len(tagged_modules)} tagged+deps modules)")
    for f in target_files:
        mod_name = f.replace('.cpp', '.js')
        if mod_name not in tagged_modules:
            continue
        cpp_path = os.path.join(dsl_dir, f)
        transpile_cpp_file(cpp_path, all_async_funcs, js_gen_dir, generator_funcs=animation_registry)

    # Output gallery registry with static imports for bundlers
    gallery_path = os.path.join(js_dir, "gallery_registry.js")
    with open(gallery_path, 'w', encoding='utf-8') as f:
        # Group by module to generate clean imports
        mod_to_funcs = {}
        for func_name, mod_name in gallery_registry.items():
            if mod_name not in mod_to_funcs:
                mod_to_funcs[mod_name] = []
            mod_to_funcs[mod_name].append(func_name)
        
        # Write imports
        for mod_name, funcs in mod_to_funcs.items():
            f.write(f"import {{ {', '.join(funcs)} }} from './{mod_name}';\n")
            
        f.write("\nexport const GALLERY_FUNCTIONS = {\n")
        for func_name in gallery_registry.keys():
            f.write(f"  {func_name},\n")
        f.write("};\n")
        
    print(f"✅ Generated static gallery registry with {len(gallery_registry)} items.")

    # Output generator gallery registry for gallery-2 (only #animation #gallery)
    gen_gallery = {k: v for k, v in gallery_registry.items() if k in animation_registry}
    gen_gallery_path = os.path.join(js_gen_dir, "gallery_registry.js")
    with open(gen_gallery_path, 'w', encoding='utf-8') as f:
        mod_to_funcs = {}
        for func_name, mod_name in gen_gallery.items():
            if mod_name not in mod_to_funcs:
                mod_to_funcs[mod_name] = []
            mod_to_funcs[mod_name].append(func_name)
        for mod_name, funcs in mod_to_funcs.items():
            f.write(f"import {{ {', '.join(funcs)} }} from './{mod_name}';\n")
        f.write("\nexport const GALLERY_GEN_FUNCTIONS = {\n")
        for func_name in gen_gallery.keys():
            f.write(f"  {func_name},\n")
        f.write("};\n")
    print(f"✅ Generated generator gallery registry with {len(gen_gallery)} items (gallery-2).")

if __name__ == "__main__":
    main()
