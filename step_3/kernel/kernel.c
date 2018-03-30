#include "kernel.h"
#include "../include/utilities.h"
#include "../user/user.h"
#include "../user/terminal.h"
#include "../include/mystring.h"
#include "../filesystem/API/fsapi.h"
#define true 1
#define false 0
int main() {
    clear_screen();
    draw_str("enter help to get help", 0, 30);
    // draw_char_style('A', 0, 10, 0x8F);
    newline();
    terminal();
    return 0;
}