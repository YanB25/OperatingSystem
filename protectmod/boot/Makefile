LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

all: boot.bin head.bin
boot.bin: boot.o
	$(LD) $(LDFLAGS) -Ttext 0x0 --oformat binary -o $@ $^
boot.o: boot.s
	$(AS) $(ASFLAGS) -f elf -o $@ $^
head.bin: head.o
	$(LD) $(LDFLAGS) -Ttext 0x8000 --oformat binary -o $@ $^
head.o: head.s
	$(AS) $(ASFLAGS) -f elf -o $@ $^

clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.bin" -delete