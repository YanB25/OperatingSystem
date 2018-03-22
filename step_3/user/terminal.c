#include "../include/utilities.h"
int terminal() {
    puts("yb@yb-thinkpad-e450:~\% ");
    while(1) {
        int try = kbhit();
        if (try) {
            int key = readkb();
            putch(key);
        }
    }
    return 0;
}