LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m32 -mpreferred-stack-boundary=2 -ffreestanding -I ../include/
#TODO: in pm, here should be -m32 not -m16
AS=nasm
ASFLAGS=

all: asm.o traps.o
asm.o: asm.s 
	$(AS) $(ASFLAGS) -f elf -o $@ $^
traps.o: traps.c
	$(CC) $(CCFLAGS) -c $^