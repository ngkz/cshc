SECTIONS {
    .rela.init 0xfffffffffffff000 : { /* dirty */
        *(.rela.init)
    }

    .text 0 : {
        _GLOBAL_OFFSET_TABLE_ = .;
        *(.init)
        *(.text*)
        *(.rodata*)
        *(.data*)

        *(._rel_start)
        *(.rela*)
        *(._rel_end)
    }

    .bss : {
        *(.bss)
        *(COM*)
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
