LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

UTILITIES=../include
STONE_OBJ=stone/%.o
all: user.o terminal.o $(STONE_OBJ)

user.o: user.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^
terminal.o: terminal.c $(UTILITIES)/utilities.h stone/stone.h
	$(CC) $(CCFLAGS) -c $^

$(STONE_OBJ): stone/stone.c $(UTILITIES)/utilities.h stone/stone_helper.h
	$(CC) $(CCFLAGS) -c $< -D LU -o stone/stoneQ.o
	$(CC) $(CCFLAGS) -c $< -D RU -o stone/stoneW.o
	$(CC) $(CCFLAGS) -c $< -D LD -o stone/stoneA.o
	$(CC) $(CCFLAGS) -c $< -D RD -o stone/stoneS.o

clean:
	rm *.bin -f 
	rm *.o -f  
	rm *.gch -f
rebuild:
	make clean 
	make
