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
    mov word [es: 22H], ax


    popa
    pop ds 
    pop es

    pop ecx
    jmp cx

timeOut:
    ;jmp saveRegisterImage

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

saveRegisterImage:
    ;ax
    ;cx
    ;dx
    ;bx
    ;old_ps
    ;bp
    ;si
    ;di
    pusha

    push ds
    push es
    push fs
    push gs
    push ss
    mov bx, sp ;TODO: maybe bug
    mov word [bx-2], sp

    calll get_current_PCB_address