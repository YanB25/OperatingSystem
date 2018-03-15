org 07c00H
start:
    mov ax, 0
    mov es, ax
    mov ds, ax

init_utility:
.load_utility:
    mov cl, 2
    mov bx, phy_base
    call load
.realocate_utility:
    mov bx, 0A100H
    mov ax, 07c00H
    mov [bx], ax ; 07c00H to show address
    mov ax, wait_key.test_key ; 07c00H + test_key 
    mov [bx + 2], ax

init_screen:
.clean_up_screen:
    mov bx, phy_base
    call [bx + 8] ; call clear screen
.print_promt:
    call printStr

wait_key:
    ; init
    mov ax, 0
    mov es, ax
    mov ds, ax

    xor al, al
    mov ah, 1
    int 16H
    cmp ah, 1
    jz wait_key ; no key pressed

    ; fetch the key
    xor ax, ax
    int 16H
    ; now key in `al`


.test_key:
    mov cl, 2 ; initial to 2(th) sector
    mov bx, phy_base ; initial to base

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

    mov si, 4 * 80 * 2
    mov bx, phy_base
    call [bx+8]

    pop bx
    jmp wait_key


load:
    ; cl the nth sector to load
    ; bx the base address to put the code
.body:
    mov ax, 0
    mov es, ax ; which segment to load
    mov ah, 2 ; function number
    mov al, 1 ; load one sector
    mov dx, 0 ; dl = 0 for floppy disk, dh = 0 for 0 head
    mov ch, 0 
    int 13H ; TODO: unkown bugs
    ret    

.Ret:
    pop bx
    ret


printStr:
    ; bp point to str address
    ; cx contents the length

    push bx
    push bp
    push cx

    mov cx, length
    mov bp, promt
    mov ah, 13H
    mov al, 1
    mov bl, 0FH
    mov bh, 0
    mov dh, 0
    mov dl, 8
    int 10H

    pop cx
    pop bp
    pop bx
    ret


clearScreen:
    mov cx, ScreenLength
    mov ax, 0B800H
    mov es, ax
.Loop:
    mov byte[es:si], 0
    inc si
    loop .Loop

    ret
data:
hasLoaded db 0 ; x x b s a e w q
phy_base equ 0A100H ; where to load
promt db `press Q, E, R, A, S, D to load a program\n\r        press L to clear the screen.`
db `\n\r\n\r        made by yanbin, 16337269`
length equ $ - promt
newline db `\n\r`
nl_length equ $ - newline
ScreenLength equ 25 * 80 * 2

; for boot
times 510-($-$$) db 0
    dw 0xAA55
