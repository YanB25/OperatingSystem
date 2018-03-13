set -x
nasm bar.asm -o bar.bin
nasm loader.asm -o loader.bin
# dd if=bar.bin of=bar.img bs=512 count=1 conv=notrunc
dd if=loader.bin of=boot.img conv=notrunc
dd if=bar.bin of=boot.img conv=notrunc oflag=seek_bytes seek=512