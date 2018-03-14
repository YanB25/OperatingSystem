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
     ScreenLength equ 25 * 80 * 2
     ;org 07c00h					; ������ص�100h������������COM
[SECTION .text]
start:
      mov ax,cs
      mov es,ax					; ES = 0
      mov ds,ax					; DS = CS
      mov es,ax					; ES = CS
      mov ax,0B800h				; �ı������Դ���ʼ��ַ
      mov gs,ax					; GS = B800h
      mov dh, byte[style]
      call clearTheScreen
      call sn

      mov dl, byte[char] ; init char to what I want
      mov word[y], 39
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
      call show
      jmp loop1
dr2ur:
      mov word[x],23
      mov byte[rdul],Up_Rt
      call show
      jmp loop1
dr2dl:
      mov word[y],78
      mov byte[rdul],Dn_Lt
      call show
      jmp loop1

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
      call show
      jmp loop1
ur2ul:
      mov word[y],78
      mov byte[rdul],Up_Lt
      call show
      jmp loop1
ur2dr:
      mov word[x],1
      mov byte[rdul],Dn_Rt
      call show
      jmp loop1



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
      call show
      jmp loop1

ul2dl:
      mov word[x],1
      mov byte[rdul],Dn_Lt
      call show
      jmp loop1
ul2ur:
      mov word[y],1
      mov byte[rdul],Up_Rt
      call show
      jmp loop1



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
      call show
      jmp loop1

dl2dr:
      mov word[y],1
      mov byte[rdul],Dn_Rt
      call show
      jmp loop1

dl2ul:
      mov word[x],23
      mov byte[rdul],Up_Lt
      call show
      jmp loop1

show:
;input
; x, y for cordination
; char for the character
      cmp dl, 'Z' + 1
      jz clearChar
      inc dl
      inc dh
      and dh, 0x7F
show_kernel:
      push dx
      xor ax,ax                 ; �����Դ��ַ
      mov ax,word[x]
      mov bx,80
      mul bx
      add ax,word[y] ; ax = 80 * x + y
      mov bx,2
      mul bx
      mov bx,ax ; bx = 2(80 * x + y)
      ;mov al,byte[char]			;  AL = ��ʾ�ַ�ֵ��Ĭ��ֵΪ20h=�ո���� 
      pop dx
      mov ax, dx ;get ax to the char
      ;mov ah, byte[style]				;  0000���ڵס�1111�������֣�Ĭ��ֵΪ07h��
      mov [gs:bx],ax  		;  ��ʾ�ַ���ASCII��ֵ
      ret
; showMyNameAndId:
;       push dx ;save from the shooting format
;       mov dh, byte[style]
;       mov bx, 0 ; index
;       mov cx, myNameAndIdLength
; showNameLoop:
;       loop showNameIdSetting
;       pop dx
;       ret
; showNameIdSetting:
;       mov dl, byte[myNameAndId+bx]
;       inc bx
;       push bx
;       push cx
;       call show_kernel
;       pop cx
;       pop bx
;       mov al, byte[y]
;       inc ax
;       mov byte[y], al
;       jmp showNameLoop
sn:
      push dx
      mov ax, 0B800h
      mov es, ax ; es = 0B800H
      mov ax, 0
      mov si, myNameAndId
      mov di, ax
      mov cx, myNameAndIdLength
      rep movsb
      pop dx
      ret

end:
    jmp $                   ; ֹͣ��������ѭ��

clearChar:
      mov dl, 'A'
      jmp show

clearTheScreen:
      mov cx, ScreenLength
      mov bx, 0
clearScreenLoop:
      loop clearWorker
      ret
clearWorker:
      mov word[gs:bx], 0
      inc bx
      jmp clearScreenLoop
datadef:
    count dw delay
    dcount dw ddelay
    rdul db Dn_Rt         ; �������˶�
    x    dw 12
    y    dw 32
    char db 'A'
    myNameAndId db `16337269 yanbin\0`
    myNameAndIdLength equ $-myNameAndId
    style db 8Fh

; below for boot
    times 510-($-$$) db 0
stack:
      dw 0xaa55