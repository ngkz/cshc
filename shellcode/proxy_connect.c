#include <endian.h>
#include <asm-generic/poll.h>
#include <netinet/in.h>

#define IP(t,z,y,x)  ((x)|(y)<<8|(z)<<16|(t)<<24)

#define DEST_IP IP(127, 0, 0, 1)
#define DEST_PORT 43210

#define INFD0 0
#define OUTFD0 1

int main() {
    int result;
    int i;
    char buf[4096];

    int sock;
    struct sockaddr_in sa;
    sock = sys_socket(PF_INET, SOCK_STREAM, 0);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htobe32(DEST_IP);
    sa.sin_port = htobe16(DEST_PORT);
    while (sys_connect(sock, (struct kernel_sockaddr *)&sa, sizeof(sa)) < 0);

    struct kernel_pollfd fds[] = {
        {INFD0, POLLIN, 0},
        {sock, POLLIN, 0}
    };

    const int outfds[] = {
        sock,
        OUTFD0
    };

    for(;;) {
        if (sys_poll(fds, sizeof(fds) / sizeof(fds[0]), -1) <= 0) continue;
        for (i = 0; i < (sizeof(fds) / sizeof(fds[0])); i++) {
            if (fds[i].revents & POLLIN) {
                ssize_t len = sys_read(fds[i].fd, buf, sizeof(buf));
                if (len <= 0) {
                    sys__exit(1);
                }
                sys_write(outfds[i], buf, len);
            }
        }
    }
}
