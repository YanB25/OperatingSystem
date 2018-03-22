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