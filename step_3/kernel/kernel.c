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
#include "../include/mystring.h"
#include "../filesystem/API/fsapi.h"
#define true 1
#define false 0
extern void clock_install_interupt(); ///< used to install clock 
extern void global_custom_int_install(); ///< used to install cumstom interupt
void init();
void init_INIT_process();
void restoreProcess();
void timeout_init();
/// kernel entry
void init_terminal_process();
void add_new_process(uint32_t address);
void init_terminal_process();
void init_PCBManager();
int main() {
    // TODO:debug, delete me plz.
    init();
    __load_program("termina", 0x4200);
    
    init_PCBManager();
    init_INIT_process();
    //init_terminal_process();
    timeout_init();
    clock_install_interupt();
    restoreProcess();
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