#define CMD "cat /etc/passwd"

int main() {
    const char *a[] = {"/bin/sh", "-c", CMD, 0};
    sys_execve(*a, a, 0);
}

