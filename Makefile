TARGETS=bin/scrun-i386 bin/scrun-x86_64 bin/scrun-armel bin/scrun-aarch64 \
		bin/scrun-ppc
CFLAGS=-Wall -fno-stack-protector -z execstack
CC_I386=gcc -m32
CC_X86_64=gcc
CC_ARMEL=arm-linux-gnueabi-gcc -static
CC_AARCH64=aarch64-linux-gnu-gcc -static
CC_POWERPC=powerpc-linux-gnu-gcc -static

all: $(TARGETS)

bin/scrun-i386: scrun.c
	$(CC_I386) $(CFLAGS) -o $@ $<

bin/scrun-x86_64: scrun.c
	$(CC_X86_64) $(CFLAGS) -o $@ $<

bin/scrun-armel: scrun.c
	$(CC_ARMEL) $(CFLAGS) -o $@ $<

bin/scrun-aarch64: scrun.c
	$(CC_AARCH64) $(CFLAGS) -o $@ $<

bin/scrun-ppc: scrun.c
	$(CC_POWERPC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGETS)
