#include <stdint.h>
#include "../include/linux/head.h"
#include "../include/asm/system.h"

void divide_error(void);
void debug(void);
void int3(void);
void bounds(void);

static void die(char* str, int32_t esp_ptr, int32_t nr) {
    //TODO: not implement. do not have printk
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
     
    
void trap_init() {
    set_trap_gate(0, &divide_error);
    set_trap_gate(1, &debug);
    set_trap_gate(3, &int3);
    set_trap_gate(5, &bounds);
}