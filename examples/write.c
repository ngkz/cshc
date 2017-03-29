#define FILE "/tmp/test"
#define FD 0
#define FLAG (O_CREAT | O_WRONLY)
#define PERM 0644

void main() {
    int fd;
    char buf[4096];
    int readsize;

    fd = sys_open(FILE, FLAG, PERM);
    while((readsize = sys_read(FD, buf, sizeof(buf))) > 0) {
        sys_write(fd, buf, readsize);
    }

    sys__exit(0);
}
