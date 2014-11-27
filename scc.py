#!/usr/bin/python3

import argparse
import shlex
import subprocess
import sys
import os.path

SELF_DIR = os.path.dirname(os.path.realpath(__file__))
LINKER_SCRIPT = os.path.join(SELF_DIR, "linker.ld")
LSS_PATH = os.path.join(SELF_DIR, "linux-syscall-support", "lss")
PREPEND = os.path.join(SELF_DIR, "prepend.h")

COMPILER = {
    'i386': "gcc -m32",
    'x86_64': "gcc"
}

parser = argparse.ArgumentParser(description = 'C Shellcode Compiler')
parser.add_argument('srcpath', help = 'source code file')
parser.add_argument('-o', metavar = "<file>", dest = 'outpath', help = 'place the output into <file>')
parser.add_argument('-a', '--arch', choices = ("i386", "x86_64", "armel", "arm", "aarch64", "mips", "ppc"), default = "i386", help = 'target architecture')
parser.add_argument('-v', help = 'verbose mode', action = 'store_true', dest = 'verbose')
parser.add_argument('-e', '--encoder', choices = ("alnum", "cstring"), help = 'encode shellcode')

args = parser.parse_args()

cmd = COMPILER[args.arch]
cmd += " -O3 -fPIE -Winline -finline-functions -ffreestanding -fomit-frame-pointer -fno-zero-initialized-in-bss -isystem {} -include {} -Wl,-T,{},-s,--gc-sections -nostdlib -nodefaultlibs -nostartfiles".format(shlex.quote(LSS_PATH), shlex.quote(PREPEND), shlex.quote(LINKER_SCRIPT))

if args.verbose:
    cmd += " -Wl,-M"

if not args.outpath is None:
    cmd += " -o " + shlex.quote(args.outpath)

cmd += " " + shlex.quote(args.srcpath)

if args.verbose:
    print(cmd)

retcode = subprocess.call(cmd, shell = True)
if retcode != 0:
    sys.exit(retcode)

if not args.encoder is None:
    #TODO
    pass


