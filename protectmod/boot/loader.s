 [BITS 16]
global _start

;SEG equ 0x7C0
;KERNEL equ 0x800

_start:
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    jmp load_kernel

load_kernel:
    mov cl, 2

    ;below set load target memory to KERNEL:0
    mov ax, 0x800
    mov es, ax
    mov bx, 0
    ; cl
    ; bx
    mov ah, 2 ; function number
    mov al, 10 ; load two sector
    mov dl, 0; 0 for fd
    mov dh, 0; head
    mov ch, 0 ; low 8 bits of cyl
    int 13H

jmp2KERNEL:
    jmp 0:0x8000 

blank:
    times 444-($-$$) db 0
partition_table:
.first:
    ; TODO: partition table in MBR
    times 510-($-$$) db 0
dw 0xAA55