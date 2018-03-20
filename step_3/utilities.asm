[BITS 16]
global clear_screen
global hello_hybrid_programming
global add

clear_screen:
    mov ax, 03h
    int 10h
    pop ecx
    jmp cx

hello_hybrid_programming:
    mov ah, 13H
    mov al, 1
    mov bl, 0FH
    mov bh, 0
    mov dh, 5
    mov dl, 5
    ; mov es, ??
    mov bp, helloStr
    mov cx, length
    int 10H

    pop ecx
    jmp cx

add:
    pop ecx 
    jmp cx

helloStr db "hello hybrid programming!"
length equ $ - helloStr