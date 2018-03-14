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

    mov cl, 2 ; initial to 2(th) sector

    cmp al, 'q'
    je .UL
    cmp al, 'w'
    je .UP
    cmp al, 'e'
    je .UR
    cmp al, 'a'
    je .DL
    cmp al, 's'
    je .DN
    cmp al, 'd'
    je .DR

    jmp wait_key

.load:

    mov bx, phy_base
    mov ax, 0
    mov es, ax ; which segment to load
    mov ah, 2 ; function number
    mov al, 1 ; load one sector
    mov dx, 0 ; dl = 0 for floppy disk, dh = 0 for 0 head
    mov ch, 0 
    ;mov cl, 2 ; from 2 (th) sector
    int 13H

    mov bx, phy_base
    jmp phy_base ; FIXME: ERROR in segments
    

.DR:
    inc cl
.DN:
    inc cl
.DL:
    inc cl
.UR:
    inc cl
.UP:
    inc cl
.UL:
    jmp .load


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
phy_base equ 0A100H ; where to load
promt db "press Q, E, R, A, S, D to load a program"
length equ $ - promt
newline db `\n\r`
nl_length equ $ - newline
ScreenLength equ 25 * 80 * 2

; for boot
times 510-($-$$) db 0
    dw 0xAA55
