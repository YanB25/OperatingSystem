/**
 * @file
 * @brief my stdio.h implementation
 * 
 */
#ifndef __STDIO_H_
#define __STDIO_H_
#include "graphic.h"
#include "utilities.h"
#include <stdarg.h>
#define DEFAULT_STYLE_DARK (G_DEFAULT | G_DARK)
#define DEFAULT_STYLE (G_DEFAULT)

static inline int32_t d2x(int32_t d) {
    if (d <= 9) return d + '0';
    return (d-10) + 'A';
}

/**
 * low level char output function
 * @param ch that character that want to draw
 * @param offset the offset from (0, 0) in terminal
 * counted by ((row * 80) + column) * 2
 * @param style print style
 * @return always 1
 */
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
static inline int16_t putch_style(char ch, uint8_t style) {
    uint16_t cursor = get_cursor();
    uint8_t crow = cursor >> 8;
    uint8_t ccol = cursor & 0b11111111;
    if (ch == '\r') {
        set_cursor(crow, 1);
    } else if (ch == '\n') {
        if (crow >= 23) {
            scroll_up_one_line();
        } else {
            set_cursor(crow + 1, ccol);
        }
    } else if (ch == '\b') {
        set_cursor(crow, ccol-1);
    }
    else if (ch == '\t') {
        set_cursor(crow, ccol + 4);
    }
    else {
        _draw_char(ch, (crow * 80 + ccol)*2, style);
        ccol++;
        if (ccol == 79) {
            crow++;
            ccol = 1;
        }
        set_cursor(crow, ccol);
    }
    return 1;
}
static inline int16_t putch(char ch) {
    return putch_style(ch, DEFAULT_STYLE);
}

/**
 * output space specified by num
 * @param num how much space to output
 * @return same as num
 */
static inline int16_t padding(int16_t num) {
    for (int16_t i = 0; i < num; ++i) {
        putch(' ');
    }
    return num;
}
/**
 * @param str string to output
 * @param row the starting row in terminal (0 based, count from left)
 * @param col (0 based, count from up)
 */
static inline int16_t draw_str(char const* str, int row, int col) {
    int pos = (row * 80 + col) * 2;
    int16_t index = 0;
    while (*str != '\0') {
        _draw_char(*str, pos, DEFAULT_STYLE_DARK);
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
/** put string with style
 */
static inline int16_t puts_style(char const* str, uint8_t style) {
    int16_t index = 0;
    while (*str) {
        putch_style(*str, style);
        str++;
        index++;
    }
    return index;
}
static inline int16_t puts(char const* str) {
    return puts_style(str, DEFAULT_STYLE);
}
static inline int16_t putln(char const* str) {
    int16_t cnt = 0;
    cnt += puts(str);
    cnt += puts("\n\r");
    return cnt;
}

/**
 * no need to used this.
 * inner function that used to parce int from string
 */
static inline int16_t __uts_read_int(const char* s, int32_t* readNum) {
    int16_t fac = 1;
    int16_t cnt = 0;
    if (*s == '-') {
        fac = -1;
        s++;
        cnt++;
    }
    int32_t ret = 0;
    while (*s && *s >= '0' && *s <= '9') {
        ret = ret * 10 + (*s - '0');
        s++;
        cnt++;
    }
    *readNum = (int32_t)ret * fac;
    return cnt;
}

/**
 * put integer.
 * @param num the int to be print
 */
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
static inline int32_t putx(int32_t num) {
    if (num == 0) {
        puts("0x0");
        return 3;
    }
    char buffer[10] = {};
    int32_t idx = 0;
    int32_t ret = 0;
    if (num < 0) {
        putch('-');
        ret++;
        num = -num;
    }
    puts("0x");
    while (num) {
        buffer[idx++] = d2x(num % 16);
        num /= 16;
        ret++;
    }
    while (idx) {
        putch(buffer[--idx]);
    }
    return ret;

}
/**
 * almost same as printf.
 * currently support %d, %s, %c, and %<num>d ...
 * @return TODO: BUG.
 */
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
        int32_t putSize = 0;
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
            } else if (format[index + digitLength + 1] == 'x') {
                int32_t xint = va_arg(valist, int32_t);
                delta = putx(xint);
            }
            else if (format[index+ digitLength + 1] == 'c') {
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
static inline int32_t sscanf(const char* s, const char* format, ...) {
    //FIXME: there's something wrong.
    //  when %d is interpreted as int32_t, it is wrong when pass in int16_t type and parce a negative number
    // when is interpreted as int16_t, it is wrong .. 32 bits.
    va_list valist;
    int16_t pcnt = 0;
    int16_t index = 0;
    int16_t nargs = 0;
    while (format[index]) {
        if (format[index] == '%') nargs++;
        index++;
    }

    va_start(valist, nargs);

    index = 0;
    int16_t s_index = 0;
    int16_t s_offset;
    while (format[index]) {
        if (format[index] == '%') {
            if (format[index + 1] == 'c') {
                char* pc = va_arg(valist, char*);
                *pc = s[s_index];
                s_offset = 1;
            }
            else if (format[index+1] == 'd') {
                if (!isdigit(s[s_index]) && s[s_index] != '-') {
                    // printf("not digit, get %c\n", s[s_index]);
                    return pcnt;
                }
                int32_t* pd = va_arg(valist, int32_t*);
                s_offset = __uts_read_int(s+s_index, pd);
                //printf("inner %d\n", *pd);
            }
            else if (format[index+1] == 's') {
                char* pstr = va_arg(valist, char*);
                while (s[s_index] && !isblank(s[s_index])) {
                    *pstr = s[s_index];
                    pstr++;
                    s_index++;
                }
                s_offset = 0;
                *pstr = '\0';
            }
            index += 2;
            s_index += s_offset;
            pcnt++;
        } 
        else {
            // below is normal match
            if (format[index] == ' ') {
                while (isblank(s[s_index])) {
                    s_index++;
                }
                index++;
            }
            else if (format[index] == s[s_index]) {
                index++;
                s_index++;
            } else {
                // printf("not same, %c and %c\n", format[index], s[s_index]);
                return pcnt;
            }
        }
    }

    va_end(valist);
    return pcnt;
}
static inline int32_t putxln(int32_t num) {
    int32_t ret = 0;
    ret += putx(num);
    ret += newline();
    return ret;
}
#endif