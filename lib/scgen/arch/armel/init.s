    .section    ._rel_start
    .global    rel_start
rel_start:
    .section    ._rel_end
    .global    rel_end
rel_end:
    .section    .init
    .align    2
relocate:
    adr    r4, relocate /* shellcode base */
    ldr    r2, =rel_start
    add    r2, r2, r4
    ldr    r3, =rel_end
    add    r3, r3, r4
relocate_loop:
    ldmia    r2!, {r0-r1}        /* (r0,r1) <- (SRC location,fixup) */
    and    r1, r1, #0xff
    cmp    r1, #23            /* relative fixup? */
    bne    after_fix

    /* relative fix: increase location by offset */
    add    r0, r0, r4
    ldr    r1, [r0]
    add    r1, r1, r4
    str    r1, [r0]
after_fix:
    cmp    r2, r3
    blo    relocate_loop

    b main
