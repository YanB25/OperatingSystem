#include "../include/utilities.h"
#define DELAY (1e5)
int getKbHit();
void checkBound();

int x;
int y;
int deltax;
int deltay;
int stone() {
    x = 5;
    y = 5;
    deltax = 1;
    deltay = 1;

    clear_screen();
    while(1) {
        int key = getKbHit();
        if (key) return key;

        int delay = DELAY;
        while ((--delay) >= 0) continue;

        x += deltax;
        y += deltay;

        checkBound();
        draw_str("A", y, x);
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
void checkBound() {
    if (x == 0) deltax = 1;
    if (x == 79) deltax = -1;
    if (y == 0) deltay = 1;
    if (y == 24) deltay = -1;
}