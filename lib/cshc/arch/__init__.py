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
ARCH = dict([(name, __import__(
        "cshc.arch." + name, globals(), locals(), ["Arch"]
    ).Arch) for name in ("x86", "x86_64", "armel", "aarch64")])

def archlist():
    return ARCH.keys()

def arch(archname, verbose = False):
    return ARCH[archname](verbose)

