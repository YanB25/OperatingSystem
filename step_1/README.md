# 实验项目1
## 搭建和应用实验环境
### Problem1
将其中一个虚拟软盘用 DOS 格式化为 DOS 引导盘
Solution：
``` python
.
├── a.img # formatted image
├── bochsout.log # log file
├── .bochsrc # config file
├── boot.com # a sample code
└── freedos.img # Dos image used by bochs
```
上述`a.img`即为格式化后的文件
``` shell
$ bochs
// be in the Dos system
Dos:> format b:
...
format complete
$ xxd a.image | less
```
### Problem2
用 WinHex 工具将其中一个虚拟软盘的首扇区填满你的个人信息
Solution:
``` x86/asm
; in file fill.asm
times 32 db "16337269 yanbin "
```
``` shell
$ nasm fill.asm -o fill.bin
$ dd if=fill.bin of=fill.img
$ xxd fill.img | less
```
```
# some output
00000000: 3136 3333 3732 3639 2079 616e 6269 6e20  16337269 yanbin
00000010: 3136 3333 3732 3639 2079 616e 6269 6e20  16337269 yanbin
00000020: 3136 3333 3732 3639 2079 616e 6269 6e20  16337269 yanbin
...
...
000001f0: 3136 3333 3732 3639 2079 616e 6269 6e20  16337269 yanbin
```

## 接管裸机控制权
### Problem3
运动变化A
特效
个人信息