org 07c00H
start:
    mov ax, cs
    mov es, ax
    mov ds, ax
    mov bp, promt
    mov cx, length
    call printStr

wait_key:
    mov ah, 0
    int 16H
    cmp al, 0
    jz wait_key ; no key pressed

    cmp al, 'e'
    jnz wait_key ; key not 'e'

    ;key is e
    mov cx, nl_length
    mov bp, newline
    call printStr

    mov bx, phy_base 
    mov ax, 0
    mov es, ax ; which segment to load
    mov ah, 2 ; function number
    mov al, 1 ; load one sector
    mov dx, 0 ; dl = 0 for floppy disk, dh = 0 for 0 head
    mov ch, 0 
    mov cl, 2 ; from 2 (th) sector
    int 13H
    
    jmp phy_base


printStr:
    ; bp point to str address
    ; cx contents the length
    mov ah, 0EH
    mov si, 0
    push bx
    mov bl, 0
.Loop:
    mov al, [bp + si]
    int 10H
    inc si
    loop .Loop
    pop bx
    ret
    
clearScreen:
    mov cx, ScreenLength
    mov si, 0
    mov ax, 0B800H
    mov es, ax
.Loop:
    mov byte[es:si], 0
    inc si
    loop .Loop
    ret
data:
phy_base dw 08000H ; where to load
promt db "press E to load a program"
length equ $ - promt
newline db `\n\r`
nl_length equ $ - newline
ScreenLength equ 25 * 80 * 2

; for boot
times 510-($-$$) db 0
    dw 0xAA55
