LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding 
AS=nasm
ASFLAGS=

all: DBR.bin datablock.bin FAT.bin

DBR.bin: DBR.o DBRkernelLoader.o fsutilities.o
	$(LD) $(LDFLAGS) -Ttext 0x7E00 --oformat binary -o $@ $^ 
DBR.o: DBR.asm 
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^
DBRkernelLoader.o: DBR.c fsutilities.h filesystem.h
	$(CC) $(CCFLAGS) -c $< -o $@ -Og

datablock.o: datablock.c FATMacro.h
	$(CC) $(CCFLAGS) -c $^
datablock.bin: datablock.o
	$(LD) $(LDFLAGS) -Tdata 0 --oformat binary -o $@ $^

FAT.bin: FAT.o 
	$(LD) $(LDFLAGS) --oformat binary -o $@ $^
FAT.o: FAT.c 
	$(CC) $(CCFLAGS) -c $^ -o $@

fsutilities.o: fsutilities.asm
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^