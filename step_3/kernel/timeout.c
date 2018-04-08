#include "../include/utilities.h"
char ch = 'A';
#define DELAY 2
#define LeftBound 39
#define RightBound 40
int16_t left = 0;
int16_t right = 0;
int16_t delay = DELAY;
void callback();
void timeout() {
    _draw_char(ch++, 0, 0x0F);
    callback();
}
void callback() {
    if (delay --> 0) return;
    delay = DELAY;
    if (left - 1 >= 0) {
        draw_char_style(' ', 24, left-1, DEFAULT_STYLE);
    } else {
        draw_char_style(' ', 24, LeftBound, DEFAULT_STYLE);
    }
    if (right + 1 <= 79) {
        draw_char_style(' ', 24, right + 1, DEFAULT_STYLE);
    } else {
        draw_char_style(' ', 24, RightBound, DEFAULT_STYLE);
    }
    draw_char_style(' ', 24, left, G_BG_WHITE | G_DARK);
    draw_char_style(' ', 24, right, G_BG_WHITE | G_DARK);
    left = (left+1) % (LeftBound + 1);
    right = (right-1) < RightBound ? 79 : right-1;
}