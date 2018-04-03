LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

UTILITIES=../include
STONE=stone
all: user.o terminal.o $(STONE)/stoneQ.bin $(STONE)/stoneW.bin

user.o: user.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^
terminal.o: terminal.c $(UTILITIES)/utilities.h 
	$(CC) $(CCFLAGS) -c $^

$(STONE)/stoneQ.bin: $(STONE)/stoneQ.o $(UTILITIES)/utilities.o
	$(LD) $(LDFLAGS) -Ttext 0x6C00 --oformat binary -o $@ $^
$(STONE)/stoneQ.o: $(STONE)/stone.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $< -D UL -o $@

$(STONE)/stoneW.bin: $(STONE)/stoneW.o $(UTILITIES)/utilities.o
	$(LD) $(LDFLAGS) -Ttext 0x6C00 --oformat binary -o $@ $^
$(STONE)/stoneW.o: $(STONE)/stone.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $< -D UR -o $@






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
