OUTPUT_FORMAT("binary")

SECTIONS {
    .text : {
        _GLOBAL_OFFSET_TABLE_ = .;
        *(.text.startup)
        *(.text*)
        *(.rodata*)
        *(.data*)
    }

    .bss : {
        *(.bss)
    }
    /DISCARD/ : {
        *(.eh_frame)
        *(.eh_frame_hdr)
        *(.note.gnu.build-id)
        *(.note.GNU-stack)
        *(.gnu_debuglink)
        *(.gnu.lto_*)
        *(.gnu.hash)
    }
}
