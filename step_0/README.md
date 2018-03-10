# step0
## how-tos
### build
``` shell
$ sh build.sh
```
this code turn `boot.asm` to `boot.bin`
then write `boot.bin` into `boot.image`
### run
``` shell
$ sh run.sh
```
this open `bochs`, load `.bochsrc` and get startted.
## directory tree
``` python
.
├── a.img # image file written by boot.bin
├── bochsout.log # log file by bochs
├── .bochsrc # config for bochs
├── boot.asm # source code
├── boot.bin # get from boot.asm
├── build.sh
├── README.md
└── run.sh

0 directories, 8 files
```