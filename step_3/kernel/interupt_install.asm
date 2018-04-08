[BITS 16]
global install_interupt
extern timeout
extern kb_custom_interupt
%include "../include/bridge.inc"
install_interupt:
    push es
    push ds
    pusha

    mov ax, cs
    mov ds, ax
    xor ax, ax 
    mov es, ax 

    ; install int 08: clock interupt
    mov word [es: 20H], timeOut
    mov ax, cs
    mov word [es: 22H], ax

    ; install int 09: keyboard interupt
    mov ax, 0
    mov ds, ax 
    mov ax, [ds: 24H]
    mov [old_09_ip], ax
    mov ax, [ds: 26H]
    mov [old_09_cs], ax

    mov word [ds: 24H] , kbCallback
    mov ax, cs
    mov word [ds: 26H] , ax

    popa
    pop ds 
    pop es

    pop ecx
    jmp cx

timeOut:

    pusha
    push gs
    push ds
    push es

    mov ax, cs 
    mov ds, ax 
    mov es, ax 

    push cs 
    call timeout

    pop es
    pop ds
    pop gs
    popa

    jmp 0F000H:0fea5H

kbCallback:
    push ds
    push ax
    mov ax, cs 
    mov ds, ax
    
    calll kb_custom_interupt

    pushf
    call far [ds:old_09_ip]

    pop ax 
    pop ds

    iret


data:
    char db 'A'
    old_09_ip dw 0
    old_09_cs dw 0