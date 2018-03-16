# step 2
## 任务
写一个调度程序，允许将用户程序加载进内存并运行。  
其中用户程序应有四个以上（本项目做了6个，在`step1`的程序的基础上修改）。  
调度程序应能正确地将四个不同的用户程序加载入内存并运行（用键盘控制）
## Solution
本项目超额完成了这个任务。  
首先本项目通过`nasm`的宏，做了六个不同的用户程序。  
可以见`userCodes/stone.asm`和`userCodes/build.sh`研究如何通过宏编译。  
本项目还写了`Utilities/utility.asm`，该文件将常用的函数封装成系统调用，统一地整理在内存的某个位置。该文件将被载入到内存的`0xA100`位置。  
其余六个不同的用户程序，第`i`个放在`0xA300 + 200H * i`的位置（i从1算起）
## 文件介绍
<pre>
.
├── bochsout.log # log file
├── boot.img # image used to boot
├── build.sh
├── loader.asm # source code. compile into boot.img
├── loader.bin
├── README.md
├── run.sh
├── userCodes
│   ├── bochsout.log
│   ├── build.sh # use macro here to generate 6 user files
│   ├── dl.bin
│   ├── dn.bin
│   ├── dr.bin
│   ├── run.sh
│   ├── stone.asm # course code of user file.
│   ├── ul.bin
│   ├── up.bin
│   └── ur.bin
└── Utilities
    ├── build.sh
    ├── run.sh
    ├── utility.asm # group frequently-used code into this file
    └── utility.bin

2 directories, 21 files

</pre>
## 严重的BUG
### 栈溢出
很有可能发生了栈溢出，代码段和数据段被中断调用修改了．具体DEBUG情况如下．
<pre>
(0) [0x000000000000a481] 0000:a481 (unk. ctxt): int 0x16                  ; cd16
<bochs:32>
<strong>(0) Caught write watch point at 0x000000000000a4b0</strong>
Next at t=38737314
(0) [0x00000000000f05f1] f000:05f1 (unk. ctxt): push ds                   ; 1e



(0) [0x000000000000a482] 0000:a482 (unk. ctxt): mov ah, 0x01              ; b401
<bochs:29> n
Next at t=32029212
(0) [0x000000000000a484] 0000:a484 (unk. ctxt): int 0x16                  ; cd16
<bochs:30> n
<strong>(0) Caught write watch point at 0x000000000000a4b2</strong>
Next at t=32029254
(0) [0x00000000000f05ee] f000:05ee (unk. ctxt): mov bp, sp                ; 89e5
<bochs:31>

watch 0xa4b3
</pre>
可能原因是，一个开始将`rsp`定位到了程序所在扇区的末尾．而扇区末尾距离程序的末尾的距离比较近，导致栈溢出  

问：bios中断调用不会自动切换运行栈的吗
###　数据长度错误
一个应为`dw`的数据段，不小心写成了`db`．在某些情况下（数据只有低位），程序能正确运行．但总会出现bug（且很难找到必然的复现方式）