LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

ROOT=..
INCLUDE=../include
USER=../user
FILESYSTEM=../filesystem
STONE=stone

USER_HEADER=$(USER)/user.h $(USER)/terminal.h 
USER_OBJ=$(USER)/user.o $(USER)/terminal.o $(USER)/$(STONE)/stoneQ.o

all: kernel.bin

kernel.bin: kernel.o $(INCLUDE)/utilities.o $(USER_OBJ) $(INCLUDE)/mystring.o $(FILESYSTEM)/fsutilities.o
	$(LD) $(LDFLAGS) -Ttext 0xA200 --oformat binary -o $@ $^
kernel.o: kernel.c kernel.h $(INCLUDE)/utilities.h $(USER_HEADER) $(FILESYSTEM)/API/fsapi.h
	$(CC) $(CCFLAGS) -c $^
$(INCLUDE)/utilities.o:
	cd $(INCLUDE)/ && make
	cd ../kernel
$(USER)/user.o:
	cd $(USER)/ && make
	cd ../kernel
$(INCLUDE)/mystring.o:
	cd $(INCLUDE)/ && make 
	cd ../kernel
$(FILESYSTEM)/fsutilities.o:
	cd $(FILESYSTEM)/ && make 
	cd ../kernel
$(USER)/$(STONE)/stoneQ.o:
	cd $(USER)/ && make
	cd ../kernel
clean:
	rm *.bin -f 
	rm *.o -f  
	rm *.gch -f
rebuild:
	make clean 
	make
