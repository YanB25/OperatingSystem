; this file is the head of `system` so it is called head.s
; 0000:0000
[BITS 32]
%include "../include/boot/pm.inc"
extern main
extern INIT_STACK
; ld recognize startup_32 to be entry
global startup_32, gdt, idt, pg_dir
global tmp_STACK_end
pg_dir:
startup_32:
    mov eax, 0x10 ; descriptor! RPL = 0. the third item(data descriptor)
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
    ;lss esp, stack_start ;TODO: error! I still not have stack_start
    mov ss, ax
    mov esp, tmp_STACK_end ;TODO: maybe bugs. it seems to work pretty well =)
    call setup_idt
    call setup_gdt

    ; again
    mov eax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ;lss esp, stack_start ;TODO: same, see above
    mov ss, ax
    mov esp, tmp_STACK_end ;TODO: maybe bugs

   ; .temp used to test A20 really ok
.tmp:
   xor eax, eax 
   inc eax
   mov [0x000000], eax
   cmp [0x100000], eax
   je .tmp

after_page_table:
    push dword 0
    push dword 0
    push dword 0
    push dword L6
    push dword main
    ; jmp setup_page ;NOTICE: not set page.
    ret ;use this hack to jmp to main
L6:
    ; main never return. in case it returns, be into dead loop
    jmp $
setup_page:
    jmp $ ; not implemented

setup_gdt:
    lgdt [GDT_PTR]
    ret
setup_idt:
    lea edx, [ignore_int] ; TODO: why not mov edx, ignore_int?
    mov eax, 0x00080000
    mov ax, dx
    mov dx, 0x8E00
    lea edi, [idt]
    mov ecx, 256
rp_sidt:
    mov [edi], eax
    mov [edi + 4], edx
    add edi, 8
    dec ecx
    jne rp_sidt
    lidt [IDT_PTR]
    ret


IDT_PTR:
    dw 256*8-1
    dd idt

GDT_PTR:
    dw 256*8-1
    dd gdt

ignore_int:
    push eax
    push ecx
    push edx
    push ds
    push es
    push fs
    mov eax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    ; push int_msg
    ; call _printk ;TODO: here, workaround. find a way to print.
    pop fs
    pop es
    pop ds
    pop edx
    pop ecx
    pop eax
    iret

tmp_STACK: ;TODO: temporary stack. should be changed
    times 1024 db 0
tmp_STACK_end:

idt:
    times 256 * 8 db 0 ; 256 items, 8 bytes for each item. fill 0

gdt:
    dq 0; dummy
    dq 0x00C09A0000000FFF ; code
    dq 0x00C0920000000FFF ; data
    dq 0; don't use.
    Descriptor 0B8000H, 0FFFFH, DA_DRW
    Descriptor 090000H, 000FFH, DA_DRW
    times 254 * 8 db 0 ; 256 items, 8 bytes for each item. fill 0
    ;TODO: I change here from 256 to 254, because I add video descriptor
    ; and a global config data descriptor
