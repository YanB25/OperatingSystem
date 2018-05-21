[BITS 16]
INITSEG equ 0x9000
SYSSEG equ 0x1000
SETUPSEG equ 0x9020
%macro DELAY 0
    dw 0x00eb 
    dw 0x00eb
%endmacro
start:
    mov ax, INITSEG
    mov ds, ax
    mov ah, 0x03
    xor bh, bh

    ;save the cursor
    int 0x10
    mov [0], dx

    ;
    mov ah, 0x88
    int 0x15
    mov [2], ax

    ; move to pm!!
    cli

    mov ax, 0x0000
    cld
do_move:
    mov es, ax
    add ax, 0x1000
    cmp ax, 0x9000
    jz end_move
    mov ds, ax
    xor di, di
    xor si, si
    mov cx, 0x8000
    rep movsw
    jmp do_move
end_move:
    mov ax, SETUPSEG
    mov ds, ax ;TODO: ??

    lidt [idt_48]
    lgdt [gdt_48]

    ;NOTICE: not origin implement
    in al, 92H
    or al, 00000010b
    out 92h, al

    ; 8259A program
    mov al, 0x11
    out 0x20, al
    DELAY
    out 0xA0, al
    DELAY
    mov al, 0x20
    out 0x21, al
    DELAY
    mov al, 0x28
    out 0xA1, al
    DELAY
    mov al, 0x04
    out 0x21, al
    DELAY
    mov al, 0x02
    out 0xA1, al
    DELAY
    mov al, 0x01
    out 0x21, al
    DELAY
    out 0xA1, al
    DELAY
    mov al, 0xFF
    out 0x21, al
    DELAY
    out 0xA1, al

    ; cr0 set pe
    mov ax, 0x0001
    lmsw ax
    jmp 8:0

GDT:
    dw 0, 0, 0, 0 ;dummy

    ; code descriptor
    dw 0x07FF ; limit
    dw 0x0000 ; base address = 0
    dw 0x9A00 ; code, read and exec
    dw 0x00C0 

    ; data descriptor
    dw 0x07FF 
    dw 0x0000 ; base address = 0
    dw 0x9200 ; data, read and write
    dw 0x00C0
idt_48:
    dw 0, 0, 0
gdt_48:
    dw 0x800
    dw 512+GDT, 0x9

    jmp $