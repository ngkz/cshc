import os.path
from cshc.arch import base

curdir = os.path.dirname(__file__)

class Arch(base.Arch):
    CC = "arm-linux-gnueabi-gcc"
    OBJCOPY = "arm-linux-gnueabi-objcopy"
    LDSCRIPT = os.path.join(curdir, "linker.ld")
    LIBS = base.Arch.LIBS + [os.path.join(curdir, "init.s")]

