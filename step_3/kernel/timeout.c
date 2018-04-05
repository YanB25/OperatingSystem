#include "../include/utilities.h"
char ch = 'A';
int16_t left = 3;
int16_t right = 76;
int16_t dir = -1;
int32_t delay = 1e1;
void terminalRuningLight();
void timeout() {
    _draw_char(ch++, 0, 0x0F);
    terminalRuningLight();
}

void terminalRuningLight() {
    if (--delay > 0) return;
    delay = 1e1;
    puts("hello world");
}