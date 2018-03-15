org 0A100H
show_address dw 0xF0F0 ; 0xA100H +0
loader_back_address dw 0xF0F0 ; 0xA102H +2
_show_at_call dw show_at_call ; 0xA104H +4
_show_call dw show_call ; 0xA106H +6
_clear_screen dw clear_screen ; 0xA108H +8
_key_press_callback dw key_press_callback ; 0xA10AH + 0AH
show_at_call:
    ; bp point to str address
    ; cx contents the length
    mov ah, 0EH
    push bx
    mov bl, 0
    mov al, '@'
    int 10H
    pop bx
    jmp [loader_back_address]

show_call:
    push gs
    push dx

    mov ax, 0B800H
    mov gs, ax
    xor ax,ax               

    ; inc byte [bp]
    mov ax,word[bp + 4]
    mov bx,80
    mul bx
    add ax,word[bp + 2] ; ax = 80 * x + y
    mov bx,2
    mul bx
    mov bx,ax ; bx = 2(80 * x + y)
    mov ax, word[bp]
    mov [gs:bx],ax  

    pop dx
    pop gs
    ret

clear_screen:
    push si
    push es

    mov cx, ScreenLength ;TODO: can i change cx?
    mov si, 0
    mov ax, 0B800H
    mov es, ax
.Loop:
    mov byte[es:si], 0
    inc si
    loop .Loop
.RET:
    pop es
    pop si
    ret

key_press_callback:
    jmp [loader_back_address] ;TODO: change here!

ScreenLength equ 25 * 80 * 2