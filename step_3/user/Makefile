LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

UTILITIES=../include
STONE_OBJ=stoneQ.o stoneW.o stoneA.o stoneS.o
all: user.o terminal.o $(STONE_OBJ)

user.o: user.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^
terminal.o: terminal.c $(UTILITIES)/utilities.h stone.h
	$(CC) $(CCFLAGS) -c $^

stoneQ.o: stone.c $(UTILITIES)/utilities.h stone_helper.h
	$(CC) $(CCFLAGS) -c $< -D LU -o $@
stoneW.o: stone.c $(UTILITIES)/utilities.h stone_helper.h
	$(CC) $(CCFLAGS) -c $< -D RU -o $@
stoneA.o: stone.c $(UTILITIES)/utilities.h stone_helper.h
	$(CC) $(CCFLAGS) -c $< -D LD -o $@
stoneS.o: stone.c $(UTILITIES)/utilities.h stone_helper.h
	$(CC) $(CCFLAGS) -c $< -D RD -o $@

clean:
	rm *.bin -f 
	rm *.o -f  
	rm *.gch -f
rebuild:
	make clean 
	make
