/**
 * @brief
 * NOTICE: it is only use as a workaround.
 */
#include <stdint.h>
void putch(char);
void newline();
int32_t printks(const char* str) {
    while (*str) {
        if (*str == '\n') {
            newline();
        }
        else {
            putch(*str);
        }
        str++;
    }
}