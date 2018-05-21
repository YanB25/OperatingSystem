; this file is used to load the whole system into memory.
BITS 16
SYSSIZE equ 0x3000
SETUPLEN equ 4
BOOTSEG equ 0x07c0
INITSEG equ 0x9000
SETUPSEG equ 0x9020
SYSSEG equ 0x1000
ENDSEG equ SYSSEG + SYSSIZE

global _start

jmp BOOTSEG: _start
_start:
    mov ax, BOOTSEG
    mov ds, ax
    mov ax, INITSEG
    mov es, ax
    mov cx, 256
    xor si, si
    xor di, di
    rep movsw
    jmp INITSEG: go
go:
    ;now in 0x9000:xxxx
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0xFF00
load_setup: 
    mov dx, 0x0000
    mov cx, 0x0002
    mov bx, 0x0200
    mov ax, 0x0200 + SETUPLEN
    int 0x13

ok_load_setup: ; no error handler.

    ;print some msg
    mov ah, 0x03
    xor bh, bh
    int 0x10
    mov cx, 24
    mov bx, 0x0007
    mov bp, msg1
    mov ax, 0x1301
    int 0x10

    ; load system at 0x10000
    mov ax, SYSSEG  
    mov es, ax ; segment of 0x010000
    call read_it ; an extremely complex function that handle everything

    jmp SETUPSEG: 0

data:
sread dw 1+SETUPLEN
head dw 0
track dw 0

read_it: ; never try to understand these codes. really HOPE they work well =)
    mov ax, es
;     test ax, 0x0fff
; die:
;     jne die
    xor bx, bx
rp_read:
    mov ax, es
    cmp ax, ENDSEG
    jb ok1_read
    ret

ok1_read:
    mov ax, SECTORS
    sub ax, [sread]
    mov cx, ax
    shl cx, 9
    add cx, bx
    jnc ok2_read
    je ok2_read
    xor ax, ax
    sub ax, bx
    shr ax, 9
ok2_read:
    call read_track
    mov cx, ax
    add ax, [sread]
    cmp ax, SECTORS
    jne ok3_read
    mov ax, 1
    sub ax, [head]
    jne ok4_read

    inc word [track]
ok4_read:
    mov [head] ,ax
    xor ax,ax
ok3_read:
    mov [sread], ax
    shl cx, 9
    add bx, cx
    jnc rp_read
    mov ax, es
    add ax, 0x1000
    mov es, ax
    xor bx, bx
    jmp rp_read
read_track:
    push ax
    push bx
    push cx
    push dx
    mov dx, [track]
    mov cx, [sread]
    inc cx
    mov ch, dl
    mov dx, [head]
    mov dh, dl
    mov dl, 0
    and dx, 0x0100
    mov ah, 2
    int 0x13
    jc bad_rt
    pop dx
    pop cx
    pop bx
    pop ax
    ret
bad_rt:
    jmp $
SECTORS equ 18

msg1 db "loading system", 0

times 510 - ($-$$) db 0
dw 0xAA55