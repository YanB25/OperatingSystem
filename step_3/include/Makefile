LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

all: utilities.o mystring.o

utilities.o: utilities.asm
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^

mystring.o : mystring.c mystring.h
	$(CC) $(CCFLAGS) -c $^

clean:
	rm *.bin -f 
	rm *.o -f 
	rm *.gch -f
run:
	bochs -q
rebuild:
	make clean 
	make
