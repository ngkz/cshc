static int _errno;
#define SYS_ERRNO _errno
#include <linux_syscall_support.h>
#include <elf.h>

void entry() __attribute__((section(".entry")));
extern char shellcode_start[];

#if defined(__i386__)
extern Elf32_Rel rel_start[];
extern Elf32_Rel rel_end[];

static inline void relocate() {
    Elf32_Rel *rel;

    for (rel = rel_start; rel < rel_end; rel++) {
       *(Elf32_Addr *)(shellcode_start + rel->r_offset) += (Elf32_Addr)shellcode_start;
    }
}
#endif

#if defined(__x86_64__)
extern Elf64_Rela rel_start[];
extern Elf64_Rela rel_end[];

static inline void relocate() {
    Elf64_Rela *rel;

    for (rel = rel_start; rel < rel_end; rel++) {
       *(Elf64_Addr *)(shellcode_start + rel->r_offset) += (Elf64_Addr)shellcode_start;
    }
}
#endif

#if defined(__ARM_ARCH_3__) || defined(__ARM_EABI__) || defined(__aarch64__)
char rel_start[0] __attribute__((section("._rel_start")));
char rel_end[0] __attribute__((section("._rel_end")));
#endif

#if defined(__ARM_ARCH_3__) || defined(__ARM_EABI__)
static inline void relocate() {
    asm volatile(
    "    adr    r4, entry\n"
    "    ldr    r2, =rel_start    /* r2 <- SRC &__rel_dyn_start */\n"
    "    add    r2, r2, r4\n"
    "    ldr    r3, =rel_end    /* r3 <- SRC &__rel_dyn_end */\n"
    "    add    r3, r3, r4\n"
    "1:\n"
    "    ldmia    r2!, {r0-r1}        /* (r0,r1) <- (SRC location,fixup) */\n"
    "    and    r1, r1, #0xff\n"
    "    cmp    r1, #23            /* relative fixup? */\n"
    "    bne    2f\n"
    "\n"
    "    /* relative fix: increase location by offset */\n"
    "    add    r0, r0, r4\n"
    "    ldr    r1, [r0]\n"
    "    add    r1, r1, r4\n"
    "    str    r1, [r0]\n"
    "2:\n"
    "    cmp    r2, r3\n"
    "    blo    1b\n"
    : : : "r0", "r1", "r2", "r3", "r4", "cc", "memory");
}
#endif

#ifdef __aarch64__
static inline void relocate() {
    asm volatile(
    "    adr    x9, entry\n"
    "    ldr    x2, =rel_start    /* x2 <- SRC &__rel_dyn_start */\n"
    "    add    x2, x2, x9\n"
    "    ldr    x3, =rel_end    /* x3 <- SRC &__rel_dyn_end */\n"
    "    add    x3, x3, x9\n"
    "1:\n"
    "    ldp    x0, x1, [x2], #16    /* (x0,x1) <- (SRC location, fixup) */\n"
    "    ldr    x4, [x2], #8        /* x4 <- addend */\n"
    "    and    x1, x1, #0xffffffff\n"
    "    cmp    x1, #1027        /* relative fixup? */\n"
    "    bne    2f\n"
    "\n"
    "    /* relative fix: store addend plus offset at dest location */\n"
    "    add    x0, x0, x9\n"
    "    add    x4, x4, x9\n"
    "    str    x4, [x0]\n"
    "2:\n"
    "    cmp    x2, x3\n"
    "    b.lo    1b\n"
    : : : "x0", "x1", "x2", "x3", "x4", "x9", "cc", "memory");
}
#endif

void entry() {
    relocate();
    main();
}

