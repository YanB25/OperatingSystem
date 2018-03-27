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
all: $(LOADER)/loader.bin build cleangch

$(KERNEL)/kernel.bin: 
	cd $(KERNEL)/ && make
	cd $(ROOT)/

$(INCLUDE)/utilities.o: 
	cd $(INCLUDE)/ && make
	cd $(ROOT)/

$(LOADER)/loader.bin: 
	cd $(LOADER) && make
	cd $(ROOT)/

$(FILESYSTEM)/DBR.bin:
	cd $(FILESYSTEM)/ && make
	cd $(ROOT)/

$(FILESYSTEM)/FAT.bin:
	cd $(FILESYSTEM)/ && make 
	cd $(ROOT)/

$(FILESYSTEM)/datablock.bin:
	cd $(FILESYSTEM)/ && make 
	cd $(ROOT)/

build: $(LOADER)/loader.bin $(FILESYSTEM)/DBR.bin $(FILESYSTEM)/FAT.bin $(FILESYSTEM)/datablock.bin
	dd if=$(LOADER)/loader.bin of=OS.img conv=notrunc
	dd if=$(FILESYSTEM)/DBR.bin of=OS.img conv=notrunc oflag=seek_bytes seek=512
	dd if=$(FILESYSTEM)/FAT.bin of=OS.img conv=notrunc oflag=seek_bytes seek=1536
	dd if=$(FILESYSTEM)/FAT.bin of=OS.img conv=notrunc oflag=seek_bytes seek=3584
	dd if=$(FILESYSTEM)/datablock.bin of=OS.img conv=notrunc oflag=seek_bytes seek=5632
clean:
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