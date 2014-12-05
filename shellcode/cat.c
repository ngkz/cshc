#define FILE "/etc/passwd"
#define OUTFD 1

void main() {
    int fd;
    char buf[4096];
    int readsize;

    fd = sys_open(FILE, 0, 0);
    while((readsize = sys_read(fd, buf, sizeof(buf))) > 0) {
        sys_write(OUTFD, buf, readsize);
    }
    
    sys_exit(0);
}
