TARGETS=tester_i386 tester_x86_64 tester_armel tester_armhf tester_aarch64 \
		tester_ppc
CFLAGS=-Wall -fno-stack-protector -z execstack
CC_I386=gcc -m32
CC_X86_64=gcc
CC_ARMEL=arm-linux-gnueabi-gcc -static
CC_AARCH64=aarch64-linux-gnu-gcc -static
CC_POWERPC=powerpc-linux-gnu-gcc -static

all: $(TARGETS)

tester_i386: tester.c
	$(CC_I386) $(CFLAGS) -o $@ $<

tester_x86_64: tester.c
	$(CC_X86_64) $(CFLAGS) -o $@ $<

tester_armel: tester.c
	$(CC_ARMEL) $(CFLAGS) -o $@ $<

tester_aarch64: tester.c
	$(CC_AARCH64) $(CFLAGS) -o $@ $<

tester_ppc: tester.c
	$(CC_POWERPC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGETS)
