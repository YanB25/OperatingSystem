LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m32 -mpreferred-stack-boundary=2 -ffreestanding
AS=nasm
ASFLAGS=

INCLUDE=include
KERNEL=kernel
LOADER=loader

all: $(KERNEL)/kernel.bin $(LOADER)/loader.bin build

$(KERNEL)/kernel.bin: $(KERNEL)/kernel.o $(INCLUDE)/utilities.o 
	$(LD) $(LDFLAGS) -Ttext 0xA100 --oformat binary -o $@ $^
$(KERNEL)/kernel.o: 
	cd $(KERNEL)/ && make
	cd ..
$(INCLUDE)/utilities.o: 
	cd $(INCLUDE)/ && make
	cd ..

$(LOADER)/loader.bin: 
	cd $(LOADER) && make
	cd ..

build: $(LOADER)/loader.bin $(KERNEL)/kernel.bin
	dd if=$(LOADER)/loader.bin of=OS.img conv=notrunc
	dd if=$(KERNEL)/kernel.bin of=OS.img conv=notrunc oflag=seek_bytes seek=512
clean:
	find . -name "*.bin" -type f -delete
	find . -name "*.o" -type f -delete
	find . -name "*.gch" -type f -delete
run:
	bochs -q
rebuild:
	make clean 
	make
