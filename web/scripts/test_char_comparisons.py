import json
import subprocess
import unittest

from ast_transpiler import CppToJsAST


class CharComparisonTests(unittest.TestCase):
    def evaluate(self, source, expression):
        generated = CppToJsAST().parse(source)
        result = subprocess.run(
            ["node", "--input-type=module", "-e", generated + "\nconsole.log(JSON.stringify(" + expression + "));"],
            capture_output=True, text=True, check=True,
        )
        return json.loads(result.stdout)

    def test_digits_letters_and_unsupported_ascii_use_character_codes(self):
        source = '''bool Valid(char *name) {
          return (name[0] >= 48 && name[0] <= 57) ||
                 (name[0] >= 65 && name[0] <= 90) ||
                 (name[0] >= 97 && name[0] <= 122);
        }'''
        self.assertEqual(self.evaluate(source, "['0','3','9','A','z','$','!',' '].map(c => Valid([c]))"),
                         [True, True, True, True, True, False, False, False])

    def test_signed_cp850_bytes_remain_numbers_and_literal_checks_keep_strings(self):
        source = "bool Check(char c) { return c == -126 || c == -91 || c == '3'; }"
        self.assertEqual(self.evaluate(source, "[-126,-91,'3','a',String.fromCharCode(130)].map(Check)"),
                         [True, True, True, False, True])

    def test_int_shadowing_and_other_functions_do_not_inherit_char_type(self):
        source = '''int First(char c) { int result = 0; if (c >= 48) result = 1;
          { int c = 3; if (c <= 47) result += 2; } return result; }
          bool Second(int c) { return c <= 47; }'''
        self.assertEqual(self.evaluate(source, "[First('3'), Second(3), Second(51)]"), [3, True, False])

    def test_local_buffers_reverse_comparisons_and_single_evaluation(self):
        source = '''int Check() { char *name = new char[1]; name[0] = '3'; int i = 0;
          bool digit = 48 <= name[i++]; return i * 10 + digit; }'''
        self.assertEqual(self.evaluate(source, "Check()"), 11)


if __name__ == "__main__":
    unittest.main()
