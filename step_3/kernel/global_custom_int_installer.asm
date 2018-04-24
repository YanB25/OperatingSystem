; custom 2BH interupt (43 base 10)
; in address
[BITS 16]
%include "../include/bridge.inc"
global global_custom_int_install
extern draw_my_info
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
    push ds
    push bx
    push ax
    push dx 

    ; sync ds, important
    push ax
    mov ax, 0
    mov ds, ax
    pop ax

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
    pop ds

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
        ; cx written data
            ; cl store showing char
            ; ch store showing style
        ; di store offset from B800(byte)
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
_int_draw_my_info:
    ;input
        ;None
    ;modify
        ;None
    ;description:
        ;print out my student id in 3-D mod
    pusha 
    push es
    push ds 

    calll draw_my_info

    pop ds 
    pop es
    popa

    retf
custom_int_table:
    dw testcase
    dw 0x0000
    dw _int_draw_char
    dw 0x0000
    dw _int_draw_my_info
    dw 0x0000