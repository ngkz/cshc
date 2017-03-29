/*
 * cshc - C Shellcode Compiler
 * Copyright (C) 2014-2017  Kazutoshi Noguchi
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <elf.h>

extern char shellcode_start[];
void init() __attribute__((section(".init")));
extern Elf64_Rela rel_start[];
extern Elf64_Rela rel_end[];

void init() {
    Elf64_Rela *rel;

    for (rel = rel_start; rel < rel_end; rel++) {
       *(Elf64_Addr *)(shellcode_start + rel->r_offset) += (Elf64_Addr)shellcode_start;
    }

    main();
}

