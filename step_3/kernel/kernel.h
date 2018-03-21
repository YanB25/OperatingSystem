#ifndef __KERNEL_H_
#define __KERNEL_H_
// __asm__(".code16gcc\n");
__asm__(".globl _start\n");
__asm__("_start:\n");
__asm__("mov $0, %eax\n");
__asm__("mov %ax, %ds\n");
__asm__("mov %ax, %es\n");
__asm__("jmpl $0, $main\n");
#endif