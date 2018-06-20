LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-march=i386 -m32 -mpreferred-stack-boundary=2 -ffreestanding -g 
#TODO: in pm, here should be -m32 not -m16
AS=nasm
ASFLAGS=


all: write_os_img kernel/system_call.o
BOOT=boot
ALL_BIN = ${BOOT}/boot.bin ${BOOT}/setup.bin tools/system tools/system.elf
# NOTICE: printk_tmp.o only used as workaround
SYSTEM_OBJ=boot/head.o init/main.o kernel/asm.o kernel/traps.o init/testscript.o kernel/printk.o kernel/printk_tmp.o kernel/system_call.o kernel/sched.o kernel/semaphore.o
SYSTEM_H=include/linux/semaphore.h
# TODO: remember to link system_call.o into it
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

lib/string.o: lib/string.c
	@make -C lib/ string.o

kernel/asm.o: kernel/asm.s
	@make -C kernel/
kernel/traps.o: kernel/traps.c
	@make -C kernel/
kernel/printk.o: kernel/printk.c
	@make -C kernel/
kernel/printk_tmp.o: kernel/printk.s
	@make -C kernel/
kernel/system_call.o: kernel/system_call.s
	@make -C kernel/
kernel/sched.o: kernel/sched.c include/linux/sys.h
	@make -C kernel/
kernel/fork.o: kernel/fork.c
	@make -C kernel/ fork.o
kernel/semaphore.o: kernel/semaphore.c
	@make -C kernel/ semaphore.o
kernel/vsprintf.o: kernel/vsprintf.c
	@make -C kernel/ vsprintf.o

init/testscript.o: init/testscript.s
	$(AS) $(ASFLAGS) -f elf -o $@ $^

clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.bin" -delete

init/main.o: init/main.c
	${CC} ${CCFLAGS} -c $^ -o $@
	
tools/system: $(SYSTEM_OBJ)
	$(LD) $(LDFLAGS) -Ttext 0x0 --oformat binary -o $@ $^ -e startup_32

tools/system.elf: $(SYSTEM_OBJ)
	$(LD) $(LDFLAGS) -Ttext 0x0 -o $@ $^ -e startup_32
	objdump -Sl tools/system.elf > tools/debug
run:
	bochs -q