/**
 * @file
 * @brief 
 * this file define a lot of helper macro
 * using ldt, gdt var in include/linux/head.h. but this file not directly include head.h
 * p.s. I DON'T UNDERSTAND ANY SINGLE LINE IN THIS FILE.
 * p.s. I simple copy them. =)
 */
#ifndef __SYSTEM_H_
#define __SYSTEM_H_
#include <stdint.h>
#define move_to_user_mode() \
__asm__( \
    "movl %%esp, %%eax\n" \
    "pushl $0x17\n" /* task Task0 stack segment selector!*/ \
    "pushl %%eax\n" \
    "pushfl \n"\
    "pushl $0x0f\n" /* Task0 code selector (cs) */\
    "pushl $1f\n" \
    "iret\n" \
    "1: \t movl $0x17, %%eax\n" \
    "movw %%ax, %%ds\n" \
    "movw %%ax, %%es\n" \
    "movw %%ax, %%fs\n" \
    "movw %%ax, %%gs\n" \
    :::"ax"\
)

#define sti() __asm__("sti\n"::)
#define cli() __asm__("cli\n"::)
#define nop() __asm__("nop\n"::)
#define iret() __asm__("iret\n"::)

// gate_addr 描述符地址
// type: 描述符中类型域值
// dpl: descriptor privilige level
// addr: 偏移地址
#define _set_gate(gate_addr, type, dpl, addr) \
    __asm__( \
        "movw %%dx, %%ax\n"\
        "movw %0, %%dx\n"\
        "movl %%eax, %1\n"\
        "movl %%edx, %2\n" \
        :\
        :"i"((int16_t)(0x8000 + (dpl << 13) + (type << 8))),\
        "o"(*((char*) (gate_addr))), \
        "o"(* (4 + (char*)(gate_addr))), \
        "d"((char*)(addr)), "a"(0x00080000) \
    );
#define set_intr_gate(n, addr) \
    _set_gate(&idt[n], 14, 0, addr)

#define set_trap_gate(n, addr) \
    _set_gate(&idt[n], 15, 0, addr)

#define set_system_gate(n, addr) \
    _set_gate(&idt[n], 15, 3, addr)

/**
 * @brief
 * fxxking code I don't understand
 */
#define _set_seg_desc(gate_addr, type, dpl, base, limit) {\
    *(gate_addr) = ((base) & 0xff000000) | \
        (((base) & 0x00ff0000) >> 16) | \
        ((limit) & 0xf0000) | \
        ((dpl) << 13) | \
        (0x00408000) | \
        ((type) << 8); \
    *((gate_addr) + 1) = (((base) & 0x0000ffff) << 16) | \
        ((limit) & 0x0ffff); \
}
#define _set_tssldt_desc(n ,addr, type)\
    __asm__(\
        "movw $104, %1\n" \
        "movw %%ax, %2\n" \
        "rorl $16, %%eax\n" \
        "movb %%al, %3\n" \
        "movb $"type", %4\n" \
        "movb $0x00, %5\n" \
        "movb %%ah, %6\n" \
        "rorl $16, %%eax\n" \
        ::"a"(addr), "m"(*(n)), "m"(*(n+2)), "m"(*(n+4)), \
        "m"(*(n+5)), "m"(*(n+6)), "m"(*(n+7)) \
    )
#define set_tss_desc(n, addr) _set_tssldt_desc(((char*)(n)), addr, "0x89")
#define set_ldt_desc(n, addr) _set_tssldt_desc(((char*)(n)), addr, "0x82")
#endif