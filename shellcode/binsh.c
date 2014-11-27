/* 
 * ShellForge example: execute /bin/sh 
 * $Id$
 */

int main() {
    const char *a[] = {"/bin/sh", 0};
    sys_execve(*a, a, 0);
}

