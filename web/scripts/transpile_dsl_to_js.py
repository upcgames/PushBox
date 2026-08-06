import os
import re
import shutil
import sys
import subprocess
from transpiler_core import transpile_cpp_to_js, resolve_async_functions

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
            func_to_module[line_str] = current_mod
            module_to_funcs[current_mod].add(line_str)

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

def transpile_cpp_file(cpp_path, all_async_funcs):
    current_mod_name = os.path.basename(cpp_path).replace('.cpp', '.js')
    js_path = os.path.join(js_dir, current_mod_name)

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

    js_code = transpile_cpp_to_js(code, asset_replacements=asset_replacements, all_async_funcs=all_async_funcs)

    if top_imports:
        header_imports = "\n".join(top_imports) + "\n\n"
        js_code = header_imports + js_code

    with open(js_path, 'w', encoding='utf-8') as out_f:
        out_f.write(js_code + "\n")

    print(f"✅ Transpiled {os.path.basename(cpp_path)} ➔ web/src/dsl/{os.path.basename(js_path)}")
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
        called_mods = transpile_cpp_file(cpp_path, all_async_funcs)
        dep_map[mod_name] = list(called_mods.keys())
        details_map[mod_name] = called_mods

    check_circular_dependencies(dep_map, details_map)

if __name__ == "__main__":
    main()
