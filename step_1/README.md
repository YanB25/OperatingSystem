# 实验项目1
## 搭建和应用实验环境
### Problem1
产生一个虚拟软盘  
将其用 DOS 格式化为 DOS 引导盘  
Solution：  
下载bochs的DOS镜像文件，并按`.bochsrc`的方式配置bochs。
DOS镜像放在A盘，`a.img`放在B盘。
上述`a.img`即为格式化后的文件
``` shell
$ bochs
// be in the Dos system
Dos:> format b:
...
format complete
$ xxd a.image | less
```
文件介绍
``` python
.
├── a.img # formatted image
├── bochsout.log # log file
├── .bochsrc # config file
├── boot.com # a sample code
└── freedos.img # Dos image used by bochs
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
nasm汇编器产生特殊的”汇编“填满整个文件。  
使用dd将.bin文件写入.img  
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
完成`storm.asm`程序，使其在裸机上显示个人的相关信息
Solotion：
运行方式
``` shell
$ sh run.sh
```
会直接弹出bochs的虚拟机窗口，打开stone.img,并运行。
生成文件方式
``` shell
$ sh build.sh
```
## 遇到的Bugs
### mul instruction
乘的指令，当操作数为16bits时，会将高位放置到dx处
在本程序中，该行为错误地将dl置为0
见wiki mul