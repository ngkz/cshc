import sys
import os.path

SELF_DIR = os.path.dirname(__file__)
sys.path.insert(0, os.path.join(SELF_DIR, "lib"))

import unittest
import scgen
import subprocess
import tempfile

class CompileTest(unittest.TestCase):
    def check_shellcode(self, arch, shellcode):
        tmp = tempfile.NamedTemporaryFile()
        tmp.write(shellcode)
        tmp.flush()

        stdout = subprocess.check_output(["bin/scrun-" + arch, tmp.name])
        self.assertEqual(stdout, b"ok\n")

        tmp.close()

    def test_x86(self):
        self.check_shellcode("x86",
                scgen.arch("x86").compile("shellcode/test.c"))

    def test_x86_64(self):
        self.check_shellcode("x86_64",
                scgen.arch("x86_64").compile("shellcode/test.c"))

    def test_armel(self):
        self.check_shellcode("armel",
                scgen.arch("armel").compile("shellcode/test.c"))

    def test_aarch64(self):
        self.check_shellcode("aarch64",
                scgen.arch("aarch64").compile("shellcode/test.c"))

if __name__ == "__main__":
    unittest.main()

