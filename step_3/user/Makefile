LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

UTILITIES=../include

all: user.o terminal.o stone.o

user.o: user.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^
terminal.o: terminal.c $(UTILITIES)/utilities.h stone.h
	$(CC) $(CCFLAGS) -c $^
stone.o: stone.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^

clean:
	rm *.bin -f 
	rm *.o -f  
	rm *.gch -f
rebuild:
	make clean 
	make
