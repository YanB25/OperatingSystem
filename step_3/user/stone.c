#include "../include/utilities.h"
int getKbHit();
int stone() {
    while(1) {
        int key = getKbHit();
        if (key) return key;

        int delay = 1000000;
        while ((--delay) >= 0) continue;

        putln("new loop");
    }
}

int getKbHit() {
    int try = kbhit();
    if (try) {
        int key = readkb();
        return key;
    }
    return 0;
}