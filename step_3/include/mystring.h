#ifndef __STRING_H_
#define __STRING_H_
#include <stdint.h>

static inline int16_t strlen(const char* str) {
    int index = 0;
    while (str[index]) index++;
    return index;
}

int strcmp(const char*, const char*);
static inline int16_t strchr(const char* str, char chr) {
    const char* p = str;
    while (*p) {
        if (*p == chr) {
           return p - str; 
        }
        p++;
    }    
    return -1;
}
static inline int16_t strstr(const char* src, const char* tar) {
    int16_t src_size = strlen(src);
    int16_t tar_size = strlen(tar);
    int jmp = 0;
    for (int i = 0; i < src_size; ++i) {
        for (int j = 0; j < tar_size; ++j) {
            if (!tar[j] || !src[i+j] || src[i+j] != tar[j]) {
                jmp = 1;
                break;
            }
        }
        if (jmp == 0) {
            return i;
        } else {
            jmp = 0;
        }
    }
    return -1;
}
#endif