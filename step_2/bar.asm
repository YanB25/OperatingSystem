;org 0x7c00
start:
    mov al, 0
    mov ah, 0
    int 16H
    cmp al, 0
    jnz print
back:
    loop start
print:
    mov ah, 0EH
    push bx
    mov bl, 0
    cmp al, `\n`
    jz .carry
    int 10H
    pop bx
    jmp back
.carry:
    mov ah, 0EH
    mov bl, 0
    int 10H
    mov al, `\n`
    int 10H
    pop bx
    jmp back

;times 510-($-$$) db 0
;    dw 0xAA55