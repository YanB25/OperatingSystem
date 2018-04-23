#ifndef __PCB_H_
#define __PCB_H_

#include <stdint.h>
#define P_RUNNING (0)
#define P_SLEEPING (1)

/**
 * @brief a copy of registers for PCB
 * 
 * the order of registers is as follows:
 * 1) flags, cs, ip(48 bits) pushed by interupt
 * 2) ax ~ di, pushed by pusha
 * 3) ds ~ ss, pushed manualy
 * 4) sp, mov value of sp into [sp-2]
 * after all of the registers have been ready in the stack
 * a special memcpy is call to copy all of the value
 * from user stack to PCB's RegisterImage.
 * 
 * note that, old_sp is never used. it is the sp value before pusha(in step(2)) happened
 * , which is not correct.
 */
struct RegisterImage {
    uint16_t sp;
    uint16_t ss;
    uint16_t gs;
    uint16_t fs;
    uint16_t es;
    uint16_t ds;
    // pusha
    uint16_t di;
    uint16_t si;
    uint16_t bp;
    uint16_t old_sp;
    uint16_t bx;
    uint16_t dx;
    uint16_t cx;
    uint16_t ax;
    // pushed by int
    uint16_t ip;
    uint16_t cs;
    uint16_t flags;
}__attribute__((packed));

typedef struct PCB* pPCB;

/** @brief book keeping infomation for PCB
 * rest_time_slice: a positive int, meaning how many time slices this process has before process switch.
 */
struct PBookKeeping {
    int16_t rest_time_slice;
}__attribute__((packed));

struct PCB {
    struct RegisterImage register_image;
    int16_t pid;
    pPCB pFatherPCB;
    uint8_t state;
}__attribute__((packed));

typedef struct PCB PCB;
#endif
