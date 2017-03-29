import os.path
from cshc.arch import base

class Arch(base.Arch):
    CC = "x86_64-linux-gnu-gcc"
    OBJCOPY = "x86_64-linux-gnu-objcopy"
    CFLAGS = base.Arch.CFLAGS + ["-m32"]
    LDFLAGS = base.Arch.LDFLAGS + ["-m32"]
    LIBS = base.Arch.LIBS + [os.path.join(os.path.dirname(__file__), "init.c")]
