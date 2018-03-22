#include "kernel.h"
#include "../include/utilities.h"
#include "../user/user.h"
#include "../user/terminal.h"
#include "../include/mystring.h"
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
    if (strcmp("hello", "hello") == 0) {
        putln("equal 1");
    }
    if (strcmp("hello", "hello ") == 0) {
        putln("equal 2");
    }
    if (strcmp("hello", "hell") == 0) {
        putln("equal 3");
    }
    char s1[5] = "abcd";
    char s2[5];
    puti(strlen("hello world!"));
    char* tar = memcpy(s2, s1, 5);
    putln(tar);

    // terminal();
    return 0;
}