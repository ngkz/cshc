from scgen.arch import x86, x86_64, armel, aarch64
ARCH = {
    "x86": x86.Arch,
    "x86_64": x86_64.Arch,
    "armel": armel.Arch,
    "aarch64": aarch64.Arch
}

def archlist():
    return ARCH.keys()

def arch(archname, verbose = False):
    return ARCH[archname](verbose)

