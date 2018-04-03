__asm__("jmpl $0, $stone\n");

#include "../../include/utilities.h"
#include "stone.h"
#define DELAY (5 * 1e5)
int getKbHit();
void checkBound();

int x;
int y;
int deltax;
int deltay;
int stone() {
    // return 0;
    x = _X;
    y = _Y;
    deltax = 1;
    deltay = 1;
    uint8_t style = 0;

    clear_screen();
    while(1) {
        int key = getKbHit();
        if (key) return key;

        int delay = DELAY;
        while ((--delay) >= 0) continue;

        draw_str(" ", y, x);
        x += deltax;
        y += deltay;

        checkBound();
        draw_str_style("A", y, x, style & 15);
        style++;
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
    if (x <= LEFT_B) deltax = 1;
    if (x >= RIGHT_B) deltax = -1;
    if (y <= UP_B) deltay = 1;
    if (y >= DOWN_B) deltay = -1;
}