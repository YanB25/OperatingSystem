[BITS 32] ;TODO: really?
global divide_error 
global debug 
global int3 
global bounds
global double_fault 
global general_protection
global invalid_TSS
global segment_not_present
global stack_segment

extern do_divide_error 
extern do_int3 
extern do_bounds
extern do_general_protection
extern do_double_fault
extern do_invalid_TSS
extern do_segment_not_present
extern do_stack_segment

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


; below int has error code
double_fault:
    push dword do_double_fault
error_code:
    xchg [esp + 4], eax
    xchg [esp], ebx
    push ecx
    push edx
    push edi
    push esi
    push ebp
    push ds
    push es
    push fs
    push eax
    lea eax, [esp + 44]
    push eax
    mov eax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    call ebx
    add esp, 8
    pop fs
    pop es
    pop ds
    pop ebp
    pop esi
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax
    iret

general_protection:
    push dword do_general_protection
    jmp error_code

invalid_TSS:
    push dword do_invalid_TSS
    jmp error_code
segment_not_present:
    push dword do_segment_not_present
    jmp error_code
stack_segment:
    push dword do_stack_segment
    jmp error_code
