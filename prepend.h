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

void entry() {
    relocate();
    main();
}

