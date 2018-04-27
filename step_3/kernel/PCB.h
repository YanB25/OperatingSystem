#ifndef __PCB_H_
#define __PCB_H_

#include <stdint.h>
#include "../include/utilities.h"
#include "../include/kmm.h"
#define P_RUNNING (0)
#define P_SLEEPING (1)
#define P_DEAD (2)

#define PCB_MANAGER_PROCESS_SIZE 20
#define PCB_COMMENT_LENGTH 30
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
    // pushed by interupt
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
    pPCB* pFatherPCB;
    uint8_t state;
    uint32_t address;
    // char comment[PCB_COMMENT_LENGTH];
}__attribute__((packed));
typedef struct PCB PCB;
struct PCBManager {
    PCB PCBList[PCB_MANAGER_PROCESS_SIZE];
    int16_t psize;
    int16_t cur_active;
    int32_t init_id;

    /* functions */
}__attribute__((packed));
extern struct PCBManager PCB_manager;
void init_PCBManager();
static inline int32_t add_new_process(uint32_t segment) {
    segment /= 16;

    int32_t index = -1;
    for (int32_t i = 0; i < PCB_manager.psize; ++i) {
        if (PCB_manager.PCBList[i].state == P_DEAD) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        PCB_manager.psize++;
        index = PCB_manager.psize - 1;
    }

    if (PCB_manager.cur_active == -1) PCB_manager.cur_active = PCB_manager.psize-1;

    struct RegisterImage* ri = &(PCB_manager.PCBList[index].register_image);
    ri->ss = 0;
    ri->sp = 16*segment + 0x700; //TODO: think twice: how sp should be
    ri->cs = segment;
    ri->ds = segment;
    ri->es = segment;
    ri->gs = segment;
    ri->fs = segment;
    ri->ip = 0;


    int32_t pid = PCB_manager.init_id++;
    PCB_manager.PCBList[index].pid = pid;
    PCB_manager.PCBList[index].state = P_RUNNING;
    PCB_manager.PCBList[index].address = segment*16;
    //strcpy(PCB_manager.PCBList[index].comment, "None"); //TODO: should be altered
    return pid;
}
static inline int32_t kill_process(uint32_t pid) {
    for (int32_t i = 0; i < PCB_manager.psize; ++i) {
        if (PCB_manager.PCBList[i].pid == pid && PCB_manager.PCBList[i].state == P_RUNNING) {
            PCB_manager.PCBList[i].state = P_DEAD;
            mm_free(PCB_manager.PCBList[i].address, 0x800);
            return 0; //TODO: should return errno
        }
    }
    return 1;
}
void init_INIT_process();
struct RegisterImage* get_current_PCB_address();
struct RegisterImage* get_next_PCB_address();
int32_t get_process_num();
static inline void __print_process_info() {
    printf("%10s %3s %10s\n", "comment", "pid", "address");
    for (int32_t i = 0; i < PCB_manager.psize; ++i) {
        if (PCB_manager.PCBList[i].state != P_DEAD) {
            printf("%10s %3d %10x\n", "none", PCB_manager.PCBList[i].pid, PCB_manager.PCBList[i].address);
        }
    }
}
#endif
