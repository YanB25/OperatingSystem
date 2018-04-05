#include "kernel.h"
#include "../include/utilities.h"
#include "../user/user.h"
#include "../user/terminal.h"
#include "../include/mystring.h"
#include "../filesystem/API/fsapi.h"
#define true 1
#define false 0
extern void install_interupt();
int main() {
    install_interupt();
    // __asm__("int $0x8\n");
    // __load_program("stoneS");
    clear_screen();
    draw_str("enter help to get help", 0, 30);
    newline();
    terminal();
    return 0;
}