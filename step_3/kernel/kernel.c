#include "kernel.h"
#include "../include/utilities.h"
#include "../user/user.h"
#define true 1
#define false 0
int main() {
    clear_screen();
    int col = sum(10);
    // int col=20;
    draw_str("hello world", 5, col);
    puts("I am here!");
    puts("\n\rhei, i am happy!");
    draw_str("I love you", 10, 8);
    puts("\n\rcan i still output?");
    jumpToUser();
    while(true) {}
    return 0;
}