#include "kernel.h"
#include "../include/utilities.h"
#include "../user/user.h"
#include "../user/terminal.h"
#include "../include/mystring.h"
#include "../filesystem/API/fsapi.h"
#define true 1
#define false 0
extern void clock_install_interupt();
extern void global_custom_int_install();
int main() {
    global_custom_int_install();
    // __asm__ volatile (
    //     "pushw %ax\n"
    //     "mov $0, %ax\n"
    //     "INT $0x2B\n"
    //     "popw %ax\n"
    // );
    clock_install_interupt();
    _draw_char('A', 0, DEFAULT_STYLE);
    // __asm__("int $0x8\n");
    // __load_program("stoneS");
    clear_screen();
    draw_str("enter help to get help", 0, 30);
    //draw_char_style('A', 0, 10, G_DEFAULT);
    // draw_char_style('A', 0, 11, G_DEFAULT_DARK);
    newline();
    terminal();
    return 0;
}