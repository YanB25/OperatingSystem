#include "../include/utilities.h"
char ch = 'A';
int16_t left = 0;
int16_t delay = 10;
void callback();
void timeout() {
    _draw_char(ch++, 0, 0x0F);
    callback();
}
void callback() {
    if (delay-- > 0) return;
    delay = 10;
    if (left - 1 >= 0) {
        draw_char_style(' ', 2, left-1, DEFAULT_STYLE);
    }
    draw_char_style('!', 2, left, DEFAULT_STYLE);
    left = (left+1) % 50;
}