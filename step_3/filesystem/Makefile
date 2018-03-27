LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

all: DBR.bin FATitem.bin

DBR.bin: DBR.o DBRkernelLoader.o
	$(LD) $(LDFLAGS) -Ttext 0x7E00 --oformat binary -o $@ $^ 
DBR.o: DBR.asm 
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^
DBRkernelLoader.o: DBR.c 
	$(CC) $(CCFLAGS) -c $^ -o $@

FATitem.o: FATitem.c FATMacro.h
	$(CC) $(CCFLAGS) -c $^
FATitem.bin: FATitem.o
	$(LD) $(LDFLAGS) -Tdata 0 --oformat binary -o $@ $^