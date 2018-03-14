set -x
nasm loader.asm -o loader.bin
nasm bar.asm -o bar.bin
dd if=loader.bin of=boot.img conv=notrunc
# dd if=bar.bin of=boot.img conv=notrunc oflag=seek_bytes seek=512
dd if=section1/ul.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*1))"
dd if=section1/up.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*2))"
dd if=section1/ur.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*3))"
dd if=section1/dl.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*4))"
dd if=section1/dn.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*5))"
dd if=section1/dr.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*6))"