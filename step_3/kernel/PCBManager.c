#include <stdint.h>
#include <stddef.h>
#include "PCB.h"
/**
 * @brief global infomation and high lever manager
 */
#define PCB_MANAGER_PROCESS_SIZE 20
struct PCBManager {
    PCB PCBList[PCB_MANAGER_PROCESS_SIZE];
    int16_t psize;
    int16_t cur_active;

    /* functions */
}__attribute__((packed));

typedef struct PCBManager PCBManager;
PCBManager PCB_manager;

/**
 * warning:
 *     PCBList not initialized
 */
void init_PCBManager() {
    PCB_manager.psize = 1;
    PCB_manager.cur_active = 0;
    //TODO: important!!!!!!fixme!!!!!
    //FIXME: important!!
}
/**
 * @biref testcase
 * 
 * this is only a testcase
 * TODO:please delete me after debug finish
 */
void init_testcase() {
    PCB_manager.psize = 1;
    PCB_manager.cur_active = 0;
    struct RegisterImage* ri = &(PCB_manager.PCBList[PCB_manager.cur_active].register_image);
    ri->sp = 1;
    ri->ss = 2;
    ri->gs = 3;
    ri->fs = 4;
    ri->es = 5;
    ri->ds = 6;
    ri->ax = 0x1234;
    ri->flags = 0x5678;
}
void init_INIT_process() {
    PCB_manager.psize = 1;
    PCB_manager.cur_active = 0;
    struct RegisterImage* ri = &(PCB_manager.PCBList[PCB_manager.cur_active].register_image);

    ri->ss = 0;
    ri->sp = 0x4000;
    ri->cs = 0;
    ri->ds = 0;
    ri->es = 0;

    ri->bp = ri->sp;
    ri->ip = 0xA200;
}
struct RegisterImage* get_current_PCB_address() {
    int16_t index = PCB_manager.cur_active;
    int16_t psize = PCB_manager.psize;
    if (index == -1 || psize == 0) return NULL;
    return &(PCB_manager.PCBList[index].register_image); ///< typecheck for safe.
}

struct RegisterImage* get_next_PCB_address() {
    int16_t index = PCB_manager.cur_active;
    int16_t psize = PCB_manager.psize;
    if (index == -1 || psize <= 0) return NULL;
    index = (index + 1) % psize;
    return &(PCB_manager.PCBList[index].register_image);
}