#include "../include/utilities.h"
#include "../include/stdio.h"
char ch = 'A';
#define DELAY 2
#define UpBound 12
#define DownBound 13
int16_t up = 0;
int16_t down = 0;
int16_t delay = DELAY;
void callback();
void timeout() {
    _draw_char(ch++, 0, 0x0F);
    callback();
}
void callback() {
    if (delay --> 0) return;
    delay = DELAY;
    if (up - 1 >= 0) {
        draw_char_style(' ', up-1, 78, DEFAULT_STYLE);
    } else {
        draw_char_style(' ', UpBound - 1, 78, DEFAULT_STYLE);
    }
    if (down + 1 <= 24) {
        draw_char_style(' ', down+1, 78, DEFAULT_STYLE);
    } else {
        draw_char_style(' ', DownBound , 78, DEFAULT_STYLE);
    }
    draw_char_style(' ', up, 78, G_BG_WHITE | G_DARK);
    draw_char_style(' ', down, 78, G_BG_WHITE | G_DARK);
    up = (up+1) % UpBound;
    down = (down-1) < DownBound ? 24 : down-1;
}