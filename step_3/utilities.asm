[BITS 16]
global clear_screen
global hello_hybrid_programming
global add
global _puts

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
    enter 4, 0

    mov eax, [bp+6]
    mov [esp], eax
    mov ecx, [bp+10]
    add [esp], ecx
    mov eax, [sp]

    leave
    pop ecx
    jmp cx

_puts:
    
helloStr db "hello hybrid programming!"
length equ $ - helloStr