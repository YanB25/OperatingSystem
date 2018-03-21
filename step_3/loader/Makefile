LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

loader.bin: loader.o
	$(LD) $(LDFLAGS) -Ttext 0x7c00 --oformat binary -o $@ $^

loader.o: loader.asm
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^

clean:
	rm *.bin -f 
	rm *.o -f 
	rm *.gch -f
run:
	bochs -q
rebuild:
	make clean 
	make
