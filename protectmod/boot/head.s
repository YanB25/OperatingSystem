%include "../include/boot/pm.inc"

jmp begin

GDT:
NULL_GDT: Descriptor 0, 0, 0; null
CODE_32_GDT: Descriptor 0, CODE_32_LENGTH -1, DA_C + DA_32 ; main code
CODE_VIDEO_GDT: Descriptor 0B8000H, 0FFFFH, DA_DRW ; for video
LABEL_DESC_TEST: Descriptor 0500000H, 0FFFFH, DA_DRW ; a very far address for testing
LABEL_DESC_STACK: Descriptor 0, STACK_LENGTH, DA_DRW + DA_32 ; for stack

GDT_LENGTH equ $-GDT
GDT_PTR dw GDT_LENGTH-1
    dd 0

SelectorCode32 equ CODE_32_GDT - GDT
SelectorVideo equ CODE_VIDEO_GDT - GDT
SelectorTest equ LABEL_DESC_TEST - GDT
SelectorStack equ LABEL_DESC_STACK - GDT

[BITS 16]
begin:
    ; ax should be 0
    mov ax, cs    
    mov es, ax
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov sp, 0FFH 

    ; init base address in descriptor
    DescriptorBaseInitor STACK, LABEL_DESC_STACK
    DescriptorBaseInitor CODE_32, CODE_32_GDT

    ;set base address for gdt_ptr
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
    mov ax, SelectorTest
    mov es, ax
    mov ax, SelectorVideo
    mov gs, ax

    mov ax, SelectorStack
    mov ss, ax

    mov esp, 0FFF0H 

    mov ah, 0Ch
    mov edi, (80 * 10 + 0 ) * 2
    cld

    mov byte [es:0], 'Y'
    mov byte [es:1], 'B'

    mov byte al, [es:0]
    mov ah, 0Ch
    mov word [gs:edi], ax

    add edi, 2
    mov byte al, [es:1]
    mov ah, 0CH
    mov word [gs:edi], ax

    jmp $

CODE_32_LENGTH equ $ - CODE_32

STACK:
    times 100 db 0
STACK_END:
STACK_LENGTH equ STACK_END - STACK