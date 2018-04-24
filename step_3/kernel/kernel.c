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
void init_INIT_process();
void restoreProcess();
/// kernel entry
int main() {
    __load_program("stoneQ", 0x4200);
    // __load_program("stoneW", 0x4A00);
    init_INIT_process();
    clock_install_interupt();
    // __asm__ volatile(
    //     ".intel_syntax noprefix\n"
    //     "int 0x08\n"
    //     ".att_syntax\n"
    // );
    init();
    restoreProcess();
    // void (*p)() = (void (*)()) (0x4200);
    // p();
    //terminal();
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