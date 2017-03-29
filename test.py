"""
cshc - C Shellcode Compiler
Copyright (C) 2014-2017  Kazutoshi Noguchi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""

import sys
import os.path

SELF_DIR = os.path.dirname(__file__)
sys.path.insert(0, os.path.join(SELF_DIR, "lib"))

import unittest
import cshc
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
                cshc.arch("x86").compile_file("examples/test.c"))

    def test_x86_64(self):
        self.check_shellcode("x86_64",
                cshc.arch("x86_64").compile_file("examples/test.c"))

    def test_armel(self):
        self.check_shellcode("armel",
                cshc.arch("armel").compile_file("examples/test.c"))

    def test_aarch64(self):
        self.check_shellcode("aarch64",
                cshc.arch("aarch64").compile_file("examples/test.c"))

class CompileStringTest(ShellcodeExecuteTest):
    SRC = r"""
    void main() {
        sys_write(1, "ok\n", 3);
        sys__exit(0);
    }
    """

    def test_x86(self):
        self.check_shellcode("x86", cshc.arch("x86").compile(self.SRC))

    def test_x86_64(self):
        self.check_shellcode("x86_64", cshc.arch("x86_64").compile(self.SRC))

    def test_armel(self):
        self.check_shellcode("armel", cshc.arch("armel").compile(self.SRC))

    def test_aarch64(self):
        self.check_shellcode("aarch64", cshc.arch("aarch64").compile(self.SRC))

class NOTreeLoopDistributePatternsRegressionTest(ShellcodeExecuteTest):
    def test_test(self):
        cshc.arch("x86").compile("""
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

