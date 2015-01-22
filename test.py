import sys
import os.path

SELF_DIR = os.path.dirname(__file__)
sys.path.insert(0, os.path.join(SELF_DIR, "lib"))

import unittest
import scgen
import subprocess
import tempfile

class ShellcodeExecuteTest(unittest.TestCase):
    def check_shellcode(self, arch, shellcode):
        tmp = tempfile.NamedTemporaryFile()
        tmp.write(shellcode)
        tmp.flush()

        stdout = subprocess.check_output(["bin/scrun-" + arch, tmp.name])
        self.assertEqual(stdout, b"ok\n")

        tmp.close()

class CompileFileTest(ShellcodeExecuteTest):
    def test_x86(self):
        self.check_shellcode("x86",
                scgen.arch("x86").compile_file("shellcode/test.c"))

    def test_x86_64(self):
        self.check_shellcode("x86_64",
                scgen.arch("x86_64").compile_file("shellcode/test.c"))

    def test_armel(self):
        self.check_shellcode("armel",
                scgen.arch("armel").compile_file("shellcode/test.c"))

    def test_aarch64(self):
        self.check_shellcode("aarch64",
                scgen.arch("aarch64").compile_file("shellcode/test.c"))

class CompileStringTest(ShellcodeExecuteTest):
    SRC = r"""
    void main() {
        sys_write(1, "ok\n", 3);
        sys__exit(0);
    }
    """

    def test_x86(self):
        self.check_shellcode("x86", scgen.arch("x86").compile(self.SRC))

    def test_x86_64(self):
        self.check_shellcode("x86_64", scgen.arch("x86_64").compile(self.SRC))

    def test_armel(self):
        self.check_shellcode("armel", scgen.arch("armel").compile(self.SRC))

    def test_aarch64(self):
        self.check_shellcode("aarch64", scgen.arch("aarch64").compile(self.SRC))

class NOTreeLoopDistributePatternsRegressionTest(ShellcodeExecuteTest):
    def test_test(self):
        scgen.arch("x86").compile("""
            void *_memset(void *s, int c, size_t n) {
                unsigned char* p=s;
                while(n--)
                    *p++ = (unsigned char)c;
                return s;
            }

            int main() {
                char buf[4096];
                _memset(buf, 0, sizeof(buf));
                _memset(buf, 0, sizeof(buf));
                sys__exit(0);
            }
        """)

if __name__ == "__main__":
    unittest.main()

