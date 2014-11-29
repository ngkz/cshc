SECTIONS {
    .text : {
        _GLOBAL_OFFSET_TABLE_ = .;
        *(.entry)
        *(.text*)
        *(.rodata*)
        *(.data*)
        *(._rel_start)
        *(.rel*)
        *(._rel_end)
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
