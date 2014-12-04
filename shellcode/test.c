int bss = 0;
int data = 1000;

int _strlen(const char *str) {
    int l;
    for (l = 0; str[l]; l++);
    return l;
}

void put(const char *str) {
    sys_write(1, str, _strlen(str));
}

volatile void *pstrlen = &_strlen;

int main() {
    if (bss != 0) {
        put("bss ng\n");
        sys__exit(1);
    }
    if (data != 1000) {
        put("data ng\n");
        sys__exit(1);
    }
    if (pstrlen != &_strlen) {
        put("relocation ng\n");
        sys__exit(1);
    }
    put("ok\n");
    sys__exit(0);
}
