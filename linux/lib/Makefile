LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-m32 -mpreferred-stack-boundary=2 -ffreestanding -g
#TODO: in pm, here should be -m32 not -m16
#TODO: delete -march=i386
AS=nasm
ASFLAGS=

string.o: string.c
	$(CC) $(CCFLAGS) -c $^