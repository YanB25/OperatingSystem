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
static inline void putln(char* str) {
    puts(str);
    puts("\n\r");
}
#endif