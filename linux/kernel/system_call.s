;TODO: maybe bugs check twice
extern sys_call_table
;extern schedule
extern do_signal
extern jiffies
extern do_timer
extern current
extern task
extern I_AM_HERE
extern sys_save
extern sys_restart
extern schedule

global timer_interrupt
global system_call
global return_from_timer_interrupt
global return_from_sys_restart

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
    ; push dword ret_from_sys_call ;TODO: not
    ;jmp schedule ;TODO: in file sched.c, not imple yet

system_call:

    cmp eax, nr_system_calls
    ja bad_sys_call
    push eax
    push ecx
    push edx
    push ebx
    push 0; false push esp
    push ebp
    push esi
    push edi
    push es
    push ss
    push ds
    push fs
    push gs
    sub esp, 4
    mov [esp], esp

    call sys_save
    mov eax, [esp + 4 *13]

    mov edx, 0x10
    mov ds, edx
    mov es, edx
    mov fs, edx
    mov gs, edx

    call [sys_call_table + 4 * eax] ;TODO: probably it is correct. not pretty sure
    push eax ;sys call return value

.final:
    pop eax
    add esp, 4
    pop gs
    pop fs
    pop ds
    pop ss
    pop es
    pop edi
    pop esi
    pop ebp
    add esp, 4
    pop ebx
    pop edx
    pop ecx
    pop eax ;TODO: very important!! eax is wrong!!

    iret


timer_interrupt:
    xchg bx, bx
    push eax
    push ecx
    push edx
    push ebx

    push 0; false push esp
    push ebp
    push esi
    push edi

    push es
    push ss
    push ds
    push fs
    push gs

    ;
    ; set to same
    mov eax, 0x10
    mov es, eax
    mov ss ,eax
    mov ds, eax
    mov fs, eax
    mov gs, eax

    sub esp, 4
    mov [esp], esp

    call sys_save
return_from_timer_interrupt:
    ; for debug: calling I_AM_HERE
    push 20
    call I_AM_HERE
    add esp, 4

    ; for open hardware 8259A
    mov al, 0x20
    out 0x20, al
    
    xchg bx, bx;NOTICE: delete me
    call schedule
    push eax
    call sys_restart
return_from_sys_restart:
    add esp, 4
    pop gs
    pop fs
    pop ds
    pop ss
    pop es
    pop edi
    pop esi
    pop ebp
    add esp, 4 ; false pop
    pop ebx
    pop edx
    pop ecx
    pop eax
    iret

    ; a c d b
    ; sp bp si di
    ; es cs ss ds fs gs

sys_execve:
    jmp $ ; TODO: NIY
sys_fork:
    jmp $ ; TODO: NIY


