[BITS 32]
global test_write
test_write:
    push ds

    mov eax, 0x20
    mov ds, eax
    mov byte [0], 'Y'
    mov byte [1], 0x0C

    pop ds
    ret