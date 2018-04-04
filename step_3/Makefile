LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

INCLUDE=include
KERNEL=kernel
LOADER=loader
ROOT=..
FILESYSTEM=filesystem
USER=user
STONE=stone
STONE_OBJ=$(USER)/$(STONE)/stoneQ.bin $(USER)/$(STONE)/stoneW.bin $(USER)/$(STONE)/stoneA.bin $(USER)/$(STONE)/stoneS.bin
all: $(STONE_OBJ) $(KERNEL)/kernel.bin $(LOADER)/loader.bin build cleangch

$(KERNEL)/kernel.bin: 
	echo "\n"
	cd $(KERNEL)/ && make
	cd $(ROOT)/

$(INCLUDE)/utilities.o: 
	echo "\n"
	cd $(INCLUDE)/ && make
	cd $(ROOT)/

$(LOADER)/loader.bin: 
	echo "\n"
	cd $(LOADER) && make
	cd $(ROOT)/

$(FILESYSTEM)/DBR.bin:
	echo "\n"
	cd $(FILESYSTEM)/ && make
	cd $(ROOT)/

$(FILESYSTEM)/FAT.bin:
	echo "\n"
	cd $(FILESYSTEM)/ && make 
	cd $(ROOT)/

$(FILESYSTEM)/datablock.bin:
	echo "\n"
	cd $(FILESYSTEM)/ && make 
	cd $(ROOT)/

$(USER)/$(STONE)/stoneQ.bin:
	echo "\n"
	cd $(USER)/ && make 
	cd $(ROOT)/
$(USER)/$(STONE)/stoneW.bin:
	echo "\n"
	cd $(USER)/ && make 
	cd $(ROOT)/
$(USER)/$(STONE)/stoneA.bin:
	echo "\n"
	cd $(USER)/ && make 
	cd $(ROOT)/
$(USER)/$(STONE)/stoneS.bin:
	echo "\n"
	cd $(USER)/ && make 
	cd $(ROOT)/


build: $(LOADER)/loader.bin $(FILESYSTEM)/DBR.bin $(FILESYSTEM)/FAT.bin $(FILESYSTEM)/datablock.bin $(STONE_OBJ)
	echo "\n"
	dd if=$(LOADER)/loader.bin of=OS.img conv=notrunc
	dd if=$(FILESYSTEM)/DBR.bin of=OS.img bs=512 conv=notrunc seek=1
	dd if=$(FILESYSTEM)/FAT.bin of=OS.img conv=notrunc seek=3 bs=512
	dd if=$(FILESYSTEM)/FAT.bin of=OS.img conv=notrunc seek=7 bs=512
	dd if=$(FILESYSTEM)/datablock.bin of=OS.img conv=notrunc bs=512 seek=13
	dd if=$(KERNEL)/kernel.bin of=OS.img conv=notrunc seek=15 bs=512
	dd if=$(USER)/$(STONE)/stoneQ.bin of=OS.img conv=notrunc seek=25 bs=512
	dd if=$(USER)/$(STONE)/stoneW.bin of=OS.img conv=notrunc seek=29 bs=512
	dd if=$(USER)/$(STONE)/stoneA.bin of=OS.img conv=notrunc seek=33 bs=512
	dd if=$(USER)/$(STONE)/stoneS.bin of=OS.img conv=notrunc seek=37 bs=512
clean:
	echo "\n"
	find . -name "*.bin" -type f -delete
	find . -name "*.o" -type f -delete
	find . -name "*.gch" -type f -delete
run:
	bochs -q
rebuild:
	make clean 
	clear
	make
auto:
	make rebuild
	make run
cleangch:
	find . -name "*.gch" -type f -delete