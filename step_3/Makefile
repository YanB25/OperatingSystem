LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m32 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

kernel.bin: kernel.o utilities.o
	$(LD) $(LDFALGS) -Text 0xA100 --oformat binary -o $@ $^
kernel.o: kernel.c kernel.h utilities.h
	$(CC) $(CCFLAGS) -c $^
utilities.o: utilities.asm
	$(AS) $(ASFLAGS) -c elf32 -o $@ $^
loader.o: loader.asm
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^
loader.bin: loader.o
	$(LD) $(LDFLAGS) -Ttext 0x7c00 --oformat binary -o $@ $^

clean:
	rm *.bin
	rm *.o

run:
	bochs -q