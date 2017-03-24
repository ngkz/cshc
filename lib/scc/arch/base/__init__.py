import os.path
import subprocess
import tempfile
import shutil
import sys
import os
import stat

def change_extension(path, extension):
    name = os.path.basename(path).rsplit(".", 1)
    if len(name) == 2:
        name[1] = extension
    return os.path.join(os.path.dirname(path), ".".join(name))

def mtime(path):
    return os.stat(path)[stat.ST_MTIME]

curdir = os.path.dirname(__file__)
class Arch:
    CFLAGS = ["-O3", "-fPIE", "-Winline", "-finline-functions", "-ffreestanding",
              "-fomit-frame-pointer", "-fno-zero-initialized-in-bss",
              "-I", os.path.join(curdir, "linux-syscall-support", "lss"),
              "-include", os.path.join(curdir, "prepend.h"),
              "-fno-tree-loop-distribute-patterns"]
    LDFLAGS = ["-pie", "-Wl,-s", "-nostdlib", "-nodefaultlibs", "-nostartfiles"]
    LDSCRIPT = os.path.join(curdir, "linker.ld")
    LIBS = []

    def __init__(self, verbose = False):
        self.verbose = verbose

    def _execute(self, args):
        if self.verbose:
            print(" ".join(args))

        retcode = subprocess.call(args)
        if retcode != 0:
            sys.exit(retcode)

    def cc(self, args):
        self._execute([self.CC] + self.CFLAGS + args)

    def compile_object(self, srcpath, outpath):
        self.cc(["-c", "-o", outpath, srcpath])

    def compile_libraries(self):
        libobjs = []
        for libsrc in self.LIBS:
            libobj = change_extension(libsrc, "o")
            if (not os.path.exists(libobj)) or mtime(libobj) < mtime(libsrc):
                self.compile_object(libsrc, libobj)
            libobjs.append(libobj)
        return libobjs

    def link_elf(self, objs, outpath):
        ldflags = self.LDFLAGS + ["-Wl,-T," + self.LDSCRIPT]
        if self.verbose:
            ldflags.append("-Wl,-M")
        ldflags += ["-o", outpath]
        self._execute([self.CC] + ldflags + objs)

    def extract_section(self, srcpath, outpath, section):
        self._execute([self.OBJCOPY, "-O", "binary", "-j", section, srcpath,
                       outpath])

    def elf2binary(self, srcpath, outpath):
        self.extract_section(srcpath, outpath, ".text")

    def patch_init_reloc(self, elf_path, bin_path, tmpdir):
        pass

    #compile file
    def compile_file(self, srcpath):
        tmpdir = tempfile.mkdtemp()
        try:
            objs = self.compile_libraries()

            scobj = os.path.join(tmpdir, "shellcode.o")
            self.compile_object(srcpath, scobj)

            objs.append(scobj)

            tmp_elf = os.path.join(tmpdir, "shellcode_elf")
            self.link_elf(objs, tmp_elf)

            outpath = os.path.join(tmpdir, "shellcode")
            self.elf2binary(tmp_elf, outpath)
            self.patch_init_reloc(tmp_elf, outpath, tmpdir)

            with open(outpath, "rb") as scfile:
                return scfile.read()
        finally:
            shutil.rmtree(tmpdir)

    #compile string
    def compile(self, shellcode):
        tmp = tempfile.NamedTemporaryFile(suffix = ".c")
        try:
            tmp.write(shellcode.encode("utf-8"))
            tmp.flush()
            return self.compile_file(tmp.name)
        finally:
            tmp.close()

    #compile and write assembly to file
    def compile_assembly(self, srcpath, outpath):
        args = ["-S"]
        if not outpath is None:
            args += ["-o", outpath]
        args.append(srcpath)
        self.cc(args)

