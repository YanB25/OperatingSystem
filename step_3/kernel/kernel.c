#include "kernel.h"
#include "../include/utilities.h"
#include "../user/user.h"
#include "../user/terminal.h"
#define true 1
#define false 0
int main() {
    clear_screen();
    // int col = sum(10);
    // // int col=20;
    // draw_str("hello world", 5, col);
    // putln("I am here!");
    // putln("hei, i am happy!");
    // draw_str("I love you", 10, 8);
    // putln("can i still output?");
    // jumpToUser();
    terminal();
    return 0;
}