import re

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

def detect_called_functions(cpp_code, current_mod_name, func_to_module):
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
                import sys
                sys.exit(1)
    print("  ✓ Dependency DAG check passed (0 circular dependencies detected)")
