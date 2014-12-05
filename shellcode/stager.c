#include <sys/mman.h>

#define FD 0
#define LENGTH 0x1000
void main() {
#if defined(__i386__) || defined(__ARM_ARCH_3__) ||                         \
  defined(__ARM_EABI__) ||                                             \
 (defined(__mips__) && _MIPS_SIM == _MIPS_SIM_ABI32) || defined(__PPC__)
    void *mem = sys_mmap2(NULL, LENGTH, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
                 -1, 0);
#else
    void *mem = sys_mmap(NULL, LENGTH, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
                 -1, 0);
#endif

    sys_read(FD, mem, LENGTH);

    ((void (*)())mem)();
}
