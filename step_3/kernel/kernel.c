/**
 * @file
 * @brief KERNEL of the operating system
 * 
 * currently, it will clear screen, output some infomation,
 * than pass control to terminal. 
 * @see terminal.h
 */
#include "kernel.h"
#include "../include/utilities.h"
#include "../user/user.h"
#include "../user/terminal.h"
#include "../include/mystring.h"
#include "../filesystem/API/fsapi.h"
#define true 1
#define false 0
extern void clock_install_interupt(); ///< used to install clock 
extern void global_custom_int_install(); ///< used to install cumstom interupt
void init_testcase(); ///< TODO:delete me after debug finish
void init();
/// kernel entry
int main() {
    init_testcase();
    clock_install_interupt();
    init();
    // __screen_scroll(0, (20 << 8) + 20, 5, 0);
    // __asm__ volatile (
    //     "pushw %ax\n"
    //     "mov $0, %ax\n"
    //     "INT $0x2B\n"
    //     "popw %ax\n"
    // );
    // _draw_char('A', 0, DEFAULT_STYLE);
    // __asm__("int $0x8\n");
    // __load_program("stoneS");
    //draw_char_style('A', 0, 10, G_DEFAULT);
    // draw_char_style('A', 0, 11, G_DEFAULT_DARK);
    terminal();
    return 0;
}

void init() {
    global_custom_int_install();
    // clock_install_interupt();
    clear_screen();
    draw_str("enter help to get help", 1, 30);
    newline();
    set_cursor(2, 1);

}