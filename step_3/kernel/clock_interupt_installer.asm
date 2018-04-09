[BITS 16]
global clock_install_interupt
extern timeout
extern kb_custom_interupt
%include "../include/bridge.inc"
clock_install_interupt:
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

    jmp 0F000H:0fea5H ;TODO: should not hard code

data:
    char db 'A'