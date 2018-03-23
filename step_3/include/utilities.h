#ifndef __UTILITIES_H_
#define __UTILITIES_H_
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
#endif