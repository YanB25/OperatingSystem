set -x
nasm stone.asm -o ul.bin -d DEBUG -d UL
nasm stone.asm -o up.bin -d DEBUG -d UP
nasm stone.asm -o ur.bin -d DEBUG -d UR
nasm stone.asm -o dl.bin -d DEBUG -d DL
nasm stone.asm -o dn.bin -d DEBUG -d DN
nasm stone.asm -o dr.bin -d DEBUG -d DR
# dd if=ul.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*0))"
# dd if=up.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*1))"
# dd if=ur.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*2))"
# dd if=dl.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*3))"
# dd if=dn.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*4))"
# dd if=dr.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*5))"