LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

UTILITIES=../include
STONE=stone
STONE_BIN = $(STONE)/stoneQ.bin $(STONE)/stoneW.bin $(STONE)/stoneA.bin $(STONE)/stoneS.bin
all: terminal.o $(STONE_BIN) kb_interupt_installer.o kbhit.o

user.o: user.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^
terminal.o: terminal.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $^

$(STONE)/stoneQ.bin: $(STONE)/stoneQ.o $(UTILITIES)/utilities.o
	$(LD) $(LDFLAGS) -Ttext 0x0 --oformat binary -o $@ $^
$(STONE)/stoneQ.o: $(STONE)/stone.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $< -D UL -o $@

$(STONE)/stoneW.bin: $(STONE)/stoneW.o $(UTILITIES)/utilities.o
	$(LD) $(LDFLAGS) -Ttext 0x0 --oformat binary -o $@ $^
$(STONE)/stoneW.o: $(STONE)/stone.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $< -D UR -o $@

$(STONE)/stoneA.bin: $(STONE)/stoneA.o $(UTILITIES)/utilities.o
	$(LD) $(LDFLAGS) -Ttext 0x5200 --oformat binary -o $@ $^
$(STONE)/stoneA.o: $(STONE)/stone.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $< -D DL -o $@

$(STONE)/stoneS.bin: $(STONE)/stoneS.o $(UTILITIES)/utilities.o
	$(LD) $(LDFLAGS) -Ttext 0x5A00 --oformat binary -o $@ $^
$(STONE)/stoneS.o: $(STONE)/stone.c $(UTILITIES)/utilities.h
	$(CC) $(CCFLAGS) -c $< -D DR -o $@


kb_interupt_installer.o: kb_interupt_installer.asm
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^
kbhit.o: kbhit.c 
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
