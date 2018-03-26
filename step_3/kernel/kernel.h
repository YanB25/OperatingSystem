#ifndef __KERNEL_H_
#define __KERNEL_H_
// __asm__(".code16gcc\n");
__asm__(".intel_syntax noprefix\n");
__asm__(".globl _start\n");
__asm__("_start:\n");
__asm__("mov eax, 0\n");
__asm__("mov ds, ax\n");
__asm__("mov es, ax\n");
__asm__("jmp 0: main\n");
__asm__(".att_syntax\n");
#endif