#ifndef __UTILITIES_H_
#define __UTILITIES_H_
#include <stdarg.h>
#include <stdint.h>
#include "graphic.h"
#define DEFAULT_STYLE 0x0F
void clear_screen();
void hello_hybrid_programming();
int add(int, int);
int16_t _draw_char(char ch, int offset, uint8_t style);
int16_t putch(char);
// unbocked function to test whether kb is hit
// return zero if no kb is hit. return ascii
// otherwise.
// WARNING: this function will not remove kbhit
// in buffer. you need to call readkb to do so.
int kbhit();
// blocked function to read hit kb.
int readkb();
static inline int16_t draw_str(char const* str, int row, int col) {
    int pos = (row * 80 + col) * 2;
    int16_t index = 0;
    while (*str != '\0') {
        _draw_char(*str, pos, DEFAULT_STYLE);
        str++;
        index++;
        pos += 2;
    }
    return index;
}
static inline int16_t newline() {
    putch('\n');
    putch('\r');
    return 2;
}
static inline int16_t draw_str_style(char const* str, int row, int col, uint8_t style) {
    int pos = (row * 80 + col) * 2;
    int16_t index = 0;
    while (*str != '\0') {
        _draw_char(*str, pos, style);
        str++;
        index++;
        pos += 2;
    }
    return index;
}
static inline int16_t draw_char_style(char ch, int row, int col, uint8_t style) {
    int pos = (row * 80 + col) * 2;
    return _draw_char(ch, pos, style);
}
static inline int16_t puts(char const* str) {
    int16_t index = 0;
    while (*str) {
        putch(*str);
        str++;
        index++;
    }
    return index;
}
static inline int16_t putln(char const* str) {
    int16_t cnt = 0;
    cnt += puts(str);
    cnt += puts("\n\r");
    return cnt;
}
static inline int16_t puti(int32_t num) {
    char _buffer[30];
    int index = 0;
    if (num < 0) {
        putch('-');
        num = -num;
    }
    if (num == 0) {
        putch('0');
        return 0;
    }
    while (num) {
        _buffer[index++] = num % 10 + '0';
        num /= 10;
    }
    for (int i = index-1; i >= 0; --i) {
        putch(_buffer[i]);
    }
    return index;
}
static inline void putiln(int num) {
    int16_t cnt = 0;
    cnt += puti(num);
    cnt += newline();
}
static inline int printf(const char* format, ...) {
    va_list valist;
    int narg = 0;
    int index = 0;
    while (format[index]) {
        if (format[index] == '%') narg++;
        index++;
    }

    va_start(valist, narg);

    index = 0;
    while (format[index]) {
        if (format[index] == '%') {
            if (format[index+1] == 'd') {
                int data = va_arg(valist, int);
                puti(data);
            } else if (format[index+1] == 'c') {
                int c = va_arg(valist, int);
                putch(c);
            } else if (format[index+1] == 's') {
                char* str = va_arg(valist, char*);
                puts(str);
            } else if (format[index+1] == '%'){
                putch('%');
            }
            index += 2;
            continue;
        } else if (format[index] == '\n' || format[index] == '\r') {
            putch('\n');
            putch('\r');
        } else {
            putch(format[index]);
        }
        index++;
    }
    va_end(valist);
    return 0;
}
static inline int getch() {
    return readkb();
}
static inline int16_t putn(const char* s, uint16_t size) {
    for (int i = 0; i < size; ++i) {
        if (!s[i]) {
            return i;
        }
        putch(s[i]);
    }
    return size;
}
#endif