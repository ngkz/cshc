"""
cshc - C Shellcode Compiler
Copyright (C) 2014-2017  Kazutoshi Noguchi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
import os.path
from cshc.arch import base

curdir = os.path.dirname(__file__)

class Arch(base.Arch):
    CC = "arm-linux-gnueabi-gcc"
    OBJCOPY = "arm-linux-gnueabi-objcopy"
    LDSCRIPT = os.path.join(curdir, "linker.ld")
    LIBS = base.Arch.LIBS + [os.path.join(curdir, "init.s")]

