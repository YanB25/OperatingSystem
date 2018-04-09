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
    pusha
    pusha
    pusha
    popa
    popa
    popa

    retf
custom_int_table:
    dw testcase
    dw 0x0000