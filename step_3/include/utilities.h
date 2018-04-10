#ifndef __UTILITIES_H_
#define __UTILITIES_H_

#include <stdarg.h>
#include <stdint.h>
#include "graphic.h"
#include "ctype.h"
#define DEFAULT_STYLE 0x0F
void clear_screen();
void hello_hybrid_programming();
int add(int, int);
static inline int16_t _draw_char(char ch, int offset, uint8_t style) {
    uint16_t written_data = ch | (style << 8);
    __asm__ volatile (
        "movb $1, %%ah\n"
        "int $0x2B\n"
        : /* no output */
        : "c"(written_data), "D"(offset)
        : "cc", "ax", "memory"
    );
    return 1;

}
int16_t putch(char);
// unbocked function to test whether kb is hit
// return zero if no kb is hit. return ascii
// otherwise.
// WARNING: this function will not remove kbhit
// in buffer. you need to call readkb to do so.
int kbhit();
// blocked function to read hit kb.
int readkb();
static inline int16_t padding(int16_t num) {
    for (int16_t i = 0; i < num; ++i) {
        putch(' ');
    }
    return num;
}
static inline int16_t __uts_read_int(const char* s, int16_t* readNum) {
    int16_t fac = 1;
    int16_t cnt = 0;
    if (*s == '-') {
        fac = -1;
        s++;
        cnt++;
    }
    int16_t ret = 0;
    while (*s && *s >= '0' && *s <= '9') {
        ret = ret * 10 + (*s - '0');
        s++;
        cnt++;
    }
    *readNum = ret;
    return cnt;
}
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
static inline int16_t putiln(int num) {
    int16_t cnt = 0;
    cnt += puti(num);
    cnt += newline();
    return cnt;
}
static inline int printf(const char* format, ...) {
    va_list valist;
    int16_t pcnt = 0;
    int narg = 0;
    int index = 0;
    while (format[index]) {
        if (format[index] == '%') narg++;
        index++;
    }

    va_start(valist, narg);

    index = 0;
    while (format[index]) {
        int16_t putSize = 0;
        int16_t delta = 0;
        int16_t digitLength = 0;
        if (format[index] == '%') {
            if ((format[index+1] >= '0' && format[index+1] <= '9') | format[index+1] == '-') {
                // putln("get digit!");
                digitLength = __uts_read_int(format + index + 1, &putSize);
                // putiln(digitLength);
            }
            if (format[index + digitLength + 1] == 'd') {
                int data = va_arg(valist, int);
                delta = puti(data);
            } else if (format[index+ digitLength + 1] == 'c') {
                int c = va_arg(valist, int);
                delta = putch(c);
            } else if (format[index + digitLength + 1] == 's') {
                char* str = va_arg(valist, char*);
                delta = puts(str);
            } else if (format[index + digitLength + 1] == '%'){
                delta = putch('%');
            }
            if (delta < putSize) {
                padding(putSize - delta);
            }
            pcnt += delta;
            index += 2 + digitLength;
            continue;
        } else if (format[index] == '\n' || format[index] == '\r') {
            pcnt += putch('\n');
            pcnt += putch('\r');
        } else {
            pcnt += putch(format[index]);
        }
        index++;
    }
    va_end(valist);
    return pcnt;
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
static inline void set_cursor(uint8_t row, uint8_t col) {
    uint16_t _DX_ = col | (row << 8);
    __asm__ volatile(
        "pushw %%bx\n"
        "pushw %%ax\n"
        "movb $0x02, %%ah\n"
        "movw $0, %%bx\n"
        "int $0x10\n"
        "popw %%ax\n"
        "popw %%bx\n"
        : /* no output */
        : "d"(_DX_)
        : "cc", "memory"
    );
}
static inline uint16_t get_cursor(){
    uint16_t cursor_pos;
    __asm__ volatile(
        "pushw %%ax\n"
        "pushw %%bx\n"
        "movb $0x03, %%ah\n"
        "movb $0, %%bh\n"
        "int $0x10\n"
        "popw %%bx\n"
        "popw %%ax\n"
        : "=d"(cursor_pos)
        : /* no input */
        : "cc", "cx"
    );
    return cursor_pos;
}
// row_col_lu: high: row, low: col
// row_col_rd: high: row, low: col
static inline void __screen_scroll(
    uint16_t row_col_lu, // for DX
    uint16_t row_col_rd, // for CX
    uint8_t lines, // for AL
    uint16_t direction
    ){
    uint8_t funCode;
    if (direction == 0) {
        funCode = 0x06;
    } else {
        funCode = 0x07;
    }
    __asm__ volatile(
        "pushw %%bx\n"
        "movb %[funCode], %%ah\n"
        "movb $0x07, %%bh\n"
        "int $0x10\n"
        "popw %%bx\n"
        : /*no output*/
        : "a"(lines), "c"(row_col_lu), "d"(row_col_rd), [funCode]"rm"(funCode)
        : "cc", "memory", "bx"
    );
}
#endif