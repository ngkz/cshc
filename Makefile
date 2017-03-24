TARGETS=bin/scrun-x86 bin/scrun-x86_64 bin/scrun-armel bin/scrun-aarch64 \
		bin/scrun-ppc bin/scrun-ppc64 bin/scrun-ppc64le
CFLAGS=-Wall -fno-stack-protector -z execstack
CC_X86=x86_64-linux-gnu-gcc -m32
CC_X86_64=x86_64-linux-gnu-gcc
CC_ARMEL=arm-linux-gnueabi-gcc -static
CC_AARCH64=aarch64-linux-gnu-gcc -static
CC_POWERPC=powerpc-linux-gnu-gcc -static
CC_POWERPC64=powerpc-linux-gnu-gcc -m64 -static
CC_POWERPC64LE=powerpc64le-linux-gnu-gcc -static

all: $(TARGETS)

bin/scrun-x86: scrun.c
	$(CC_X86) $(CFLAGS) -o $@ $<

bin/scrun-x86_64: scrun.c
	$(CC_X86_64) $(CFLAGS) -o $@ $<

bin/scrun-armel: scrun.c
	$(CC_ARMEL) $(CFLAGS) -o $@ $<

bin/scrun-aarch64: scrun.c
	$(CC_AARCH64) $(CFLAGS) -o $@ $<

bin/scrun-ppc: scrun.c
	$(CC_POWERPC) $(CFLAGS) -o $@ $<

bin/scrun-ppc64: scrun.c
	$(CC_POWERPC64) $(CFLAGS) -o $@ $<

bin/scrun-ppc64le: scrun.c
	$(CC_POWERPC64LE) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGETS)
