extern get_current_PCB_address
extern get_next_PCB_address
%macro context_switch_save 0
    pusha

    push ds ; sp + 8
    push es ; sp + 6
    push fs ; sp +4
    push gs ; sp + 2
    push ss ; sp 
    ; 低地址
    
    mov ax, 0 ; cs is 0
    mov es, ax
    mov ds, ax

    calll get_current_PCB_address

    mov bx, sp ;TODO: maybe bug 
    mov word [ss:bx-2], sp ; sp - 2 ;TODO: important, use ss to get position!

    mov di, ax
    mov ax, sp
    sub ax, 2
    mov si, ax

    mov cx, 17 * 2
    cld
    rep movsb
%endmacro

%macro context_switch_restore 0
    mov ax, 0 ; cs is 0
    mov es, ax
    mov ds, ax

    calll get_next_PCB_address
    ; si and di
    ; move the register image into stack
    mov si, ax
    mov bx, ax
    mov cx, [bx]
    mov di, cx ; sp
    sub di, 2; important, bug?
    add bx, 2
    mov cx, [bx]
    mov ds, cx ; ss
    mov cx, 17 * 2
    cld
    rep movsb

    mov bx, ax
    mov cx, [bx] ;sp
    mov sp, cx

    add bx, 2
    mov cx, [bx] ;ss
    mov ss, cx

    pop ax; pop ignore ss

    pop gs
    pop fs 
    pop es 
    pop ds

    popa

%endmacro