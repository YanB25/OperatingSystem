#include <stdint.h>
#include "../include/linux/head.h"
#include "../include/asm/system.h"

void divide_error(void);
void debug(void);
void int3(void);
void bounds(void);
void double_fault(void);
void general_protection(void);
void invalid_TSS();
void segment_not_present();
void stack_segment();
int32_t printks(const char* msg);

static void die(char* str, int32_t esp_ptr, int32_t nr) {
    //TODO: not implement. do not have printk
    printks(str);
    //do_exit(11);
    while(1) {} //TODO: should call do_exit. but not implement
}
/**
 * NOTICE: int32_t esp is actually as pointer to esp.
 * but we still use type int32_t, according to how linux wrote.
 * its type will be cast when necessary
 */
void do_divide_error(int32_t esp, int32_t error_code) {
    int32_t magic = 0x77887788; //magic number to check whether jump is correct
    die("divide error", esp, error_code);
}
void do_int3(int32_t* esp, 
    int32_t error_code,
    int32_t fs,
    int32_t es,
    int32_t ds,
    int32_t ebp,
    int32_t esi,
    int32_t edi,
    int32_t edx,
    int32_t ecx,
    int32_t ebx,
    int32_t eax) {
        //TODO: empty so far.
}

void do_bounds(int32_t esp, int32_t error_code) {
    die("bounds", esp, error_code);
}
     
void do_general_protection(int32_t esp, int32_t error_code) {
    die("general protection", esp, error_code);
}
    
void do_double_fault(int32_t esp, int32_t error_code) {
    die("double fault", esp, error_code);
}
void do_invalid_TSS(int32_t esp, int32_t error_code) {
    die("invalid TSS", esp, error_code);
}
void do_stack_segment(int32_t esp, int32_t error_code) {
    die("stack segment", esp, error_code);
}
void do_segment_not_present(int32_t esp, int32_t error_code) {
    die("segment not present", esp, error_code);
}
void trap_init() {
    set_trap_gate(0, &divide_error);
    set_trap_gate(1, &debug);
    set_trap_gate(3, &int3);
    set_trap_gate(5, &bounds);
    set_trap_gate(8, &double_fault);
    set_trap_gate(10, &invalid_TSS);
    set_trap_gate(11, &segment_not_present);
    set_trap_gate(12, &stack_segment);
    set_trap_gate(13, &general_protection);
}