#include <asm-generic/poll.h>

#define INFD0 0
#define OUTFD0 1
#define INFD1 0
#define OUTFD1 1

struct kernel_pollfd fds[] = {
    {INFD0, POLLIN, 0},
    {INFD1, POLLIN, 0}
};

const int outfds[] = {
    OUTFD1,
    OUTFD0
};

int main() {
    int result;
    int i;
    char buf[4096];

    for(;;) {
        if (sys_poll(fds, sizeof(fds) / sizeof(fds[0]), -1) <= 0) continue;
        for (i = 0; i < (sizeof(fds) / sizeof(fds[0])); i++) {
            if (fds[i].revents & POLLIN) {
                ssize_t len = sys_read(fds[i].fd, buf, sizeof(buf));
                ssize_t sent = 0;
                if (len <= 0) {
                    sys__exit(1);
                }
                while(sent < len) {
                    ssize_t write_res = sys_write(outfds[i], buf + sent, len - sent);
                    if (write_res <= 0) {
                        sys__exit(2);
                    }
                    sent += write_res;
                }
            }
        }
    }
}
