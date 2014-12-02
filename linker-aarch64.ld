SECTIONS {
    .text : {
        _GLOBAL_OFFSET_TABLE_ = .;
        *(.entry)
        *(.text*)
        *(.rodata*)
        *(.data*)
        *(._rel_start)
        *(.rela.data.rel)
        *(._rel_end)
    }

    .bss : {
        *(.bss)
        *(COM*)
    }

    .rela.entry : {
        *(.rela.entry)
    }

    .junk : {
        *(.note.gnu.build-id)
        *(.got*)
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
