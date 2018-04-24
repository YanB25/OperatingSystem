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

USER_HEADER=$(USER)/terminal.h 
USER_OBJ=$(USER)/terminal.o $(USER)/kb_interupt_installer.o $(USER)/kbhit.o
INT_OBJ=clock_interupt_installer.o global_custom_int_installer.o timeout.o custom_interupt.o
PCB_OBJ=PCBManager.o
all: kernel.bin

kernel.bin: kernel.o $(INCLUDE)/utilities.o $(USER_OBJ) $(INCLUDE)/mystring.o $(FILESYSTEM)/fsutilities.o $(INT_OBJ) $(PCB_OBJ)
	$(LD) $(LDFLAGS) -Ttext 0xA200 --oformat binary -o $@ $^
kernel.o: kernel.c kernel.h $(INCLUDE)/utilities.h $(USER_HEADER) $(FILESYSTEM)/API/fsapi.h
	$(CC) $(CCFLAGS) -c $^
clock_interupt_installer.o: clock_interupt_installer.asm 
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^
global_custom_int_installer.o: global_custom_int_installer.asm 
	$(AS) $(ASFLAGS) -f elf32 -o $@ $^
timeout.o: timeout.c
	$(CC) $(CCFLAGS) -c $^
custom_interupt.o : custom_interupt.c
	$(CC) $(CCFLAGS) -c $^
PCBManager.o: PCBManager.c
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
$(USER)/kb_interupt_installer.o:
	cd $(USER)/ && make 
	cd ../kernel
$(USER)/kbkit.o:
	cd $(USER)/ && make 
	cd ../kernel
clean:
	rm *.bin -f 
	rm *.o -f  
	rm *.gch -f
rebuild:
	make clean 
	make
