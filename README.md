# OperatingSystem
操作系统实验课课程项目，按照本学期操作系统课程的进度逐步完成。  
[点此查看实验六的实验报告(首次实现进程切换的实验)](https://github.com/YanB25/OperatingSystem/blob/master/report/16337269_%E9%A2%9C%E5%BD%AC_%E5%AE%9E%E9%AA%8C%E5%85%AD.pdf)
## 介绍
使用`git tag`和`git checkout`查看项目完成的各个阶段。  

`/step_0`到`/step_2`是一些demo代码，是建立起该OS的一些初步尝试。**后续所有代码都在`/step_3`上完成**   
`/linux`文件夹存放的是linux系统的早期版本的内核，用于学习用途  
`/protectmod`存放的是我试图进入保护模式完成实验的一些代码。这部分代码最终没有成功(无法完成进程切换)故暂时弃置了。  

想要了解项目的具体情况，可以`git checkout`到具体的版本上，并查看实验报告`/report/16337269_颜彬_实验*.pdf`
## 更新log（outdated，后续更新见实验报告）
1. [step three][4]
C语言和汇编混合编程。 
linux下工具链：编译器gcc，连接器ld。  
成功。
1. [step two][3]  
操作系统的第二个demo项目。  
主要内容为学习调用`bios`
1. [step one][1]
操作系统实验的第一个demo项目。  
项目中的sectoin1和section2都是热身，其任务要求[见此][1]  
任务3要求制作引导程序。引导程序要求可以在裸机上运行，且输出动画和个人信息。
1. [step zero][2]
操作系统的第＂零＂个项目
该项目中包含一个＂样例程序＂，用来检测自己的环境是否搭配完成
该样例程序可以正确在裸机上运行。正确运行时，其输出Hello World
## How-to
### run
每个`step_3`内有一份`README.md`  
请阅读相应的文件了解各次项目的实验目的和运行方式，或直接阅读 Makefile
## Enviroment and Tools
- Ubuntu  
本实验在 Ubuntu 16.04 环境下进行    
- nasm
编译 16/32 位`x86`汇编代码  
- bximage  
用于产生`*.img`文件  
- bochs  
用于调试运行  
  
[1]: /step_1/README.md
[2]: /step_0/README.md
[3]: /step_2/README.md
[4]: /step_3/README.md
