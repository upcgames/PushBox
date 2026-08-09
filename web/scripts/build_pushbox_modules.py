import os
import re
import json
import shutil
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))
web_dir = os.path.dirname(script_dir)
repo_root = os.path.dirname(web_dir)

source_file = os.path.join(repo_root, "Retro Push Box", "Source Code.cpp")
rules_file = os.path.join(web_dir, "modules_manifest.txt")
modules_dir = os.path.join(web_dir, "pushbox_modules")
json_dir = os.path.join(modules_dir, "maps_json")
bg_json_dir = os.path.join(modules_dir, "backgrounds_json")

def strip_comments(code_text):
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return ''
        return s
    
    cleaned = pattern.sub(replacer, code_text)
    cleaned = re.sub(r'\n\s*\n\s*\n+', '\n\n', cleaned)
    return cleaned

def extract_collision_data(world_data_content):
    collision_data = {
        "1": {"walls": [], "holes": [], "boxes": [], "voids": []},
        "2": {"walls": [], "holes": [], "boxes": [], "voids": []},
        "3": {"walls": [], "holes": [], "boxes": [], "voids": []},
        "4": {"walls": [], "holes": [], "boxes": [], "voids": []},
        "5": {"walls": [], "holes": [], "boxes": [], "voids": []}
    }

    ap_pattern = re.compile(r'ap\s*\(\s*matriz\s*\[\s*nivel\s*\]\s*,\s*\d+\s*,\s*(\d+)\s*,\s*(\d+)\s*\)')
    blocks = re.split(r'if\s*\(\s*nivel\s*==\s*(\d+)\s*\)', world_data_content)

    current_level = None
    for part in blocks:
        part_str = part.strip()
        if part_str in ["1", "2", "3", "4", "5"]:
            current_level = part_str
        elif current_level and "ap(" in part_str:
            walls = ap_pattern.findall(part_str)
            for w_x, w_y in walls:
                collision_data[current_level]["walls"].append([int(w_x), int(w_y)])
            current_level = None

    coord_pattern = re.compile(r'(matriz|Cajas)\[(?:nivel|\d+)\]\[\d+\]\[0\]\s*=\s*(\d+);\s*(?:matriz|Cajas)\[(?:nivel|\d+)\]\[\d+\]\[1\]\s*=\s*(\d+);')

    huecos_idx = world_data_content.find("void DataHuecos")
    if huecos_idx != -1:
        huecos_body = world_data_content[huecos_idx:]
        h_blocks = re.split(r'if\s*\(\s*nivel\s*==\s*(\d+)\s*\)', huecos_body)
        curr_lvl = None
        for part in h_blocks:
            part_str = part.strip()
            if part_str in ["1", "2", "3", "4", "5"]:
                curr_lvl = part_str
            elif curr_lvl:
                coords = coord_pattern.findall(part_str)
                for _, c_x, c_y in coords:
                    collision_data[curr_lvl]["holes"].append([int(c_x), int(c_y)])
                curr_lvl = None

    cajas_idx = world_data_content.find("void DataICajas")
    if cajas_idx != -1:
        cajas_body = world_data_content[cajas_idx:huecos_idx if huecos_idx != -1 else len(world_data_content)]
        c_blocks = re.split(r'if\s*\(\s*nivel\s*==\s*(\d+)\s*\)', cajas_body)
        curr_lvl = None
        for part in c_blocks:
            part_str = part.strip()
            if part_str in ["1", "2", "3", "4", "5"]:
                curr_lvl = part_str
            elif curr_lvl:
                coords = coord_pattern.findall(part_str)
                for _, c_x, c_y in coords:
                    collision_data[curr_lvl]["boxes"].append([int(c_x), int(c_y)])
                curr_lvl = None

    return collision_data

def main():
    print("==================================================")
    print("🚀 PushBox modules Extractor & Disassembler Pipeline")
    print("==================================================")

    if not os.path.exists(source_file):
        print(f"❌ Fatal Error: Source file not found at {source_file}")
        sys.exit(1)

    if not os.path.exists(rules_file):
        print(f"❌ Fatal Error: Manifest file not found at {rules_file}")
        sys.exit(1)

    os.makedirs(modules_dir, exist_ok=True)
    os.makedirs(json_dir, exist_ok=True)
    os.makedirs(bg_json_dir, exist_ok=True)

    with open(source_file, 'r', encoding='utf-8', errors='ignore') as f:
        raw_content = f.read()

    print("▶ Stripping comments from source code in memory...")
    content = strip_comments(raw_content)

    rules = {}
    current_target_file = None
    with open(rules_file, 'r', encoding='utf-8') as f:
        for line in f:
            line_str = line.strip()
            if not line_str:
                continue
            if line_str.startswith("#"):
                current_target_file = line_str[1:].strip()
            elif current_target_file:
                func_name = line_str.split('#')[0].strip()
                rules[func_name] = current_target_file

    print(f"▶ Loaded {len(rules)} function mapping rules for {len(set(rules.values()))} modules files.")

    matrix_pattern = re.compile(
        r'int\s+([A-Za-z0-9_]+)\s*\[\s*(\d+)\s*\]\s*\[\s*(\d+)\s*\]\s*=\s*'
        r'\{(.*?)\}\s*;',
        re.DOTALL
    )
    func_def_pattern = re.compile(r'void\s+([A-Za-z0-9_]+)\s*\([^)]*\)')

    func_matches = list(func_def_pattern.finditer(content))
    decl_matches = list(matrix_pattern.finditer(content))

    warnings = []
    errors = []
    replacements = []
    func_matrix_counts = {}

    for decl in decl_matches:
        var_name = decl.group(1)
        decl_rows = int(decl.group(2))
        decl_cols = int(decl.group(3))
        raw_array_body = decl.group(4)
        start_pos = decl.start()
        end_pos = decl.end()

        enclosing_func = "global"
        for f in func_matches:
            if f.start() < start_pos:
                enclosing_func = f.group(1)
            else:
                break

        func_matrix_counts[enclosing_func] = func_matrix_counts.get(enclosing_func, 0) + 1
        suffix = f"_{func_matrix_counts[enclosing_func]}" if func_matrix_counts[enclosing_func] > 1 else ""
        json_name = f"{enclosing_func}{suffix}"

        func_warnings = []
        row_pattern = re.compile(r'\{\s*([0-9\s, -]+)\s*\}')
        row_matches = row_pattern.findall(raw_array_body)
        parsed_matrix = []

        for r_idx, row_str in enumerate(row_matches):
            items = [int(x.strip()) for x in row_str.split(',') if x.strip() != '']
            if len(items) != decl_cols:
                w_msg = f"[{json_name}::{var_name}] Row {r_idx}: expected {decl_cols} cols, got {len(items)}"
                warnings.append(w_msg)
                func_warnings.append(w_msg)
                while len(items) < decl_cols:
                    items.append(items[-1] if items else 0)
            parsed_matrix.append(items)

        if len(parsed_matrix) != decl_rows:
            errors.append(f"[{json_name}::{var_name}] Row count mismatch: expected {decl_rows}, got {len(parsed_matrix)}")

        json_path = os.path.join(json_dir, f"{json_name}.json")
        matrix_data = {
            "function": enclosing_func,
            "variable": var_name,
            "rows": len(parsed_matrix),
            "cols": decl_cols,
            "warnings": func_warnings,
            "matrix": parsed_matrix
        }
        with open(json_path, 'w', encoding='utf-8') as jf:
            json.dump(matrix_data, jf, indent=2)

        replacements.append({
            "start_char": start_pos,
            "end_char": end_pos,
            "comment": f"// @MODULE_EXTRACTED_MATRIX {var_name} maps_json/{json_name}.json"
        })

    # Background asset extraction: (Fondo01..Fondo05)
    bg_func_pattern = re.compile(
        r'void\s+(Fondo\d+)\s*\(\s*\)\s*\{'
        r'\s*string\s+letras\s*=\s*"([^"]*)";'
        r'\s*int\s+arr\s*\[\s*\d+\s*\]\s*=\s*\{([^}]+)\};',
        re.DOTALL
    )

    bg_matches = list(bg_func_pattern.finditer(content))
    for bg in bg_matches:
        fondo_name = bg.group(1)
        raw_letras = bg.group(2)
        raw_colors = bg.group(3)

        colors_list = [int(x.strip()) for x in raw_colors.split(',') if x.strip()]

        bg_data = {
            "function": fondo_name,
            "letras": raw_letras,
            "colors": colors_list
        }

        bg_json_path = os.path.join(bg_json_dir, f"{fondo_name}.json")
        with open(bg_json_path, 'w', encoding='utf-8') as bjf:
            json.dump(bg_data, bjf, indent=2)

        # Replace internal string/arr body with marker comment
        bg_start = bg.start() + len(f"void {fondo_name}()\n{{")
        # find end of arr declaration
        arr_end = bg.start() + bg.group(0).find("};") + 2
        replacements.append({
            "start_char": bg_start,
            "end_char": arr_end,
            "comment": f"\n\t// @MODULE_EXTRACTED_BACKGROUND {fondo_name} backgrounds_json/{fondo_name}.json\n"
        })

    col_data = extract_collision_data(content)
    col_path = os.path.join(json_dir, "collision_data.json")
    with open(col_path, 'w', encoding='utf-8') as cjf:
        json.dump(col_data, cjf, indent=2)

    if warnings:
        print("\n⚠️ MATRIX EXTRACTOR WARNINGS:")
        for w in warnings:
            print(f"  ⚠️ {w}")

    if errors:
        print("\n❌ FATAL MATRIX EXTRACTOR ERRORS:")
        for e in errors:
            print(f"  ❌ {e}")
        sys.exit(1)

    print(f"▶ Extracted {len(decl_matches)} matrices + {len(bg_matches)} backgrounds + collision_data.json to web/pushbox_modules/")

    # Sort replacements by start_char in reverse order so character indices remain valid
    replacements.sort(key=lambda x: x['start_char'], reverse=True)

    clean_content = content
    for rep in replacements:
        start = rep['start_char']
        end = rep['end_char']
        comment = rep['comment']
        clean_content = clean_content[:start] + comment + clean_content[end:]

    func_header_pattern = re.compile(
        r'((?:void|int|bool|char|float|double|long|unsigned|short)\s+([A-Za-z0-9_]+)\s*\([^)]*\)\s*\{)'
    )

    matches = list(func_header_pattern.finditer(clean_content))
    file_buffers = {}
    extracted_count = 0
    missing_rules = []

    for match in matches:
        func_name = match.group(2)
        start_pos = match.start(1)

        brace_count = 0
        in_curly = False
        end_pos = start_pos

        for idx in range(start_pos, len(clean_content)):
            ch = clean_content[idx]
            if ch == '{':
                brace_count += 1
                in_curly = True
            elif ch == '}':
                brace_count -= 1
                if in_curly and brace_count == 0:
                    end_pos = idx + 1
                    break

        func_body = clean_content[start_pos:end_pos].strip()

        target_file = rules.get(func_name)
        if not target_file:
            missing_rules.append(func_name)
        else:
            if target_file not in file_buffers:
                file_buffers[target_file] = []
            file_buffers[target_file].append(func_body)
            extracted_count += 1

    if len(rules) != extracted_count or missing_rules:
        print(f"\n❌ FATAL COVERAGE ERROR: Expected {len(rules)} functions, extracted {extracted_count}.")
        if missing_rules:
            print(f"Missing modules rules for: {missing_rules}")
        sys.exit(1)

    for target_filename, func_bodies in file_buffers.items():
        out_path = os.path.join(modules_dir, target_filename)
        with open(out_path, 'w', encoding='utf-8') as out_f:
            out_f.write("\n\n".join(func_bodies) + "\n")

    print("\n==================================================")
    print("✅ PUSHBOX modules PIPELINE COMPLETED SUCCESSFULLY!")
    print("==================================================")
    print(f"  • Matrices extracted: {len(decl_matches)} JSONs + collision_data.json in web/pushbox_modules/maps_json/")
    print(f"  • Backgrounds extracted: {len(bg_matches)} JSONs in web/pushbox_modules/backgrounds_json/")
    print(f"  • Modular modules files generated: {len(file_buffers)} files inside web/pushbox_modules/")

if __name__ == "__main__":
    main()
