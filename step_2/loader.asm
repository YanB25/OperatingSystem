org 07c00H
start:
    mov ax, cs
    mov es, ax
    mov ds, ax
    mov bp, promt
    mov cx, length
    call printStr

init_utility:
.load_utility:
    mov cl, 2
    mov bx, phy_base
    call load
.realocate_utility:
    mov bx, 0A100H
    mov ax, 07c00H
    mov [bx], ax ; 07c00H to show address
    mov ax, wait_key ; 07c00H + test_key 
    mov [bx + 2], ax


wait_key:
    xor al, al
    mov ah, 1
    int 16H
    cmp ah, 1
    jz wait_key ; no key pressed

    ; fetch the key
    xor ax, ax
    int 16H
    ; now key in `al`

    mov cl, 2 ; initial to 2(th) sector
    mov bx, phy_base ; initial to base

.test_key:
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
    cmp al, 'l'
    je .clear_screen

    jmp wait_key


.DR:
    inc cl
    add bx, 200H
.DN:
    inc cl
    add bx, 200H
.DL:
    inc cl
    add bx, 200H
.UR:
    inc cl
    add bx, 200H
.UP:
    inc cl
    add bx, 200H
.UL:
    inc cl
    add bx, 200H

    call load
    jmp bx

.clear_screen:
    push bx

    mov bx, phy_base
    call [bx+8]

    pop bx
    jmp wait_key


load:
    ; cl the nth sector to load
    ; bx the base address to put the code
    mov ax, 0
    mov es, ax ; which segment to load
    mov ah, 2 ; function number
    mov al, 1 ; load one sector
    mov dx, 0 ; dl = 0 for floppy disk, dh = 0 for 0 head
    mov ch, 0 
    int 13H
    ret    

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
promt db `press Q, E, R, A, S, D to load a program\n\rpress L to clear the screen.`
length equ $ - promt
newline db `\n\r`
nl_length equ $ - newline
ScreenLength equ 25 * 80 * 2

; for boot
times 510-($-$$) db 0
    dw 0xAA55
