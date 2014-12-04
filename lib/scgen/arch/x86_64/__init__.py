import os.path
from scgen.arch import base

class Arch(base.Arch):
    CC = "x86_64-linux-gnu-gcc"
    OBJCOPY = "x86_64-linux-gnu-objcopy"
    LIBS = base.Arch.LIBS + [os.path.join(os.path.dirname(__file__), "init.c")]
