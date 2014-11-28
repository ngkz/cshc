TARGETS=bin/tester_i386 bin/tester_x86_64 bin/tester_armel bin/tester_aarch64 \
		bin/tester_ppc
CFLAGS=-Wall -fno-stack-protector -z execstack
CC_I386=gcc -m32
CC_X86_64=gcc
CC_ARMEL=arm-linux-gnueabi-gcc -static
CC_AARCH64=aarch64-linux-gnu-gcc -static
CC_POWERPC=powerpc-linux-gnu-gcc -static

all: $(TARGETS)

bin/tester_i386: tester.c
	$(CC_I386) $(CFLAGS) -o $@ $<

bin/tester_x86_64: tester.c
	$(CC_X86_64) $(CFLAGS) -o $@ $<

bin/tester_armel: tester.c
	$(CC_ARMEL) $(CFLAGS) -o $@ $<

bin/tester_aarch64: tester.c
	$(CC_AARCH64) $(CFLAGS) -o $@ $<

bin/tester_ppc: tester.c
	$(CC_POWERPC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGETS)
