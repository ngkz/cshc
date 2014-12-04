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
