import os
import re
import shutil
import sys
import subprocess
from ast_transpiler import CppToJsAST
from dag import resolve_async_functions, detect_called_functions, check_circular_dependencies

script_dir = os.path.dirname(os.path.abspath(__file__))
web_dir = os.path.dirname(script_dir)
repo_root = os.path.dirname(web_dir)

modules_dir = os.path.join(web_dir, "pushbox_modules")
js_dir = os.path.join(web_dir, "src", "generated")
rules_file = os.path.join(web_dir, "modules_manifest.txt")

os.makedirs(js_dir, exist_ok=True)

# JSON assets stay in web/pushbox_modules/ - no copy, imports use ../../pushbox_modules/

# Load function owner rules from modules_manifest.txt
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



def validate_js_syntax(js_path):
    result = subprocess.run(["node", "--check", js_path], capture_output=True, text=True)
    if result.returncode != 0:
        print(f"❌ JS SYNTAX VALIDATION ERROR in {js_path}:")
        print(result.stderr)
        sys.exit(1)
    else:
        print(f"  ✓ Syntax check passed (`node --check`) for {os.path.basename(js_path)}")


def transpile_cpp_file(cpp_path, all_async_funcs, output_dir, generator_funcs=None):
    current_mod_name = os.path.basename(cpp_path).replace('.cpp', '.js')
    js_path = os.path.join(output_dir, current_mod_name)

    with open(cpp_path, 'r', encoding='utf-8') as f:
        code = f.read()

    top_imports = []
    seen_imports = set()
    asset_replacements = {}

    # Extract asset annotations (@MODULE_EXTRACTED_MATRIX and @MODULE_EXTRACTED_BACKGROUND)
    for line in code.splitlines():
        line_s = line.strip()
        if line_s.startswith("// @MODULE_EXTRACTED_MATRIX"):
            parts = line_s.split()
            if len(parts) >= 4:
                var_name = parts[2]
                json_rel_path = parts[3]
                basename = os.path.basename(json_rel_path).replace('.json', '')
                import_alias = f"{basename}Data"
                
                # import from web/pushbox_modules via relative ../../pushbox_modules/
                rel = json_rel_path.lstrip('./')
                import_stmt = f"import {import_alias} from '../../pushbox_modules/{rel}';"
                if import_stmt not in seen_imports:
                    seen_imports.add(import_stmt)
                    top_imports.append(import_stmt)
                
                asset_replacements[line_s] = f"const {var_name} = {import_alias}.matrix || {import_alias};"

        elif line_s.startswith("// @MODULE_EXTRACTED_BACKGROUND"):
            parts = line_s.split()
            if len(parts) >= 4:
                bg_func = parts[2]
                json_rel_path = parts[3]
                basename = os.path.basename(json_rel_path).replace('.json', '')
                import_alias = f"{basename}Data"

                rel = json_rel_path.lstrip('./')
                import_stmt = f"import {import_alias} from '../../pushbox_modules/{rel}';"
                if import_stmt not in seen_imports:
                    seen_imports.add(import_stmt)
                    top_imports.append(import_stmt)

                asset_replacements[line_s] = f"const letras = {import_alias}.letras; const arr = {import_alias}.colors || {import_alias}.arr;"

    called_mods = detect_called_functions(code, current_mod_name, func_to_module)
    for target_mod, funcs in called_mods.items():
        sorted_funcs = ", ".join(sorted(list(funcs)))
        top_imports.append(f"import {{ {sorted_funcs} }} from './{target_mod}';")

    # Single canonical console (80x63 gameCanvas) for both generated and gallery
    console_import = "import { Console, ConsoleColor } from '../shims/gameConsole.js';"
    if console_import not in seen_imports:
        top_imports.append(console_import)
        seen_imports.add(console_import)

    # Apply asset replacements before AST parsing
    for k, v in asset_replacements.items():
        code = code.replace(k, v)
        
    js_code = CppToJsAST().parse(code, all_async_funcs=all_async_funcs, generator_funcs=generator_funcs)

    # For generated/main, keep it as async (await runAnim) not async function* (yield*) for two-driver model
    if output_dir.endswith('/generated') and current_mod_name == 'main.js' and 'export async function* main' in js_code:
        js_code = js_code.replace('export async function* main', 'export async function main')

    # If this file now needs runAnim (async caller calling generator), add import
    if "runAnim" in js_code and not any("runAnim" in imp for imp in top_imports):
        # Both src/generated paths are one level under src/, animationDriver is at src/animationDriver.js
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
    print("🚀 Transpiling C++ modules ➔ JavaScript ES Modules")
    print("==================================================")

    target_files = sorted([f for f in os.listdir(modules_dir) if f.endswith('.cpp')])
    
    # 1. Combine all C++ code to resolve DAG async functions globally across all modules
    combined_cpp = []
    for f in target_files:
        with open(os.path.join(modules_dir, f), 'r', encoding='utf-8') as cpp_f:
            combined_cpp.append(cpp_f.read())
    all_async_funcs = resolve_async_functions("\n".join(combined_cpp))
    print(f"▶ Resolved {len(all_async_funcs)} async functions across modules.")

    dep_map = {}
    details_map = {}

    for f in target_files:
        cpp_path = os.path.join(modules_dir, f)
        mod_name = f.replace('.cpp', '.js')
        # generated/main should stay async (await runAnim), not async function* (yield*), so exclude main from generator defs
        # Keep callees as generators for runAnim detection
        gen_for_calls = animation_registry
        gen_for_defs = set(x for x in animation_registry if x != "main")
        # For generated, pass full set for call detection, but definitions for main stay async
        # Achieve by passing full set but handling main specially in transpiler via output_dir check
        called_mods = transpile_cpp_file(cpp_path, all_async_funcs, js_dir, generator_funcs=animation_registry)
        dep_map[mod_name] = list(called_mods.keys())
        details_map[mod_name] = called_mods

    check_circular_dependencies(dep_map, details_map)

    # 3. Second pass: transpile only tagged modules to src/generated_anim/ (gallery subset)
    anim_js_dir = os.path.join(web_dir, "src", "generated_anim")
    if os.path.exists(anim_js_dir):
        shutil.rmtree(anim_js_dir)
    os.makedirs(anim_js_dir, exist_ok=True)

    # Determine tagged modules for gallery (animation ∩ gallery)
    tagged_modules = set()
    for func in animation_registry:
        mod = func_to_module.get(func)
        if mod:
            tagged_modules.add(mod)
    for mod in gallery_registry.values():
        if mod in tagged_modules or any(f in animation_registry for f in module_to_funcs.get(mod, [])):
            tagged_modules.add(mod)
    expanded = set(tagged_modules)
    queue = list(tagged_modules)
    while queue:
        cur = queue.pop()
        for dep in dep_map.get(cur, []):
            if dep not in expanded:
                expanded.add(dep)
                queue.append(dep)
    tagged_modules = expanded

    print(f"\n🚀 Transpiling gallery modules ➔ web/src/generated_anim/ ({len(tagged_modules)} modules)")
    for f in target_files:
        mod_name = f.replace('.cpp', '.js')
        if mod_name not in tagged_modules:
            continue
        cpp_path = os.path.join(modules_dir, f)
        transpile_cpp_file(cpp_path, all_async_funcs, anim_js_dir, generator_funcs=animation_registry)

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

    # Output generator gallery registry for gallery anim (only #animation #gallery) - in generated_anim
    gen_gallery = {k: v for k, v in gallery_registry.items() if k in animation_registry}
    # Append to main generated registry as well for single-import convenience
    with open(gallery_path, 'a', encoding='utf-8') as f:
        f.write("\n// Filtered for gallery animations only\n")
        f.write("export const GALLERY_GEN_FUNCTIONS = {\n")
        for func_name in gen_gallery.keys():
            f.write(f"  {func_name},\n")
        f.write("};\n")
    print(f"✅ Generated generator gallery registry with {len(gen_gallery)} items (gallery).")

    # Also write separate gallery anim registry in generated_anim for clean isolation
    anim_gallery_path = os.path.join(anim_js_dir, "gallery_registry.js")
    with open(anim_gallery_path, 'w', encoding='utf-8') as f:
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
        # Also export all gallery for completeness
        f.write("\nexport const GALLERY_FUNCTIONS = {\n")
        for func_name in gallery_registry.keys():
            f.write(f"  {func_name},\n")
        f.write("};\n")

if __name__ == "__main__":
    main()
