; stone.asm
; show a running 'A', 'B' and my name
     Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
     Up_Rt equ 2                  ;
     Up_Lt equ 3                  ;
     Dn_Lt equ 4                  ;
     delay equ 50000					; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
     ddelay equ 580					; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
     DownSideBoundary equ 25
     UpSideBoundary equ 0
     LeftSideBoundary equ 0
     RightSideBoundary equ 80
     org 07c00h					; ������ص�100h������������COM
[SECTION .text]
start:
      mov ax,cs
      mov es,ax					; ES = 0
      mov ds,ax					; DS = CS
      mov es,ax					; ES = CS
      mov ax,0B800h				; �ı������Դ���ʼ��ַ
      mov gs,ax					; GS = B800h
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
      mov ax, DownSideBoundary
      sub ax,bx
      jz  dr2ur
      mov bx,word[y]
      mov ax,80
      sub ax,bx
      jz  dr2dl
      jmp show
dr2ur:
      mov word[x],23
      mov byte[rdul],Up_Rt
      jmp show
dr2dl:
      mov word[y],78
      mov byte[rdul],Dn_Lt
      jmp show

UpRt:
      dec word[x]
      inc word[y]
      mov bx,word[y]
      mov ax,80
      sub ax,bx
      jz  ur2ul
      mov bx,word[x]
      mov ax,-1
      sub ax,bx
      jz  ur2dr
      jmp show
ur2ul:
      mov word[y],78
      mov byte[rdul],Up_Lt
      jmp show
ur2dr:
      mov word[x],1
      mov byte[rdul],Dn_Rt
      jmp show



UpLt:
      dec word[x]
      dec word[y]
      mov bx,word[x]
      mov ax,-1
      sub ax,bx
      jz  ul2dl
      mov bx,word[y]
      mov ax,-1
      sub ax,bx
      jz  ul2ur
      jmp show

ul2dl:
      mov word[x],1
      mov byte[rdul],Dn_Lt
      jmp show
ul2ur:
      mov word[y],1
      mov byte[rdul],Up_Rt
      jmp show



DnLt:
      inc word[x]
      dec word[y]
      mov bx,word[y]
      mov ax,-1
      sub ax,bx
      jz  dl2dr
      mov bx,word[x]
      mov ax,25
      sub ax,bx
      jz  dl2ul
      jmp show

dl2dr:
      mov word[y],1
      mov byte[rdul],Dn_Rt
      jmp show

dl2ul:
      mov word[x],23
      mov byte[rdul],Up_Lt
      jmp show

show:
;input
; x, y for cordination
; char for the character
      xor ax,ax                 ; �����Դ��ַ
      mov ax,word[x]
      mov bx,80
      mul bx
      add ax,word[y] ; ax = 80 * x + y
      mov bx,2
      mul bx
      mov bx,ax ; bx = 2(80 * x + y)
      mov ah,0Fh				;  0000���ڵס�1111�������֣�Ĭ��ֵΪ07h��
      mov al,byte[char]			;  AL = ��ʾ�ַ�ֵ��Ĭ��ֵΪ20h=�ո����
      mov [gs:bx],ax  		;  ��ʾ�ַ���ASCII��ֵ
      jmp loop1

end:
    jmp $                   ; ֹͣ��������ѭ��

datadef:
    count dw delay
    dcount dw ddelay
    rdul db Dn_Rt         ; �������˶�
    x    dw 7
    y    dw 0
    char db 'A'

; below for boot
    times 510-($-$$) db 0
stack:
      dw 0xaa55