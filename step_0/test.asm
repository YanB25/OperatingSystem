mov ax,0xB800
mov es,ax
mov byte [es:00],’@’
mov byte [es:01],0f0h
jmp $