#include "mystring.h"
int strcmp(const char* lhs, const char* rhs) {
    int index = 0;
    while (lhs[index] && rhs[index]) {
        if (lhs[index] != rhs[index]) {
            return lhs[index] - rhs[index];
        } 
        index++;
    }
    return lhs[index] - rhs[index];
}
int strlen(const char* str) {
    int index = 0;
    while (str[index]) index++;
    return index;
}
void* memcpy(void* dst, void const * src, int n) {
    for (int i = 0; i < n; ++i) {
        ((char *)dst)[i] = ((char*)src)[i];
    }
    return dst;
}