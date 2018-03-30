LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

UTILITIES=../include

all: user.o terminal.o stone.bin

user.o: user.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^
terminal.o: terminal.c $(UTILITIES)/utilities.h stone.h
	$(CC) $(CCFLAGS) -c $^

stone.bin: stone.o $(UTILITIES)/utilities.o
	$(LD) $(LDFLAGS) -Ttext 0x6C00 --oformat binary -o $@ $^
stone.o: stone.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^

$(UTILITIES)/utilities.o:
	cd $(UTILITIES)/ && make
	cd ../user/
clean:
	rm *.bin -f 
	rm *.o -f  
	rm *.gch -f
rebuild:
	make clean 
	make
