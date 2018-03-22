#include "stone_helper.h"
#ifndef X
    #define X 5
    #define Y 5
    #define DelX 1
    #define DelY 1
#endif
FUNCTION_NAME(FN_NAME_SUFFIX)
{
    x = X;
    y = Y;
    deltax = DelX;
    deltay = DelY;

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
