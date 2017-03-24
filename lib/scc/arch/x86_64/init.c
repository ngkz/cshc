#include <elf.h>

extern char shellcode_start[];
void init() __attribute__((section(".init")));
extern Elf64_Rela rel_start[];
extern Elf64_Rela rel_end[];

void init() {
    Elf64_Rela *rel;

    for (rel = rel_start; rel < rel_end; rel++) {
       *(Elf64_Addr *)(shellcode_start + rel->r_offset) += (Elf64_Addr)shellcode_start;
    }

    main();
}

