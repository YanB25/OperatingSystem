set -x
nasm stone.asm -o stone.bin
dd if=stone.bin of=stone.img bs=512 count=1 conv=notrunc