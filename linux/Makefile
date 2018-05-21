all: write_os_img
BOOT=boot
ALL_BIN = ${BOOT}/boot.bin ${BOOT}/setup.bin ${BOOT}/head.bin
write_os_img: ${ALL_BIN}
	dd if=boot/boot.bin of=OS.img bs=512 count=1 conv=notrunc
	dd if=boot/setup.bin of=OS.img bs=512 count=4 conv=notrunc seek=1
	dd if=boot/head.bin of=OS.img bs=512 count=24 conv=notrunc seek=5

boot/boot.bin: boot/boot.s
	cd boot/ && make boot.bin
boot/setup.bin: boot/setup.s
	cd boot/ && make setup.bin
boot/head.bin: boot/head.s
	cd boot/ && make head.bin
clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.bin" -delete

run:
	bochs -q