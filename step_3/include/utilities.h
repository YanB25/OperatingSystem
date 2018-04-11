#ifndef __UTILITIES_H_
#define __UTILITIES_H_

#include <stdint.h>
#include "ctype.h"
void clear_screen();
void hello_hybrid_programming();
int add(int, int);
// unbocked function to test whether kb is hit
// return zero if no kb is hit. return ascii
// otherwise.
// WARNING: this function will not remove kbhit
// in buffer. you need to call readkb to do so.
int kbhit();
// blocked function to read hit kb.
int readkb();
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
static inline void scroll_up_one_line() {
    __screen_scroll((2 << 8) + 1, (23 << 8) + 78, 1, 0);
}
#endif