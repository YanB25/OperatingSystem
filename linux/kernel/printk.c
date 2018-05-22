/**
 * @brief
 * NOTICE: it is only use as a workaround.
 */
#include <stdint.h>
void putch(char);
int32_t printks(const char* str) {
    while (*str) {
        putch(*str);
        str++;
    }
}