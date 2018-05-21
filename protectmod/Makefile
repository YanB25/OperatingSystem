all: write_os_img

write_os_img: boot/boot.bin boot/loader.bin
	dd if=boot/loader.bin of=OS.img bs=512 count=1 conv=notrunc
	dd if=boot/boot.bin of=OS.img bs=512 count=10 conv=notrunc seek=1

boot/boot.bin: boot/boot.s
	cd boot/ && make boot.bin
boot/loader.bin: boot/loader.s
	cd boot/ && make loader.bin

run:
	bochs -q