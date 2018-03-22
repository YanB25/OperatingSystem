#ifndef __UTILITIES_H_
#define __UTILITIES_H_
void clear_screen();
void hello_hybrid_programming();
int add(int, int);
void _draw_char(char, int);
// void draw_str(char*, int, int);
void putch(char);
// void puts(char*);

static inline void draw_str(char* str, int row, int col) {
    int pos = (row * 80 + col) * 2;
    while (*str != '\0') {
        _draw_char(*str, pos);
        str++;
        pos += 2;
    }
}
static inline void puts(char* str) {
    while (*str) {
        putch(*str);
        str++;
    }
}
#endif