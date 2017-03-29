#define INPUT_FD 0
#define TMP "/tmp/.REPLACE_ME1"
#define ARGV0 "REPLACE_ME2"

int main() {
    sys_unlink(TMP);
    int fd = sys_open(TMP, O_CREAT | O_WRONLY | O_TRUNC, 0700);
    if (fd == -1) {
        sys__exit(1);
    }
    for(;;) {
        char buf[4096];
        ssize_t len = sys_read(INPUT_FD, buf, sizeof(buf));
        if (len <= 0) break;
        sys_write(fd, buf, len);
    }
    sys_close(fd);

    const char *argv[] = {ARGV0, 0};
    sys_execve(TMP, argv, 0);
}
