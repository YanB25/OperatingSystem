/**
 * @file
 * @brief most importantly low level function used in kernel
 */
#ifndef __UTILITIES_H_
#define __UTILITIES_H_

#include <stdint.h>
#include "ctype.h"
void clear_screen();
void hello_hybrid_programming(); ///< testcase
int add(int, int); ///< testcase
/// unbocked function to test whether kb is hit.
/// WARNING: this function will not remove kbhit
/// in buffer. you need to call readkb to do so.
/// @return return zero if no kb is hit. return ascii
/// otherwise.
int kbhit();
// blocked function to read hit kb.
int readkb();
/** 
 * directly set cursor
 * @param row range 0~24
 * @param col range 0~79
 */
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
/** get the current cursor
 * @return a 16 bits int. the high 8 bits store the row.
 * the low 8 bits store the column.
 */
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
/** no need to use.
 * screen the scrool.
 * @param row_col_lu 16bits. high: row, low: col. left upper point.
 * @param row_col_rd high  16bits row, low: col. right down point.
 * @param lines how many lines to scrool
 * @param direction 0 if scroll up. any int otherwise.
 */
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
static inline void* memcpy(void* dst, const void* src, int16_t size) {
    __asm__ volatile(
        ".intel_syntax noprefix\n"
        "rep movsb\n"
        ".att_syntax\n"
        : /* no output */
        : "S"(src), "D"(dst), "c"(size)
        : "memory"
    );
}
#endif