;TODO: maybe bugs check twice
extern sys_call_table
extern schedule
extern do_signal
extern jiffies
extern do_timer
extern current
extern task
extern I_AM_HERE

global timer_interrupt
global system_call

offEAX equ 00H
offEBX equ 0x04
offECX equ 0x08
offEDX equ 0x0C
offFS equ 0x10
offES equ 0x14
offDS equ 0x18
offEIP equ 0x1C
offCS equ 0x20
offEFLAGS equ 0x24
offOLDESP equ 0x28
offOLDSS equ 0x2C

state equ 0
counter equ 4
priority equ 8
signal equ 12
sigaction equ 16
blocked equ 33 * 16

nr_system_calls equ 72

bad_sys_call:
    mov eax, -1
    iret

reschedule:
    push dword ret_from_sys_call
    jmp schedule ;TODO: in file sched.c, not imple yet

system_call:
    cmp eax, nr_system_calls
    ja bad_sys_call
    push ds
    push es 
    push fs
    push edx
    push ecx
    push ebx
    mov edx, 0x10
    mov ds, dx
    mov es, dx
    mov edx, 0x17 ;TODO: LDT?? where is LDT?? what?
    mov fs, dx ;TODO: so???

    call [sys_call_table + 4 * eax] ;TODO: probably it is correct. not pretty sure
    push eax ;sys call return value

    ;NOTICE: 抢占式。可以不这样实现
    ; mov eax, [current] ; current is a pointer. TODO: is it right?
    ; cmp 0, [state + eax]
    ; jne reschedule ; not standby
    ; cmp 0, [counter + eax]
    ; je reschedule

ret_from_sys_call:
    ;TODO: delete it, only for debug
    push dword 5
    call I_AM_HERE
    add esp, 4
    ;TODO: 不考虑信号量，也就不需要这些代码了
    ; mov eax, [current]
    ; cmp eax, [task] ;TODO: maybe BUGs
    ; je .final

    ; cmp word [esp + offCS], 0x0F
    ; jne .final

    ; cmp word 0x17, [esp + offOLDSS]
    ; jne .final

    ;TODO: 不考虑信号量
    ; mov ebx, [signal + eax]
    ; mov ecx, [blocked + eax]
    ; not ecx
    ; and ecx, ebx
    ; bsf ecx, ecx
    ; je .final
    ; btr ebx, ecx
    ; mov [signal + eax], ebx
    ; inc ecx
    ; push ecx
    ; call do_signal
    ; pop eax ;no, it is deliberately duplecated.
.final:
    pop eax
    pop ebx
    pop ecx
    pop edx
    pop fs
    pop es
    pop ds
    iret


timer_interrupt:
    push ds
    push es
    push fs
    push edx
    push ecx
    push ebx
    push eax
    mov eax, 0x10
    mov ds, ax
    mov es, ax
    mov eax, 0x17
    mov fs, ax ;TODO: 0x17 again
    inc dword [jiffies]
    ; EOI
    mov al, 0x20
    out 0x20, al ;TODO: order correct?
    mov eax, [esp + offCS]
    and eax, 0x3 ;cpl
    push eax
    call do_timer
    add esp, 0x4

    jmp ret_from_sys_call

sys_execve:
    jmp $ ; TODO: NIY
sys_fork:
    jmp $ ; TODO: NIY