# OperatingSystem
操作系统实验课课程项目  
本项目将长期更新，并按照本学期操作系统课程的进度逐步完成。  
其中每个文件夹代表每次可提交的课程作业（或里程碑式事件）  
本项目打算以.pdf和.latex的方式，公开以往的所有项目报告  
[点此查看实验六的实验报告(首次实现进程切换的实验)](https://github.com/YanB25/OperatingSystem/blob/master/report/16337269_%E9%A2%9C%E5%BD%AC_%E5%AE%9E%E9%AA%8C%E5%85%AD.pdf)
## 介绍
使用`git tag`和`git checkout`查看项目完成的各个阶段。  
`/step_0`到`/step_2`是一些demo代码，**后续所有代码都在`/step_3`上完成**   
`/linux`文件夹存放的是linux系统的早期版本的内核，用于学习用途  
`/protectmod`存放的是我试图进入保护模式完成实验的一些代码。这部分代码最终没有成功(无法完成进程切换)故暂时弃置了。
想要了解项目的具体情况，可以`git checkout`到具体的版本上，并查看实验报告`/report/16337269_颜彬_实验*.pdf`
## file-list
1. [step three][4]
It will be a tough war.  
~~C语言和汇编混合编程。如果在linux下失败，可能整个项目会重构并在windows下实现。~~  
linux下工具链：编译器gcc，连接器ld。  
成功。本实验可以继续在linux下进行。  
step_3大量参考了日哥的解决方案，其`github`地址见 //TODO:address
本实验从以往的`shell`脚本编译运行改为了`makefile`编译运行。  
1. [step two][3]  
操作系统的第二个项目。  
主要内容为学习调用`bios`
1. [step one][1]
操作系统实验的第一个项目。  
项目中的sectoin1和section2都是热身，其任务要求[见此][1]  
任务3要求制作引导程序。引导程序要求可以在裸机上运行，且输出动画和个人信息。
1. [step zero][2]
操作系统的第＂零＂个项目
该项目中包含一个＂样例程序＂，用来检测自己的环境是否搭配完成
该样例程序可以正确在裸机上运行。正确运行时，其输出Hello World
## How-to
### understand files
在根目录下，有若干文件夹`step_{{i}}`  
其中每个文件夹都是一次提交的项目  
`step_{{i}}`内可能有若干`section{{i}}`  
每个`section`代表本次项目需要解决的一个分支问题。  
### run
每个`step_{{i}}`内都有一份`README.md`  
请阅读相应的文件了解各次项目的实验目的和运行方式  
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
