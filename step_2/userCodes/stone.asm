; stone.asm
; show a running 'A', 'B' and my name
%ifdef DEBUG
      delay equ 1000
%else
      delay equ 50000
%endif

%ifdef UL
     mycode equ 'q'
     DownSideBoundary equ 10
     UpSideBoundary equ -1 ; for some reason, minus one
     LeftSideBoundary equ 0
     RightSideBoundary equ 23
     _x equ 1
     _y equ 10
     org 0A300H
     DIRECTION equ Up_Lt
%elifdef UP
     mycode equ 'w'
     DownSideBoundary equ 10
     UpSideBoundary equ -1 ; for some reason, minus one
     LeftSideBoundary equ 29
     RightSideBoundary equ 50
     _x equ 4
     _y equ 40
     org 0A500H
     DIRECTION equ Up_Lt
%elifdef UR
     mycode equ 'e'
     DownSideBoundary equ 10
     UpSideBoundary equ -1 ; for some reason, minus one
     LeftSideBoundary equ 56
     RightSideBoundary equ 79
     _x equ 1
     _y equ 70
     org 0A700H
     DIRECTION equ Up_Rt
%elifdef DL
     mycode equ 'a'
     DownSideBoundary equ 25
     UpSideBoundary equ 14 ; for some reason, minus one
     LeftSideBoundary equ 0
     RightSideBoundary equ 23
     _x equ 23
     _y equ 10
     org 0A900H
     DIRECTION equ Dn_Lt
%elifdef DN
     mycode equ 's'
     DownSideBoundary equ 25
     UpSideBoundary equ 14 ; for some reason, minus one
     LeftSideBoundary equ 29
     RightSideBoundary equ 50
     _x equ 20
     _y equ 38
     org 0AB00H
      DIRECTION equ Dn_Rt
%elifdef DR
     mycode equ 'd'
     DownSideBoundary equ 25
     UpSideBoundary equ 14 ; for some reason, minus one
     LeftSideBoundary equ 56
     RightSideBoundary equ 79
     _x equ 20
     _y equ 70
     org 0AD00H
     DIRECTION equ Dn_Rt
%endif



     Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
     Up_Rt equ 2                  ;
     Up_Lt equ 3                  ;
     Dn_Lt equ 4                  ;
     ddelay equ 580					; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
 eBoundary equ 80
     ScreenLength equ 25 * 80 * 2
     sys_base equ 0A100H
[SECTION .text]
start:
      ;TODO:debug
      mov ax, datadef
      mov ax, 0
      ; mov ax,cs
      mov es,ax					; ES = 0
      mov ds,ax					; DS = CS
      mov es,ax					; ES = CS
      mov ax, stack + 2000H
      mov sp, ax
      mov dh, byte[style]

loop1:
    jmp test_key_press
.Loop:
    dec word[count]				; �ݼ���������
    jnz loop1.Loop					; >0����ת;
    mov word[count],delay
    dec word[dcount]				; �ݼ���������
    jnz loop1
    mov word[count],delay
    mov word[dcount],ddelay

; setTimeOut callback here
; main logic
      mov al,1
      cmp al,byte[rdul]
      jz  DnRt
      mov al,2
      cmp al,byte[rdul]
      jz  UpRt
      mov al,3
      cmp al,byte[rdul]
      jz  UpLt
      mov al,4
      cmp al,byte[rdul]
      jz  DnLt
      jmp $

DnRt:
      inc word[x]
      inc word[y]
      mov bx,word[x]
      cmp bx, DownSideBoundary
      jge  dr2ur
      mov bx,word[y]
      cmp bx, RightSideBoundary
      jge  dr2dl
      call show
      jmp loop1
dr2ur:
      mov word[x], DownSideBoundary - 1
      mov byte[rdul],Up_Rt
      call show
      jmp loop1
dr2dl:
      mov word[y], RightSideBoundary-1
      mov byte[rdul],Dn_Lt
      call show
      jmp loop1

UpRt:
      dec word[x]
      inc word[y]
      mov bx,word[y]
      cmp bx, RightSideBoundary
      jge  ur2ul
      mov bx,word[x]
      cmp bx, UpSideBoundary
      jz  ur2dr
      call show
      jmp loop1
ur2ul:
      mov word[y],RightSideBoundary-1
      mov byte[rdul],Up_Lt
      call show
      jmp loop1
ur2dr:
      mov word[x], UpSideBoundary+ 1
      mov byte[rdul],Dn_Rt
      call show
      jmp loop1



UpLt:
      dec word[x]
      dec word[y]
      mov bx,word[x]
      cmp bx, UpSideBoundary
      jle  ul2dl
      mov bx,word[y]
      cmp bx, LeftSideBoundary
      jl  ul2ur
      call show
      jmp loop1

ul2dl:
      mov word[x], UpSideBoundary+1
      mov byte[rdul],Dn_Lt
      call show
      jmp loop1
ul2ur:
      mov word[y], LeftSideBoundary+1
      mov byte[rdul],Up_Rt
      call show
      jmp loop1



DnLt:
      inc word[x]
      dec word[y]
      mov bx,word[y]
      cmp bx, LeftSideBoundary
      jl  dl2dr
      mov bx,word[x]
      cmp bx, DownSideBoundary
      jge  dl2ul
      call show
      jmp loop1

dl2dr:
      mov word[y],LeftSideBoundary+1
      mov byte[rdul],Dn_Rt
      call show
      jmp loop1

dl2ul:
      mov word[x], DownSideBoundary-1
      mov byte[rdul],Up_Lt
      call show
      jmp loop1


show:
    inc byte[style]
    and byte[style], 0FH
    push bx

    mov ax, word [x]
    push ax

    mov ax, word [y]
    push ax

     ; mov ah, 088H
    mov ah, byte[style]
    mov al, byte[char]
    push ax

    mov bp, sp
    mov bx, 0A100H

    call [bx + 6]

    times 3 pop bx
    pop bx

    ret

test_key_press:
    xor ax, ax
    mov ah, 1
    int 16H
    cmp ah, 1
    jz loop1.Loop

      xor ax, ax
      int 16H
      cmp al, mycode
      jz loop1.Loop
    ; key pressed

    ; catch key press
    ; TODO: maybe bug: this step would lose
    ; some registers' infomation.
     push cx
     mov cl, byte[style]
     inc cl
     mov byte[style], cl
     pop cx

    mov bx, sys_base
    jmp [bx + 0AH]


end:
    jmp $                   ; ֹͣ��������ѭ��

clearChar:
      mov dl, 'A'
      jmp show
datadef:
    count dw delay
    dcount dw ddelay
    rdul db DIRECTION         ; �������˶�
    char db 'A'
    style db 0Fh
    x dw _x
    y dw _y

; below for boot
    times 510-($-$$) db 0
stack: