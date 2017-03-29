//perm, uid, gid, size, mtime(unix time, hour, min), filename
#define DIRECTORY "."
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

static void printPerm(unsigned perm) {
    switch(perm & S_IFMT) {
    case S_IFBLK:  print("b");            break;
    case S_IFCHR:  print("c");        break;
    case S_IFDIR:  print("d");               break;
    case S_IFIFO:  print("p");               break;
    case S_IFLNK:  print("l");                 break;
    case S_IFREG:  print("-");            break;
    case S_IFSOCK: print("s");                  break;
    default:       print("unknown");                break;
    }

    print(perm & S_IRUSR ? "r" : "-");
    print(perm & S_IWUSR ? "w" : "-");
    if (perm & S_IXUSR) {
        if (perm & S_ISUID) {
            print("s");
        } else {
            print("x");
        }
    } else {
        print("-");
    }

    print(perm & S_IRGRP ? "r" : "-");
    print(perm & S_IWGRP ? "w" : "-");
    if (perm & S_IXGRP) {
        if (perm & S_ISGID) {
            print("s");
        } else {
            print("x");
        }
    } else {
        print("-");
    }

    print(perm & S_IROTH ? "r" : "-");
    print(perm & S_IWOTH ? "w" : "-");
    if (perm & S_IXOTH) {
        if (perm & S_ISVTX) {
            print("t");
        } else {
            print("x");
        }
    } else {
        print("-");
    }
}

static void printInt(unsigned value, int digits) {
    char str[digits + 1];
    int i;
    int pos;

    for (i = 0; i < sizeof(str) - 1; i++) {
        str[i] = ' ';
    }
    str[sizeof(str) - 1] = 0;
    pos = sizeof(str) - 2;

    do {
        str[pos] = '0' + (value % 10);
        value /= 10;
        pos--;
    } while(value > 0);

    print(str);
}

static void printTime(unsigned time) {
    printInt(time, 20);
    print(" ");
    printInt((time / 3600) % 24, 2);
    print(":");
    printInt((time / 60) % 60, 2);
}

int main(void)
{
    int fd, nread;
    char buf[1024];
    struct kernel_dirent *d;
    int bpos;
    struct kernel_stat sb;

    fd = sys_open(DIRECTORY, O_RDONLY, 0);
    if (fd < 0) {
        println("error");
        sys__exit(1);
    }

    sys_chdir(DIRECTORY);

    for(;;) {
        nread = sys_getdents(fd, (struct kernel_dirent *)buf, sizeof(buf));
        if (nread == -1) {
            println("error");
            sys__exit(1);
        }
        if (nread == 0) break;

        for (bpos = 0; bpos < nread;) {
            d = (struct kernel_dirent *)(buf + bpos);

            sys_lstat(d->d_name, &sb);
            printPerm(sb.st_mode);
            print(" ");
            printInt(sb.st_uid, 6);
            print(" ");
            printInt(sb.st_gid, 6);
            print(" ");
            printInt(sb.st_size, 19);
            print(" ");
            printTime(sb.st_mtime_);
            print(" ");
            println(d->d_name);
            bpos += d->d_reclen;
        }
    }

    sys__exit(0);
}
