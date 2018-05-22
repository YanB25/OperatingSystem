[BITS 32]
; NOTICE:
; this file is only used as workaround
global putch
;TODO: should use cursor information
putch:
    enter 0, 0
    push ebx
    push ds
    mov eax, 0x20 ;NOTICE: hardcode for video selector
    mov ds, ax

    mov byte bl, [ebp + 8]
    mov byte bh, 0FH

    mov word [0], bx

    pop ds
    pop ebx

    leave
    ret