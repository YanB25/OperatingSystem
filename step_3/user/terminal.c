#include "../include/utilities.h"
#include "stone.h"
const char* PROMT = "yb@yb-thinkpad-e450:~\% ";
int terminal() {
    puts(PROMT);
    while(1) {
        int try = kbhit();
        if (try) {
            int key = readkb();
            if (key == 'q') {
                stone();
            }
            if (key == '\r') {
                putch('\n');
                putch('\r');
                // putch('\r');
                puts(PROMT);
            } else {
                putch(key);
            }
        }
    }
    return 0;
}