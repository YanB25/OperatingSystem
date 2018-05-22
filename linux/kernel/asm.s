[BITS 32] ;TODO: really?
global divide_error 
global debug 
global int3 
global bounds
extern do_divide_error 
extern do_int3 
extern do_bounds

divide_error:
    push dword do_divide_error
no_error_code:
    xchg dword [esp], eax
    push dword ebx
    push dword ecx
    push dword edx
    push dword edi
    push dword esi
    push dword ebp
    push ds
    push es
    push fs
    push dword 0 ; push error code
    lea edx, [44 + esp]
    push dword edx
    mov edx, 0x10
    mov ds, dx
    mov es, dx
    mov fs, dx
    call eax ; TODO: is it correct ? can it work?
    add esp, 0x8
    pop fs
    pop es
    pop ds
    pop dword ebp
    pop dword esi
    pop dword edi
    pop dword edx
    pop dword ecx
    pop dword ebx
    pop dword eax
    iret

debug:
    push dword do_int3
    jmp no_error_code

int3:
    push dword do_int3
    jmp no_error_code
bounds:
    push dword do_bounds
    jmp no_error_code