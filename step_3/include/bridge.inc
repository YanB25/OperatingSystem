%macro pushl 1
    push word 0
    push word %1
%endmacro

%macro calll 1
    push cs
    call %1
%endmacro

%macro retl 0
    pop ecx
    jmp cx

%endmacro