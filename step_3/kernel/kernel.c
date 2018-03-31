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
    //draw_char_style('A', 0, 10, G_DEFAULT);
    // draw_char_style('A', 0, 11, G_DEFAULT_DARK);
    newline();
    terminal();
    return 0;
}