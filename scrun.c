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

