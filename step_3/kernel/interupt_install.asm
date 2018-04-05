[BITS 16]
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
    push ds 
    push es

    pusha
    push gs

    push cs 
    call timeout

    mov al, 20H
    out 20H, al
    out 0A0H, al

    pop gs
    popa

    pop es 
    pop ds

    iret
    ; jmp 0F000H:0fea5H

data:
    char db 'A'
    old_CS dw 0
    old_IP dw 0