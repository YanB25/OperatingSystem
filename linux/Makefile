LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m32 -mpreferred-stack-boundary=2 -ffreestanding
#TODO: in pm, here should be -m32 not -m16
AS=nasm
ASFLAGS=


all: write_os_img
BOOT=boot
ALL_BIN = ${BOOT}/boot.bin ${BOOT}/setup.bin tools/system
write_os_img: ${ALL_BIN}
	dd if=boot/boot.bin of=OS.img bs=512 count=1 conv=notrunc
	dd if=boot/setup.bin of=OS.img bs=512 count=4 conv=notrunc seek=1
	dd if=tools/system of=OS.img bs=512 count=24 conv=notrunc seek=5

boot/boot.bin: boot/boot.s
	@make -C boot/
boot/setup.bin: boot/setup.s
	@make -C boot/
boot/head.o: boot/head.s
	@make -C boot/

clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.bin" -delete

init/main.o: init/main.c
	${CC} ${CCFLAGS} -c $^ -o $@
	
tools/system: boot/head.o init/main.o
	$(LD) $(LDFLAGS) -Ttext 0x0 --oformat binary -o $@ $^ -e startup_32

run:
	bochs -q