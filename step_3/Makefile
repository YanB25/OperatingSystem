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
all: $(USER)/$(STONE)/stoneQ.bin $(KERNEL)/kernel.bin $(LOADER)/loader.bin build cleangch

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

build: $(LOADER)/loader.bin $(FILESYSTEM)/DBR.bin $(FILESYSTEM)/FAT.bin $(FILESYSTEM)/datablock.bin
	echo "\n"
	dd if=$(LOADER)/loader.bin of=OS.img conv=notrunc
	dd if=$(FILESYSTEM)/DBR.bin of=OS.img conv=notrunc oflag=seek_bytes seek=512
	dd if=$(FILESYSTEM)/FAT.bin of=OS.img conv=notrunc oflag=seek_bytes seek=1536
	dd if=$(FILESYSTEM)/FAT.bin of=OS.img conv=notrunc oflag=seek_bytes seek=3584
	dd if=$(FILESYSTEM)/datablock.bin of=OS.img conv=notrunc oflag=seek_bytes seek=6656
	dd if=$(KERNEL)/kernel.bin of=OS.img conv=notrunc oflag=seek_bytes seek=7680
	dd if=$(USER)/$(STONE)/stoneQ.bin of=OS.img conv=notrunc oflag=seek_bytes seek=12800
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