import tree_sitter_cpp
from tree_sitter import Language, Parser

# Initialize the parser
LANGUAGE = Language(tree_sitter_cpp.language())
parser = Parser(LANGUAGE)

cpp_code = b"""
void movi(int &x, int &y, int mov) {
    x++;
}

bool MovilyCaja(int mx, int my, int mov) {
    movi(mx, my, mov);
    return false;
}
"""

tree = parser.parse(cpp_code)
root_node = tree.root_node

def print_tree(node, indent=0):
    # Print the current node's type and name if available
    name = getattr(node, "name", "") 
    
    # Try to extract text if it's an identifier or primitive
    text = ""
    if node.type in ["identifier", "primitive_type", "number_literal"]:
        text = cpp_code[node.start_byte:node.end_byte].decode('utf-8')
        print("  " * indent + f"[{node.type}] -> '{text}'")
    else:
        print("  " * indent + f"[{node.type}]")
        
    for child in node.children:
        print_tree(child, indent + 1)

print("Parsed C++ AST Tree:")
print("="*40)
print_tree(root_node)
