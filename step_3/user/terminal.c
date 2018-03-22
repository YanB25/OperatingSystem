#include "../include/utilities.h"
#include "stone.h"
#define BACK_SPACE 8
const char* PROMT = "yb@yb-thinkpad-e450:~$ ";
int terminal() {
    puts(PROMT);
    int offsetx = 0;
    int offsety = 0;
    while(1) {
        int try = kbhit();
        if (try) {
            int key = readkb();
            switch(key) {
                case('\r'):
                    putch('\n');
                    putch('\r');
                    // putch('\r');
                    puts(PROMT);
                    offsetx = 0;
                    offsety++;
                break;
                case(BACK_SPACE):
                    if (offsetx > 0) {
                        putch(8);
                        putch(' ');
                        putch(8);
                        offsetx--;
                    }
                break;
                case('\t'):
                break;
                default:
                    putch(key);
                    offsetx++;
            }
        }
    }
    return 0;
}