LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

all: boot.bin loader.bin
boot.bin: boot.o
	$(LD) $(LDFLAGS) -Ttext 0x8000 --oformat binary -o $@ $^
boot.o: boot.s
	$(AS) $(ASFLAGS) -f elf -o $@ $^
loader.bin: loader.o
	$(LD) $(LDFLAGS) -Ttext 0 --oformat binary -o $@ $^
loader.o: loader.s
	$(AS) $(ASFLAGS) -f elf -o $@ $^
