[BITS 16]
global _start

_start:
    mov ax, 0
    mov ds, ax
    mov es, ax

load_kernel:
    mov dx, 1 ; count
    mov cl, 2
    mov bx, DBR_address
    ; cl
    ; bx
    mov ax, 0
    mov es, ax ; which segment to load
    mov ah, 2 ; function number
    mov al, 1 ; load one sector
    mov dl, 0; 0 for fd
    mov dh, 0; head
    mov ch, 0 ; low 8 bits of cyl
    int 13H

jmp2DBR:
    mov bx, DBR_address
    jmp bx
    hlt

blank:
    times 444-($-$$) db 0
partition_table:
.first:
    ; TODO: finish me.
dw 0xAA55
DBR_address equ 0x7E00