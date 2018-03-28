[BITS 16]
global loadSector
%include "../include/bridge.inc"
loadSector:
    ; track bp + 6
    ; head bp + 10
    ; sector bp + 14
    ; addr bp + 18
    ; num bp + 22
    enter 0, 0
    push bx

    ; sector number in low 6 bits in CL
    mov ax, [bp + 14]
    and ax, 03FH ; 0011_1111
    mov bx, [bp + 6]
    and bx, 0C0H;1100_0000
    add ax, bx
    mov cl, al

    ; low 8 bits of cyl in CH
    mov ch, [bp + 6]

    ; head in DH
    mov dh, [bp + 10] 
    
    mov dl, 0 ; 0 for fd


    xor ax, ax 
    mov es, ax

    mov bx, [bp + 18]
    ; number of sectors to load
    mov al, [bp + 22]

    mov ah, 02H
    int 13H

    xor ah, ah 
    and al, 0FH ; 00001111

    pop bx
    leave

    retl