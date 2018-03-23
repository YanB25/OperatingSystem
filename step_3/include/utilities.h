#ifndef __UTILITIES_H_
#define __UTILITIES_H_
#include <stdarg.h>
void clear_screen();
void hello_hybrid_programming();
int add(int, int);
void _draw_char(char, int);
void putch(char);
// unbocked function to test whether kb is hit
// return zero if no kb is hit. return ascii
// otherwise.
// WARNING: this function will not remove kbhit
// in buffer. you need to call readkb to do so.
int kbhit();
// blocked function to read hit kb.
int readkb();
static inline void draw_str(char const* str, int row, int col) {
    int pos = (row * 80 + col) * 2;
    while (*str != '\0') {
        _draw_char(*str, pos);
        str++;
        pos += 2;
    }
}
static inline void puts(char const* str) {
    while (*str) {
        putch(*str);
        str++;
    }
}
static inline void putln(char const* str) {
    puts(str);
    puts("\n\r");
}
static inline void puti(int num) {
    char _buffer[30];
    int index = 0;
    if (num < 0) {
        putch('-');
        num = -num;
    }
    if (num == 0) {
        putch('0');
        return;
    }
    while (num) {
        _buffer[index++] = num % 10 + '0';
        num /= 10;
    }
    for (int i = index-1; i >= 0; --i) {
        putch(_buffer[i]);
    }
}
static inline void putiln(int num) {
    puti(num);
    putln("");
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
#endif