set -x
nasm stone.asm -o stone.com
dd if=stone.com of=stone.img bs=512 count=1 conv=notrunc