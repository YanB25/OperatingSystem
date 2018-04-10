; custom 2BH interupt (43 base 10)
; in address
[BITS 16]
%include "../include/bridge.inc"
global global_custom_int_install
global_custom_int_install:
    push ds

    mov ax, 0
    mov ds, ax

    mov word [ds:2BH * 4], custom_int_handler
    mov word [ds:2BH * 4 + 2], cs

    pop ds

    retl
custom_int_handler:
    ;TODO:warning, not to use bx, maybe bug
    ; ah=01H: _draw_char
    push bx
    push ax
    push dx 

    mov dl, 4
    mov al, ah
    xor ah, ah
    mul dl
    add ax, custom_int_table
    mov bx, ax

    pop dx
    pop ax

    call far [bx]

    pop bx

    iret

testcase:
    ;input
        ; None
    ;modify
        ; None
    ;description: test
    pusha
    pusha
    pusha
    popa
    popa
    popa

    retf
_int_draw_char:
    ;input
        ; cx store showing char
        ; di store offset from B800(byte)
        ; ch store showing style
    ;modify
        ; None
    ;description:
        ; draw a char with style at B800H + offset
    push ax 
    push gs

    mov ax, 0B800H
    mov gs, ax    
    mov [gs:di], cx

    pop gs 
    pop ax 

    retf
custom_int_table:
    dw testcase
    dw 0x0000
    dw _int_draw_char
    dw 0x0000