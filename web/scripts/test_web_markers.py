import unittest

from ast_transpiler import CppToJsAST
from build_pushbox_modules import strip_comments


class WebMarkerTests(unittest.TestCase):
    def test_markers_survive_comment_stripping_and_transpilation(self):
        source = '''void Example() {
// Ordinary comment
// @web:begin congratulations-prompts
// @web:event movement-rejected
Escribir("New prompt wording", 100, 2);
// @web:end congratulations-prompts
}'''
        cleaned = strip_comments(source)
        self.assertNotIn("Ordinary comment", cleaned)
        generated = CppToJsAST().parse(cleaned, all_async_funcs={"Example", "Escribir"})
        for marker in ["// @web:begin congratulations-prompts", "// @web:end congratulations-prompts",
                       "// @web:event movement-rejected"]:
            self.assertIn(marker, cleaned)
            self.assertIn(marker, generated)

    def test_comment_like_strings_remain_literal(self):
        source = 'void Example() { Escribir("// @web:begin fake"); /* ordinary */ }'
        cleaned = strip_comments(source)
        self.assertIn('"// @web:begin fake"', cleaned)
        self.assertNotIn("ordinary", cleaned)


if __name__ == "__main__":
    unittest.main()
