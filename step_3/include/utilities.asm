[BITS 16]
global clear_screen
global hello_hybrid_programming
global add
global _draw_char
global puts
global putch
global kbhit
global readkb

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
    mov eax, [esp]
    leave
    retl

_draw_char:
    ; enter 0, 0

    ; mov ax, 0B800H
    ; mov gs, ax
    ; push di
    ; mov ecx, [bp + 6] ; char
    ; mov edi, [bp + 10] ; offset
    ; mov ch, [bp + 14] ; style
    ; mov [gs:di], cx

    ; pop di
    ; leave
    ; mov ax, 1
    ; retl

    ;;; new version:
    enter 0, 0
    push edi

    mov ecx, [bp + 6]
    mov edi, [bp + 10]
    mov ch, [bp + 14]

    mov ah, 1
    int 2BH

    pop edi
    leave 
    mov ax, 1
    retl

putch:
    enter 0, 0

    mov ax, [bp+6]
    mov ah, 0EH
    mov bl, 0
    int 10H

    leave
    mov ax, 1
    retl

readkb:
    enter 0, 0

    xor eax, eax
    int 16H
    xor ah, ah ; IMPORTANT: ah should be 0
    leave
    retl

kbhit:
    enter 0, 0

    xor ax, ax
    mov ah, 1
    int 16H
    cmp ah, 1
    jne .ret

.nokeypress:
    xor eax, eax

.ret:
    leave
    retl



helloStr db "hello hybrid programming!"
length equ $ - helloStr
DEFAULT_STYLE equ 0FH