#ifndef __UTILITIES_H_
#define __UTILITIES_H_
void clear_screen();
void hello_hybrid_programming();
int add(int, int);
void _put_char(char, int);
void _puts(char*, int, int);

inline void _puts(char* str, int row, int col) {
    int pos = (row * 80 + col) * 2;
    while (*str != '\0') {
        _put_char(*str, pos);
        str++;
        pos += 2;
    }
}
#endif