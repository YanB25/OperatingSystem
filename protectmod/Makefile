all: write_os_img

write_os_img: boot/boot.bin
	dd if=boot/boot.bin of=OS.img bs=512 count=2 conv=notrunc

boot/boot.bin: boot/boot.s
	cd boot/ && make boot.bin

run:
	bochs -q