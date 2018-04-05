#include "../include/utilities.h"
char ch = 'A';
void timeout() {
    _draw_char(ch++, 0, 0x0F);
}