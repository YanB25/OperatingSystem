[BITS 16]
global _start

_start:
    mov ax, 0
    mov ds, ax
    mov es, ax

    mov dx, 1 ; count
    mov cl, 2
    mov bx, kernel_address
.Loop:
    push dx 
    push cx

    call load_kernel

    pop cx
    pop dx
    inc dx
    inc cl
    add bx, 0200H
    cmp dx, 10
    jle .Loop

.jmp2kernel:
    mov bx, kernel_address
    jmp bx
    hlt

load_kernel:
    ; cl
    ; bx
    mov ax, 0
    mov es, ax ; which segment to load
    mov ah, 2 ; function number
    mov al, 1 ; load one sector
    mov dx, 0 ; dl = 0 for floppy disk, dh = 0 for 0 head
    mov ch, 0 
    int 13H
    ret
times 510-($-$$) db 0
dw 0xAA55
kernel_address equ 0xA100