import os.path
import struct
from cshc.arch import base

curdir = os.path.dirname(__file__)

class Arch(base.Arch):
    CC = "aarch64-linux-gnu-gcc"
    CFLAGS = base.Arch.CFLAGS + ["-mcmodel=tiny", "-O2"]
    OBJCOPY = "aarch64-linux-gnu-objcopy"
    LDSCRIPT = os.path.join(curdir, "linker.ld")
    LIBS = base.Arch.LIBS + [os.path.join(curdir, "init.s")]

    def patch_init_reloc(self, elf_path, binpath, tmpdir):
        rela_path = os.path.join(tmpdir, "rela")
        self.extract_section(elf_path, rela_path, ".rela.init")
        with open(binpath, "r+b") as shellcode_file:
            with open(rela_path, "rb") as rela_file:
                while True:
                    #Elf64_Rela
                    rela = rela_file.read(8 * 3)
                    if len(rela) == 0:
                        break
                    r_offset, r_info, r_addend = struct.unpack("<QQQ", rela)
                    assert r_info & 0xffffffff == 1027, "unsupported relocation entry" #not R_AARCH64_RELATIVE

                    if self.verbose:
                        print("patch .init: offset: 0x%x, addend: 0x%x" % (r_offset, r_addend))
                    shellcode_file.seek(r_offset)
                    shellcode_file.write(struct.pack("<Q", r_addend))
