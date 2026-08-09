import tree_sitter_cpp
from tree_sitter import Language, Parser

class CppToJsAST:
    def __init__(self):
        self.language = Language(tree_sitter_cpp.language())
        self.parser = Parser(self.language)
        # Pre-populate with known game functions for isolated tests
        self.symbol_table = {
            "MenuPrincipal": [0],
            "InterfazPausa": [1, 2],
            "BuscarLetra": [1, 2, 3, 4],
            "guardarpos": [0, 1],
            "movi": [0, 1],
            "movinv": [0],
            "GuardarPosicion": [0],
            "Regresar": [1, 2, 3],
            "ControlDeMovimiento": [0, 1, 11],
            "ControlDeNiveles": [1]
        }

    def parse_symbols(self, cpp_code: str):
        """Pass 1: Build the symbol table of reference parameters."""
        code_bytes = cpp_code.encode('utf-8')
        tree = self.parser.parse(code_bytes)
        self._walk_for_symbols(tree.root_node, code_bytes)

    def _walk_for_symbols(self, node, code_bytes):
        if node.type == 'function_definition':
            # Find function_declarator
            for child in node.children:
                if child.type == 'function_declarator':
                    self._extract_func_symbols(child, code_bytes)
        
        for child in node.children:
            self._walk_for_symbols(child, code_bytes)

    def _extract_func_symbols(self, declarator_node, code_bytes):
        func_name = None
        params_node = None
        for child in declarator_node.children:
            if child.type == 'identifier':
                func_name = code_bytes[child.start_byte:child.end_byte].decode('utf-8')
            elif child.type == 'parameter_list':
                params_node = child
        
        if func_name and params_node:
            ref_indices = []
            param_idx = 0
            for child in params_node.children:
                if child.type == 'parameter_declaration':
                    # Check if it has a reference_declarator
                    is_ref = False
                    for p_child in child.children:
                        if p_child.type == 'reference_declarator':
                            is_ref = True
                    if is_ref:
                        ref_indices.append(param_idx)
                    param_idx += 1
            
            if ref_indices:
                self.symbol_table[func_name] = ref_indices

    def parse(self, cpp_code: str, all_async_funcs: set = None, generator_funcs: set = None) -> str:
        """Pass 2: Safely apply Reference transformations using AST byte-offsets."""
        if all_async_funcs is None:
            all_async_funcs = set()
            
        # Ensure we parse symbols for the current snippet (for self-contained tests)
        self.parse_symbols(cpp_code)
        
        code_bytes = cpp_code.encode('utf-8')
        tree = self.parser.parse(code_bytes)
        
        edits = [] # list of (start_byte, end_byte, new_string)
        self._walk_for_edits(tree.root_node, code_bytes, edits, current_func_refs=set(), all_async_funcs=all_async_funcs, generator_funcs=generator_funcs)
        
        # Apply edits in reverse order so byte offsets remain valid
        edits.sort(key=lambda x: x[0], reverse=True)
        
        for start, end, new_text in edits:
            code_bytes = code_bytes[:start] + new_text.encode('utf-8') + code_bytes[end:]
            
        final_str = code_bytes.decode('utf-8')
        
        # Fallback regex for `new int*[N]` and `new int[N]` because AST parsing for pointers is messy
        import re
        final_str = re.sub(r'\bnew\s+(?:int|bool|char|float|double|long|short)\s*\*+\s*\[\s*([^\]]+)\s*\]', r'new Array(\1)', final_str)
        final_str = re.sub(r'\bnew\s+(?:int|bool|char|float|double|long|short)\s*\[\s*([^\]]+)\s*\]', r'new Array(\1)', final_str)
        
        # Fallback regex for stripping C++ address-of operator & in function call argument lists (&csbi -> csbi)
        final_str = re.sub(r'(?<=[(,\s])&([A-Za-z0-9_]+)', r'\1', final_str)
        
        return final_str

    def _walk_for_edits(self, node, code_bytes, edits, current_func_refs, skip_node_ids=None, all_async_funcs=None, generator_funcs=None, is_inside_generator=False, is_current_async=False):
        if skip_node_ids is None:
            skip_node_ids = set()
        if all_async_funcs is None:
            all_async_funcs = set()
        if generator_funcs is None:
            generator_funcs = set()
            
        if node.type == 'function_definition':
            # Check if this function has reference parameters we need to track internally
            func_name = None
            params_node = None
            declarator = None
            for child in node.children:
                if child.type == 'function_declarator':
                    declarator = child
            
            if declarator:
                for child in declarator.children:
                    if child.type == 'identifier':
                        func_name = code_bytes[child.start_byte:child.end_byte].decode('utf-8')
                    elif child.type == 'parameter_list':
                        params_node = child
            
            my_refs = set()
            if params_node:
                for child in params_node.children:
                    if child.type == 'parameter_declaration':
                        for p_child in child.children:
                            if p_child.type == 'reference_declarator':
                                # extract the identifier inside the reference_declarator
                                for r_child in p_child.children:
                                    if r_child.type == 'identifier':
                                        var_name = code_bytes[r_child.start_byte:r_child.end_byte].decode('utf-8')
                                        my_refs.add(var_name)
                                        
            # Rewrite function header: void foo(int x) -> export function foo(x)
            # Find the return type and parameter types to strip them
            for child in node.children:
                if child.type == 'primitive_type' or child.type == 'type_identifier':
                    # Strip return type
                    edits.append((child.start_byte, child.end_byte, ""))
            
            # Change the function name to add `export [async] function`
            if declarator:
                for child in declarator.children:
                    if child.type == 'identifier':
                        is_async = func_name in all_async_funcs
                        is_gen = func_name in generator_funcs
                        if is_gen and is_async:
                            export_kw = "export async function*"
                        elif is_gen:
                            export_kw = "export function*"
                        else:
                            export_kw = "export async function" if is_async else "export function"
                        # Instead of replacing just the name, we prepend the export keyword
                        edits.append((child.start_byte, child.start_byte, f"{export_kw} "))
                    elif child.type == 'parameter_list':
                        # Clean parameter types
                        for pchild in child.children:
                            if pchild.type == 'parameter_declaration' or pchild.type == 'optional_parameter_declaration':
                                # Strip primitive_type, type_identifier, and pointers/references
                                for gchild in pchild.children:
                                    if gchild.type in ['primitive_type', 'type_identifier', 'type_qualifier', 'const']:
                                        edits.append((gchild.start_byte, gchild.end_byte, ""))
                                    elif gchild.type == 'pointer_declarator' or gchild.type == 'reference_declarator':
                                        # Recursively strip * and &
                                        def strip_ptr_ref(n):
                                            for c in n.children:
                                                if c.type == '*' or c.type == '&':
                                                    edits.append((c.start_byte, c.end_byte, ""))
                                                else:
                                                    strip_ptr_ref(c)
                                        strip_ptr_ref(gchild)
            
            # Recurse into the function body with the known references
            for child in node.children:
                if func_name == "getDevConfig" and child.type == 'compound_statement':
                    edits.append((child.start_byte, child.end_byte, "{ return window.getDevConfig(key); }"))
                    continue
                self._walk_for_edits(child, code_bytes, edits, my_refs, skip_node_ids, all_async_funcs, generator_funcs, is_inside_generator=(func_name in generator_funcs), is_current_async=(func_name in all_async_funcs))
            return # skip normal recursion since we handled it

        elif node.type == 'call_expression':
            # Detect calls to functions in our symbol table and wrap primitive arguments
            func_name_node = node.children[0]
            if func_name_node.type in ['identifier', 'primitive_type', 'type_identifier']:
                func_name = code_bytes[func_name_node.start_byte:func_name_node.end_byte].decode('utf-8')
                if func_name in self.symbol_table:
                    ref_indices = self.symbol_table[func_name]
                    args_node = node.children[1] # argument_list
                    if args_node and args_node.type == 'argument_list':
                        # Count the actual arguments (skip parentheses and commas)
                        args = [c for c in args_node.children if c.type not in ['(', ')', ',']]
                        
                        wrapper_setup = []
                        wrapper_teardown = []
                        has_wrapped = False
                        
                        for idx in ref_indices:
                            if idx < len(args):
                                arg_node = args[idx]
                                arg_str = code_bytes[arg_node.start_byte:arg_node.end_byte].decode('utf-8')
                                
                                # If the argument is already a reference parameter in the current scope, don't wrap it!
                                if arg_str in current_func_refs:
                                    # Tell the walker NOT to append .v to this node!
                                    skip_node_ids.add(arg_node.id)
                                    continue
                                
                                ref_var = f"_r{idx}"
                                wrapper_setup.append(f"let {ref_var} = new Ref({arg_str});")
                                # We replace the argument string inline for the call
                                edits.append((arg_node.start_byte, arg_node.end_byte, ref_var))
                                wrapper_teardown.append(f"{arg_str} = {ref_var}.v;")
                                has_wrapped = True
                        
                        if has_wrapped:
                            setup_str = " ".join(wrapper_setup)
                            teardown_str = " ".join(wrapper_teardown)
                            
                            is_async = func_name in all_async_funcs
                            is_gen_target = func_name in generator_funcs
                            if is_gen_target and is_inside_generator:
                                edits.append((node.start_byte, node.start_byte, f"yield* (function* () {{ {setup_str} yield* "))
                                edits.append((node.end_byte, node.end_byte, f"; {teardown_str} }})()"))
                            elif is_gen_target and not is_inside_generator:
                                # Caller is not a generator - emit plain call (no yield*) to keep file parsable
                                edits.append((node.start_byte, node.start_byte, f"(() => {{ {setup_str} "))
                                edits.append((node.end_byte, node.end_byte, f"; {teardown_str} }})()"))
                            elif is_async:
                                # Wrap the entire call_expression with async/await
                                edits.append((node.start_byte, node.start_byte, f"await (async () => {{ {setup_str} await "))
                                edits.append((node.end_byte, node.end_byte, f"; {teardown_str} }})()"))
                            else:
                                edits.append((node.start_byte, node.start_byte, f"(() => {{ {setup_str} "))
                                edits.append((node.end_byte, node.end_byte, f"; {teardown_str} }})()"))
                        else:
                            # Not wrapped, but might still need await or yield!
                            if func_name in generator_funcs and is_inside_generator:
                                edits.append((node.start_byte, node.start_byte, "yield* "))
                            elif func_name in generator_funcs and not is_inside_generator:
                                if is_current_async:
                                    # Caller async, callee generator -> await runAnim(func, args) e.g. PixelmenGif(matriz) -> await runAnim(PixelmenGif, matriz)
                                    args_node = node.children[1] if len(node.children) > 1 and node.children[1].type == 'argument_list' else None
                                    if args_node:
                                        args_text = code_bytes[args_node.start_byte+1:args_node.end_byte-1].decode('utf-8').strip()
                                        if args_text:
                                            edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name}, {args_text})"))
                                        else:
                                            edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name})"))
                                    else:
                                        edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name})"))
                                else:
                                    pass # plain call - keep parsable when caller is not a generator
                            elif func_name in all_async_funcs:
                                if func_name == "Sleep" and is_inside_generator:
                                    edits.append((node.start_byte, func_name_node.end_byte, "yield"))
                                else:
                                    edits.append((node.start_byte, node.start_byte, "await "))
                    else:
                        if func_name in generator_funcs and is_inside_generator:
                            edits.append((node.start_byte, node.start_byte, "yield* "))
                        elif func_name in generator_funcs and not is_inside_generator and is_current_async:
                            args_node2 = node.children[1] if len(node.children) > 1 and node.children[1].type == 'argument_list' else None
                            if args_node2:
                                args_text2 = code_bytes[args_node2.start_byte+1:args_node2.end_byte-1].decode('utf-8').strip()
                                if args_text2:
                                    edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name}, {args_text2})"))
                                else:
                                    edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name})"))
                            else:
                                edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name})"))
                        elif func_name in all_async_funcs:
                            if func_name == "Sleep" and is_inside_generator:
                                edits.append((node.start_byte, func_name_node.end_byte, "yield"))
                            else:
                                edits.append((node.start_byte, node.start_byte, "await "))
                elif func_name == 'int':
                    # Type cast: int(x) -> Number(x)
                    edits.append((func_name_node.start_byte, func_name_node.end_byte, "Number"))
                elif func_name == 'char':
                    edits.append((func_name_node.start_byte, func_name_node.end_byte, "String.fromCharCode"))
                else:
                    # Normal function call, just check if it needs await or yield
                    if func_name in generator_funcs and is_inside_generator:
                        edits.append((node.start_byte, node.start_byte, "yield* "))
                    elif func_name in generator_funcs and not is_inside_generator and is_current_async:
                        args_node3 = node.children[1] if len(node.children) > 1 and node.children[1].type == 'argument_list' else None
                        if args_node3:
                            args_text3 = code_bytes[args_node3.start_byte+1:args_node3.end_byte-1].decode('utf-8').strip()
                            if args_text3:
                                edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name}, {args_text3})"))
                            else:
                                edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name})"))
                        else:
                            edits.append((node.start_byte, node.end_byte, f"await runAnim({func_name})"))
                    elif func_name in all_async_funcs:
                        if func_name == "Sleep" and is_inside_generator:
                            edits.append((node.start_byte, func_name_node.end_byte, "yield"))
                        else:
                            edits.append((node.start_byte, node.start_byte, "await "))
            elif func_name_node.type == 'field_expression':
                field_str = code_bytes[func_name_node.start_byte:func_name_node.end_byte].decode('utf-8')
                if field_str.endswith('.length'):
                    # Convert `.length()` to `.length` by removing the `()` 
                    # The `()` is represented by everything from the end of the field_expression to the end of the call_expression
                    edits.append((func_name_node.end_byte, node.end_byte, ""))
            
            # Check for `cout << ...`
            # In tree-sitter C++, cout << x is a call_expression to operator<<
            # But sometimes it's parsed as a binary_expression if not fully typed.
            pass

        elif node.type == 'binary_expression':
            left = node.children[0]
            op = node.children[1]
            right = node.children[2]
            if op.type == '<<':
                def is_cout_chain(n):
                    if n.type == 'identifier':
                        return code_bytes[n.start_byte:n.end_byte].decode('utf-8').strip() == 'cout'
                    elif n.type == 'binary_expression' and len(n.children) >= 3 and n.children[1].type == '<<':
                        return is_cout_chain(n.children[0])
                    return False
                
                if is_cout_chain(left):
                    if left.type == 'identifier':
                        edits.append((left.start_byte, op.end_byte, "Console.Write("))
                        edits.append((right.end_byte, right.end_byte, ")"))
                    else:
                        edits.append((op.start_byte, op.end_byte, ".Write("))
                        edits.append((right.end_byte, right.end_byte, ")"))
                    self._walk_for_edits(left, code_bytes, edits, current_func_refs, skip_node_ids, all_async_funcs, generator_funcs, is_inside_generator, is_current_async)
                    self._walk_for_edits(right, code_bytes, edits, current_func_refs, skip_node_ids, all_async_funcs, generator_funcs, is_inside_generator, is_current_async)
                    return
            elif op.type == '/':
                    # C++ int / int trunc → JS Math.floor for all / (PushBox uses only int)
                    edits.append((node.start_byte, node.start_byte, "Math.floor("))
                    edits.append((node.end_byte, node.end_byte, ")"))
                    self._walk_for_edits(left, code_bytes, edits, current_func_refs, skip_node_ids, all_async_funcs, generator_funcs, is_inside_generator, is_current_async)
                    self._walk_for_edits(right, code_bytes, edits, current_func_refs, skip_node_ids, all_async_funcs, generator_funcs, is_inside_generator, is_current_async)
                    return

        elif node.type == 'new_expression':
            pass # We will handle new expressions globally with regex since C++ new int*[136] is hard to parse in JS

        elif node.type == 'delete_expression':
            # delete[] matriz; -> ; /* delete[] matriz */
            edits.append((node.start_byte, node.end_byte, f"; /* {code_bytes[node.start_byte:node.end_byte].decode('utf-8')} */"))
            return

        elif node.type == 'declaration':
            # Handle Random r; -> let r = new Random();
            # Handle int x -> let x
            # Handle string s = "hello" -> const s = "hello"
            decl_type = node.children[0]
            type_str = code_bytes[decl_type.start_byte:decl_type.end_byte].decode('utf-8')
            
            if type_str == 'Random':
                # Random r;
                var_name = code_bytes[node.children[1].start_byte:node.children[1].end_byte].decode('utf-8')
                edits.append((node.start_byte, node.end_byte, f"let {var_name} = new Random();"))
                return
            elif type_str == 'string':
                edits.append((decl_type.start_byte, decl_type.end_byte, "const"))
            elif type_str in ['int', 'bool', 'char', 'float', 'double', 'long', 'short', 'WORD', 'CONSOLE_SCREEN_BUFFER_INFO']:
                edits.append((decl_type.start_byte, decl_type.end_byte, "let"))
                
            # Strip pointers anywhere inside the declaration
            def strip_ptr(n):
                for c in n.children:
                    if c.type == '*':
                        edits.append((c.start_byte, c.end_byte, ""))
                    else:
                        strip_ptr(c)
            strip_ptr(node)

        elif node.type == 'qualified_identifier':
            # :: -> .
            for child in node.children:
                if child.type == '::':
                    edits.append((child.start_byte, child.end_byte, "."))
                    
        elif node.type == 'unary_expression':
            # &var -> var
            if node.children[0].type == '&':
                edits.append((node.children[0].start_byte, node.children[0].end_byte, ""))

        elif node.type == 'string_literal':
            # Octal escape \242 -> \xA2
            val = code_bytes[node.start_byte:node.end_byte].decode('utf-8')
            import re
            new_val = re.sub(r'\\([0-7]{3})', lambda m: f'\\x{int(m.group(1), 8):02x}', val)
            if val != new_val:
                edits.append((node.start_byte, node.end_byte, new_val))

        elif node.type == 'identifier':
            # Check if this identifier is a reference variable used in the body
            var_name = code_bytes[node.start_byte:node.end_byte].decode('utf-8')
            if var_name == 'TRUE':
                edits.append((node.start_byte, node.end_byte, "true"))
            elif var_name == 'FALSE':
                edits.append((node.start_byte, node.end_byte, "false"))
            elif var_name in ['NULL', 'nullptr']:
                edits.append((node.start_byte, node.end_byte, "null"))
            elif var_name in current_func_refs:
                pass # Handled below with context

        # As a fallback for TRUE/NULL inside declarations, tree-sitter sometimes parses them differently.
        # Let's do a quick global check on the node text if it's a leaf node.
        if len(node.children) == 0:
            text = code_bytes[node.start_byte:node.end_byte].decode('utf-8')
            if text == 'TRUE':
                edits.append((node.start_byte, node.end_byte, "true"))
            elif text == 'FALSE':
                edits.append((node.start_byte, node.end_byte, "false"))
            elif text in ['NULL', 'nullptr']:
                edits.append((node.start_byte, node.end_byte, "null"))

        # Recursive walk
        for child in node.children:
            if child.id in skip_node_ids:
                continue
                
            # Skip replacing '.v' inside the parameter_list declaration itself
            if child.type == 'parameter_list':
                continue
            
            # Simple AST identifier replacement for .v
            if child.type == 'identifier':
                var_name = code_bytes[child.start_byte:child.end_byte].decode('utf-8')
                if var_name in current_func_refs:
                    edits.append((child.start_byte, child.end_byte, f"{var_name}.v"))
            else:
                self._walk_for_edits(child, code_bytes, edits, current_func_refs, skip_node_ids, all_async_funcs, generator_funcs, is_inside_generator, is_current_async)
