;TODO: in this file ,cs must be 0.
[BITS 16]
global clock_install_interupt
extern timeout
extern kb_custom_interupt

extern get_current_PCB_address
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
    mov ax, cs
    ;mov word [es: 22H], ax
    mov word[es: 22H], 0 ;TODO: maybe bug.
    ; I changed the code above, to ensure that when comes into interupt
    ; the segment is always 0


    popa
    pop ds 
    pop es

    pop ecx
    jmp cx

timeOut:
    jmp saveRegisterImage

    pusha
    push gs
    push ds
    push es

    mov ax, cs 
    mov ds, ax 
    mov es, ax 

    push cs 
    call timeout

    pop es
    pop ds
    pop gs
    popa

    jmp 0F000H:0fea5H ;TODO: should not hard code

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

    ; set ds and es to 0
    ; which is the segment for kernel
    mov ax, 0
    mov ds, ax
    mov es, ax

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