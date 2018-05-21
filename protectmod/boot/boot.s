%include "../include/boot/pm.inc"
jmp 07C0H:begin

GDT:
NULL_GDT: Descriptor 0, 0, 0; null
CODE_32_GDT: Descriptor 0, CODE_32_LENGTH -1, DA_C + DA_32 
CODE_VIDEO_GDT: Descriptor 0B8000H, 0FFFFH, DA_DRW

GDT_LENGTH equ $-GDT
GDT_PTR dw GDT_LENGTH-1
    dd 0

SelectorCode32 equ CODE_32_GDT - GDT
SelectorVideo equ CODE_VIDEO_GDT - GDT

[BITS 16]
begin:
    mov ax, cs    
    mov es, ax
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov sp, 0FFH 

    xor eax, eax
    mov ax, cs
    shl eax, 4
    add eax, CODE_32
    mov word [CODE_32_GDT + 2], ax
    shr eax, 16
    mov byte [CODE_32_GDT + 4], al
    mov byte [CODE_32_GDT + 7], ah

    xor eax, eax
    mov ax, ds
    shl eax, 4
    add eax, GDT
    mov dword [GDT_PTR + 2], eax

    lgdt [GDT_PTR]

    cli

    in al, 92H
    or al, 00000010b
    out 92h, al

    mov eax, cr0
    or eax, 1
    mov cr0, eax
    
    jmp dword SelectorCode32:0

[BITS 32]
CODE_32:
    mov ax, SelectorVideo
    mov gs, ax

    mov edi, (80 * 11 + 79) * 2
    mov ah, 0CH
    mov al, 'P'
    mov [gs:edi], ax

    jmp $

CODE_32_LENGTH equ $ - CODE_32

times 510-($-$$) db 0
dw 0xaa55