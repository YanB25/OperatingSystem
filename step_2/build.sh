set -x
nasm loader.asm -o loader.bin
(cd userCodes/ && ./build.sh && cd ..)
(cd Utilities/ && ./build.sh && cd ..)
dd if=loader.bin of=boot.img conv=notrunc
dd if=Utilities/utility.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*1))"
dd if=userCodes/ul.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*2))"
dd if=userCodes/up.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*3))"
dd if=userCodes/ur.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*4))"
dd if=userCodes/dl.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*5))"
dd if=userCodes/dn.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*6))"
dd if=userCodes/dr.bin of=boot.img conv=notrunc oflag=seek_bytes seek="$((512*7))"