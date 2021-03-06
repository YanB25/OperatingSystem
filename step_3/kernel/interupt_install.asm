[BITS 16]
%include "context_switch"
global install_interupt
extern timeout
install_interupt:
    push es
    push ds
    pusha

    mov ax, cs
    mov ds, ax
    xor ax, ax 
    mov es, ax 
    ; ;cli
    ; sti
    mov word [es: 20H], timeOut
    mov ax, cs
    mov word [es: 22H], ax

    popa
    pop ds 
    pop es

    pop ecx
    jmp cx

timeOut:

    pusha
    push gs

    push cs 
    call timeout

    pop gs
    popa

    jmp 0F000H:0fea5H

data:
    char db 'A'
    old_CS dw 0
    old_IP dw 0