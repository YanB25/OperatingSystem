#include <stdint.h>
#include "../include/linux/head.h"
#include "../include/asm/system.h"
void divide_error(void);
static void die(char* str, int32_t esp_ptr, int32_t nr) {
    //TODO: not implement. do not have printk
}
void do_divide_error(int32_t esp, int32_t error_code) {
    int32_t magic = 0x77887788; //magic number to check whether jump is correct
    die("divide error", esp, error_code);
}
void trap_init() {
    set_trap_gate(0, &divide_error);
}