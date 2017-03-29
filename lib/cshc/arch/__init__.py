ARCH = dict([(name, __import__(
        "cshc.arch." + name, globals(), locals(), ["Arch"]
    ).Arch) for name in ("x86", "x86_64", "armel", "aarch64")])

def archlist():
    return ARCH.keys()

def arch(archname, verbose = False):
    return ARCH[archname](verbose)

