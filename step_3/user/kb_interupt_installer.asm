[BITS 16]
%include "../include/bridge.inc"
extern kb_custom_interupt
global kb_interupt_install
global kb_interupt_uninstall
kb_interupt_install:
    ; install int 09: keyboard interupt
    push gs
    push es
    push ds
    pusha

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
    pop gs

    pop ecx
    jmp cx
kb_interupt_uninstall:
    push ax
    push ds

    mov ax, 0
    mov ds, ax 
    mov ax, [old_09_ip]
    mov [ds: 24H], ax
    mov ax, [old_09_cs]
    mov [ds:26H], ax

    pop ds
    pop ax
    retl

kbCallback:
    pusha
    push ds
    push es
    push gs

    mov ax, 0 
    mov ds, ax
    
    calll kb_custom_interupt

    pushf
    call far [ds:old_09_ip]

    pop gs
    pop es
    pop ds
    popa

    iret

data:
    old_09_ip dw 0
    old_09_cs dw 0