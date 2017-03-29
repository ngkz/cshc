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

class Arch(base.Arch):
    CC = "x86_64-linux-gnu-gcc"
    OBJCOPY = "x86_64-linux-gnu-objcopy"
    CFLAGS = base.Arch.CFLAGS + ["-m32"]
    LDFLAGS = base.Arch.LDFLAGS + ["-m32"]
    LIBS = base.Arch.LIBS + [os.path.join(os.path.dirname(__file__), "init.c")]
