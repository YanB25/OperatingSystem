[BITS 32]
; NOTICE:
; this file is only used as workaround
global putch
;TODO: should use cursor information
putch:
    enter 0, 0
    push ebx
    push ds
    push si

    ; get cursor from global config selector
    mov eax, 0x28 ;NOTICE: hardcode for global config selector
    mov ds, ax
    mov word dx, [0] ; dh: dl is row:col
.ts:
    ; test and set new cursor
    mov cx, dx
    inc cx
    cmp cl, 80 ; test whether col reach bound
    jne .writeback
    mov cl, 0
    inc ch
.writeback:
    mov word [0], cx

    ; calculate offset and write to si
    mov al, dh
    mov ah, 160
    mul ah
    xor dh, dh
    add ax, dx
    add ax, dx
    mov si, ax

    mov eax, 0x20 ;NOTICE: hardcode for video selector
    mov ds, ax

    mov byte bl, [ebp + 8]
    mov byte bh, 07H

    mov word [si], bx

    pop si
    pop ds
    pop ebx

    leave
    ret

.rearenge: