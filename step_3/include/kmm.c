#include "kmm.h"
#include <stdint.h>
uint32_t* MM_LITTLE_HEAD = (uint32_t*)LITTLE_BEGIN;
uint32_t* MM_MID_HEAD = (uint32_t*)MID_BEGIN;
uint32_t* MM_LARGE_HEAD = (uint32_t*)LARGE_BEGIN;


void __mm__enter() {
    __asm__ volatile(
        ".intel_syntax noprefix\n"
        "mov ax, 0x1000\n"
        "mov ds, ax\n"
        ".att_syntax\n"
    );
}
 void __mm__leave() {
    __asm__ volatile(
        ".intel_syntax noprefix\n"
        "mov ax, 0\n"
        "mov ds, ax\n"
        ".att_syntax\n"
    );
}
void init_mm() {
    __mm__enter();

    MM_LITTLE_HEAD = (uint32_t*)LITTLE_BEGIN;
    MM_MID_HEAD = (uint32_t*)MID_BEGIN;
    MM_LARGE_HEAD = (uint32_t*)LARGE_BEGIN;

    int i = 0;
    void* p = (void* )(LITTLE_BEGIN);
    while (p + BLOCK_LITTLE_SIZE * i <= (void*)LITTLE_END) {
        *(uint32_t*) (p + BLOCK_LITTLE_SIZE * i) = (uint32_t)(p + BLOCK_LITTLE_SIZE * (i+1));
        i++;
    }


    i = 0;
    p = (void*)(MID_BEGIN);
    while (p + BLOCK_MID_SIZE * i <= (void*)MID_END) {
        *(uint32_t*) (p + BLOCK_MID_SIZE * i) = (uint32_t) (p + BLOCK_MID_SIZE * (i+1));
        i++;
    }

    i = 0;
    p = (void*)(LARGE_BEGIN);
    while (p + BLOCK_LARGE_SIZE*i <= (void*)LARGE_END) {
        *(uint32_t*) (p + BLOCK_LARGE_SIZE * i) = (uint32_t) (p + BLOCK_LARGE_SIZE * (i+1));
        i++;
    }
    __mm__leave();
}

uint32_t mm_get_block_nth(int32_t nth) {
    __mm__enter();
    if (nth < 0) return 0;
    uint32_t* p = (uint32_t*)0;
    while (nth--) {
        p = (uint32_t*) (*p);
    }
    __mm__leave();
    return ((uint32_t) p) + MEM_BASE;
}

uint32_t mm_malloc(int32_t size) {
    __mm__enter();
    uint32_t** phead = 0;
    if (size > BLOCK_LARGE_SIZE) {
        return 0;
    } else if (size > BLOCK_MID_SIZE) {
        phead = &MM_LARGE_HEAD;
        if (*phead >= (uint32_t*)LARGE_END) return 0;
    } else if (size > BLOCK_LITTLE_SIZE) {
        phead = &MM_MID_HEAD;
        if (*phead >= (uint32_t*)MID_END) return 0;
    } else {
        phead = &MM_LITTLE_HEAD;
        if (*phead >= (uint32_t*)LITTLE_END) return 0;
    }
    uint32_t ret = (uint32_t)(*phead);
    (*phead) = (uint32_t*)**phead;

    __mm__leave();
    return ret + (uint32_t)MEM_BASE;
}
uint32_t mm_get_HEAD() {
    __mm__enter();
    uint32_t ret = (uint32_t)MM_LARGE_HEAD;
    __mm__leave();
    return ret;
}

void mm_free(uint32_t addr, int32_t size) {
    __mm__enter();
    addr -= MEM_BASE;
    if (size >= BLOCK_LARGE_SIZE) return;
    else if (size > BLOCK_MID_SIZE) {
        *(uint32_t*)addr = (uint32_t)MM_LARGE_HEAD;
        MM_LARGE_HEAD = (uint32_t*)addr;
    } else if (size > BLOCK_LITTLE_SIZE) {
        *(uint32_t*)addr = (uint32_t)MM_MID_HEAD;
        MM_MID_HEAD = (uint32_t*) addr;
    } else {
        *(uint32_t*) addr = (uint32_t)MM_LITTLE_HEAD;
        MM_LITTLE_HEAD = (uint32_t*) addr;
    }
    __mm__leave();
}