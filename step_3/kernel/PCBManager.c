#include <stdint.h>
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
    PCB_manager.psize = 0;
    PCB_manager.cur_active = -1;
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
void* get_current_PCB_address() {
    int16_t index = PCB_manager.cur_active;
    struct RegisterImage* ret = &(PCB_manager.PCBList[index].register_image); ///< typecheck for safe.
    return (void*) ret;

}