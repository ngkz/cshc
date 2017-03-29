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

/*
 * Copyright (c) 2013 Albert ARIBAUD <albert.u.boot@aribaud.net>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

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
