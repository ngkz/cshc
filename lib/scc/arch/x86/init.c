#include <elf.h>

extern char shellcode_start[];
void init() __attribute__((section(".init")));
extern Elf32_Rel rel_start[];
extern Elf32_Rel rel_end[];

void init() {
    Elf32_Rel *rel;

    for (rel = rel_start; rel < rel_end; rel++) {
       *(Elf32_Addr *)(shellcode_start + rel->r_offset) += (Elf32_Addr)shellcode_start;
    }

    main();
}

