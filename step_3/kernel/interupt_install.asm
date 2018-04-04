[BITS 16]
global install_interupt
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
    ; mov ax, 0B800H
    ; mov gs, ax 
    ; inc byte [char]
    ; mov al, [char]
    ; mov [gs:0], al
    ; mov byte [gs:1], 0FH
    jmp 0F000H:0fea5H

data:
    char db 'A'
    old_CS dw 0
    old_IP dw 0