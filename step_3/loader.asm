[BITS 16]
global _start

_start:
    mov ax, 0
    mov ds, ax
    mov es, ax

    mov cl, 2
    mov bx, kernel_address
.load_kernel:
    mov ax, 0
    mov es, ax ; which segment to load
    mov ah, 2 ; function number
    mov al, 1 ; load one sector
    mov dx, 0 ; dl = 0 for floppy disk, dh = 0 for 0 head
    mov ch, 0 
    int 13H 
.jmp2kernel:
    jmp bx
    hlt

times 510-($-$$) db 0
dw 0xAA55
kernel_address equ 0xA100