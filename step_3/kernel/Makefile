LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m32 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

ROOT=..
INCLUDE=../include
all: kernel.bin

kernel.bin: kernel.o $(INCLUDE)/utilities.o 
	$(LD) $(LDFLAGS) -Ttext 0xA100 --oformat binary -o $@ $^
kernel.o: kernel.c kernel.h $(INCLUDE)/utilities.h
	$(CC) $(CCFLAGS) -c $^
$(INCLUDE)/utilities.o:
	cd $(INCLUDE)/ && make
	cd ../kernel
clean:
	rm *.bin -f 
	rm *.o -f  
	rm *.gch -f
rebuild:
	make clean 
	make
