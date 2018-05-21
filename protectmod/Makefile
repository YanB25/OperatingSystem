all: write_os_img
BOOT=boot
ALL_BIN = ${BOOT}/boot.bin ${BOOT}/head.bin
write_os_img: ${ALL_BIN}
	dd if=boot/boot.bin of=OS.img bs=512 count=1 conv=notrunc
	dd if=boot/head.bin of=OS.img bs=512 count=10 conv=notrunc seek=1

boot/boot.bin: boot/boot.s
	cd boot/ && make boot.bin
boot/head.bin: boot/head.s
	cd boot/ && make head.bin

clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.bin" -delete

run:
	bochs -q