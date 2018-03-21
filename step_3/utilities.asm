[BITS 16]
global clear_screen
global hello_hybrid_programming
global add
global _put_char

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
    ; mov eax, [sp] ;TODO:bugs?

    leave
    pop ecx
    jmp cx

_put_char:
    enter 0, 0

    mov ax, 0B800H
    mov gs, ax
    push di
    mov ecx, [bp + 6]
    mov edi, [bp + 10]
    mov ch, 0FH
    mov [gs:di], cx

    pop di
    leave
    pop ecx
    jmp cx

helloStr db "hello hybrid programming!"
length equ $ - helloStr