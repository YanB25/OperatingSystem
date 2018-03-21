[BITS 16]
global clear_screen
global hello_hybrid_programming
global add
global _draw_char
global puts
global putch

%include "bridge.inc"

clear_screen:
    mov ax, 03h
    int 10h
    retl

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

    retl
add:
    enter 4, 0

    mov eax, [bp+6]
    mov [esp], eax
    mov ecx, [bp+10]
    add [esp], ecx
    ; mov eax, [sp] ;TODO:bugs?

    leave
    retl

_draw_char:
    enter 0, 0

    mov ax, 0B800H
    mov gs, ax
    push di
    mov ecx, [bp + 6]
    mov edi, [bp + 10]
    mov ch, DEFAULT_STYLE
    mov [gs:di], cx

    pop di
    leave
    retl

putch:
    enter 0, 0

    mov ax, [bp+6]
    mov ah, 0EH
    mov bl, 0
    int 10H

    leave
    retl

helloStr db "hello hybrid programming!"
length equ $ - helloStr
DEFAULT_STYLE equ 0FH