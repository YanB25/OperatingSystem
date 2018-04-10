#ifndef __C_TYPE_H_
#define __C_TYPE_H_
#include <stdint.h>
static inline uint8_t isdigit(char ch) {
    return ch >= '0' && ch <= '9';
}
static inline uint8_t isalpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
static inline uint8_t isalnum(char ch) {
    return isdigit(ch) || isalpha(ch);
}
#endif