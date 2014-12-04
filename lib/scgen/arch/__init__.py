from scgen.arch import i386, x86_64, armel, aarch64
ARCH = {
    "i386": i386.Arch,
    "x86_64": x86_64.Arch,
    "armel": armel.Arch,
    "aarch64": aarch64.Arch
}

def archlist():
    return ARCH.keys()

def arch(archname, verbose = False):
    return ARCH[archname](verbose)

