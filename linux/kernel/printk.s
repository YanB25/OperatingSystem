[BITS 32]
; NOTICE:
; this file is only used as workaround
global putch 
global newline
global I_AM_HERE
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

newline:
    enter 0, 0
    push ds

    mov eax, 0x28
    mov ds, ax
    mov word dx, [0]
    xor dl, dl
    inc dh
    cmp dh, 24
    jne .writeback
    mov dh, 0
.writeback:
    mov word [0], dx

    pop ds
    leave
    ret

I_AM_HERE:
    enter 0, 0
    push ebx
    push ds

    mov eax, 0x20
    mov ds, ax
    mov ebx, [ebp + 8]
    add ebx, ebx
    inc byte [ebx]
    inc byte [ebx+1]

    pop ds
    pop ebx
    leave
    ret