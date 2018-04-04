[BITS 16]
global install_interupt
install_interupt:
    push es
    push ds
    pusha

    xor ax, ax 
    mov es, ax 
    ; ;cli
    ; sti
    mov word [es: 20H], timeOut
    mov ax, cs
    mov word [es: 22H], ax
    mov ds, ax 
    mov es, ax 

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
    mov al, 20H
    out 20H, al 
    out 0A0H, al 
    iret

data:
    char db 'A'