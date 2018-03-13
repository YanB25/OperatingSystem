; stone.asm
; show a running 'A', 'B' and my name
%ifdef DEBUG
      delay equ 1000
%else 
      delay equ 50000
%endif

%ifdef UL 
     DownSideBoundary equ 12
     UpSideBoundary equ -1 ; for some reason, minus one
     LeftSideBoundary equ 0
     RightSideBoundary equ 30
     _x equ 6
     _y equ 13
%elifdef UP 
     DownSideBoundary equ 12
     UpSideBoundary equ -1 ; for some reason, minus one
     LeftSideBoundary equ 30
     RightSideBoundary equ 60
     _x equ 6
     _y equ 40

%elifdef UR 
     DownSideBoundary equ 12
     UpSideBoundary equ -1 ; for some reason, minus one
     LeftSideBoundary equ 60
     RightSideBoundary equ 79
     _x equ 1
     _y equ 70

%elifdef DL 
     DownSideBoundary equ 25
     UpSideBoundary equ 12 ; for some reason, minus one
     LeftSideBoundary equ 0
     RightSideBoundary equ 30
     _x equ 20
     _y equ 13
%elifdef DN 
     DownSideBoundary equ 25
     UpSideBoundary equ 12 ; for some reason, minus one
     LeftSideBoundary equ 30
     RightSideBoundary equ 60
     _x equ 20
     _y equ 40

%elifdef DR 
     DownSideBoundary equ 25
     UpSideBoundary equ 12 ; for some reason, minus one
     LeftSideBoundary equ 60
     RightSideBoundary equ 79
     _x equ 20
     _y equ 70

%endif
     Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
     Up_Rt equ 2                  ;
     Up_Lt equ 3                  ;
     Dn_Lt equ 4                  ;
     ddelay equ 580					; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
 eBoundary equ 80
     ScreenLength equ 25 * 80 * 2
     org 07c00h					; ������ص�100h������������COM
[SECTION .text]
start:
      mov ax,cs
      mov es,ax					; ES = 0
      mov ds,ax					; DS = CS
      mov es,ax					; ES = CS
      mov ax,0B800h				; �ı������Դ���ʼ��ַ
      mov gs,ax					; GS = B800h
      mov dh, byte[style]

loop1:
      dec word[count]				; �ݼ���������
      jnz loop1					; >0����ת;
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
      xor ax,ax                 ; �����Դ��ַ
      inc byte [style]
      mov ax,word[x]
      mov bx,80
      mul bx
      add ax,word[y] ; ax = 80 * x + y
      mov bx,2
      mul bx
      mov bx,ax ; bx = 2(80 * x + y)
      mov al,byte[char]			;  AL = ��ʾ�ַ�ֵ��Ĭ��ֵΪ20h=�ո���� 
      mov ah, [style]
      mov [gs:bx],ax  		;  ��ʾ�ַ���ASCII��ֵ
      ret
end:
    jmp $                   ; ֹͣ��������ѭ��

clearChar:
      mov dl, 'A'
      jmp show
datadef:
    count dw delay
    dcount dw ddelay
    rdul db Dn_Rt         ; �������˶�
    char db 'A'
    style db 8Fh
    x dw _x
    y db _y

; below for boot
    times 510-($-$$) db 0
stack: