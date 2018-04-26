;TODO: in this file ,cs must be 0.
[BITS 16]
global clock_install_interupt
global restoreProcess
extern timeout
extern kb_custom_interupt

extern get_current_PCB_address
extern get_next_PCB_address
%include "../include/bridge.inc"
clock_install_interupt:
    push es
    push ds
    pusha

    mov ax, cs
    mov ds, ax
    xor ax, ax 
    mov es, ax 

    ; install int 08: clock interupt
    mov word [es: 20H], timeOut
    ;mov word [es: 22H], ax
    mov word[es: 22H], 0 ; notice, here must be ZERO
    ; I changed the code above, to ensure that when comes into interupt
    ; the segment is always 0


    popa
    pop ds 
    pop es

    pop ecx
    jmp cx

timeOut:
    jmp saveRegisterImage
.back_1:

    pusha
    push gs
    push ds
    push es

    mov ax, 0 
    mov ds, ax 
    mov es, ax 

    calll timeout

    pop es
    pop ds
    pop gs
    popa


    jmp restoreProcess
.back_2:

    push ax 
    ; hardware port to enable next int
    mov al, 20H
    out 20H, al
    out 0A0H, al 
    pop ax


    iret
    ; WARNING: will no jmp to origin clock interupt anymore

data:
    char db 'A'

;there is a critical important hack in the function
;We need to call get_current_PBC_address, so push word 0 to fit 32-bits calling rule
;but it ruin the value `sp` that is "mov" into the stack
;so, in the function
;call `get_current_PBC_address` first
;and mov sp into stack until the last second.
;
;notice, push sp is undefined
;we have to "move" sp into stack, instead of "push"
saveRegisterImage:
    ; 高地址
    ;ax
    ;cx
    ;dx
    ;bx
    ;old_ps
    ;bp
    ;si
    ;di
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

    jmp timeOut.back_1

restoreProcess:
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

    ;    push ax 
    ;    ; hardware port to enable next int
    ;    mov al, 20H
    ;    out 20H, al
    ;    out 0A0H, al 
    ;    pop ax

    ;    iret
    jmp timeOut.back_2

temp_ss dw 0
temp_sp dw 0