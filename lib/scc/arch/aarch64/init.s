    .section    ._rel_start
    .global    rel_start
rel_start:
    .section    ._rel_end
    .global    rel_end
rel_end:
    .section    .init
    .align    2
    .global    init
relocate:
    adr    x9, relocate /* shellcode base */
    ldr    x2, =rel_start
    add    x2, x2, x9
    ldr    x3, =rel_end
    add    x3, x3, x9
relocate_loop:
    ldp    x0, x1, [x2], #16    /* (x0,x1) <- (SRC location, fixup) */
    ldr    x4, [x2], #8        /* x4 <- addend */
    and    x1, x1, #0xffffffff
    cmp    x1, #1027        /* relative fixup? */
    bne    after_fix

    /* relative fix: store addend plus offset at dest location */
    add    x0, x0, x9
    add    x4, x4, x9
    str    x4, [x0]
after_fix:
    cmp    x2, x3
    b.lo    relocate_loop

    b main
