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
SECTIONS {
    .text : {
        shellcode_start = .;
        _GLOBAL_OFFSET_TABLE_ = .;
        *(.init)
        *(.text*)
        *(.rodata*)
        *(.data*)

        rel_start = .;
        *(.rel*)
        rel_end = .;
    }

    .bss : {
        *(.bss)
        *(COM*)
    }

    .junk : {
        *(.got*)
        *(.note.gnu.build-id)
    }

    /DISCARD/ : {
        *(.eh_frame)
        *(.eh_frame_hdr)
        *(.note.GNU-stack)
        *(.dynsym)
        *(.dynstr*)
        *(.dynamic*)
        *(.plt*)
        *(.interp*)
        *(.gnu*)
        *(.hash)
        *(.comment)
    }
}
