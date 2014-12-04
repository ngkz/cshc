#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *scfile;
    char buf[65536];
    if (argc <= 1) {
        printf("Usage: %s file\n", argv[0]);
        printf("Max 64KiB\n");
        exit(1);
    }
    scfile = fopen(argv[1], "r");
    if (!scfile) {
        fprintf(stderr, "Can't open\n");
        exit(1);
    }
    memset(buf, 0xff, sizeof(buf));
    fread(buf, 1, sizeof(buf), scfile);
    fclose(scfile);

#if (defined(__i386__) || defined(__x86_64__))
    asm volatile("jmp *%0" :: "a"(buf));
    return 0;
#else
    return ((int (*)())buf)();
#endif
}

