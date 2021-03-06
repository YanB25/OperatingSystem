/**
 * @file
 * @brief
 * called when clock interupt occur.
 * draw beautiful graph in terminal. 
 */
#include "../include/utilities.h"
#include "../include/stdio.h"
char ch = 'A';
#define DELAY 2
int delX[] = {1, 0, -1, 0};
int delY[] = {0, 1, 0, -1};
int direction = 0;
int x = 0;
int y = 0;
uint8_t style = 0;
void draw_terminal_board();
char nextAlphabet(char);
void timeout_init() {
    ch = 'A';
    x = 0;
    y = 0;
    style = 0;
    direction = 0;
    delX[0] = 1; delX[1] = 0; delX[2] = -1; delX[3] = 0;
    delY[0] = 0; delY[1] = 1; delY[2] = 0; delY[3] = -1;
}
void timeout() {
    // _draw_char(ch++, 0, 0x0F);
    draw_terminal_board();
}
void draw_terminal_board() {
    style = (style+1) & 0b00001111;
    ch = nextAlphabet(ch);
    draw_char_style(ch, y, x, style);
    if (y == 0 && x == 0) direction = 0;
    if (y == 0 && x == 79) direction = 1;
    if (y == 24 && x == 79) direction = 2;
    if (y == 24 && x == 0) direction = 3;
    y += delY[direction];
    x += delX[direction];
}
char nextAlphabet(char c) {
    if (c == 'z') return 'A';
    if (c == 'Z') return 'a';
    return c+1;
}