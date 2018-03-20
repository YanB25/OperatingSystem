[BITS 16]
global clear_screen
global hello_hybrid_programming

clear_screen:
    mov ax, 03h
    int 10h
    pop ecx
    jmp cx

hello_hybrid_programming:
