org 0A100H
show_address dw 0xF0F0
loader_back_address dw 0xF0F0
_show_call dw show_call
show_call:
    ; bp point to str address
    ; cx contents the length
    mov ah, 0EH
    push bx
    mov bl, 0
    mov al, '@'
    int 10H
    pop bx
    jmp [loader_back_address]