#include <string.h>
#include <sys/mman.h>

asm(
    "flag:\n"
    ".incbin \"/home/broken-oj/flags/i_m_a_very_secure_and_weird_flag_filename_trust_me\"\n"
    ".byte 0\n"
    ".global flag\n"
);

extern char flag[];

char shellcode[] = REPLACE_ME;

int main(int argc, char *argv[])
{
    char *addr = mmap(0x10000000, 0x10000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (addr != (char *)0x10000000) {
        return 1;
    }

    memcpy(addr, shellcode, sizeof(shellcode));
    *(unsigned char **)(0x1000c000) = flag;
    ((void (*)())addr)();

    return 0;
}
