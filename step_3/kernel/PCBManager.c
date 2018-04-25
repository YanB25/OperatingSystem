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
void init_terminal_process() {
    // PCB_manager.psize++;
    // int16_t index = PCB_manager.psize-1;
    // struct RegisterImage* ri = &(PCB_manager.PCBList[index].register_image);
    // ri->ss = 0;
    // ri->sp = 
}
void init_INIT_process() {
    //TODO: just for test. please change me
    PCB_manager.psize = 4;
    PCB_manager.cur_active = 0;
    struct RegisterImage* ri = &(PCB_manager.PCBList[PCB_manager.cur_active].register_image);

    ri->ss = 0;
    ri->sp = 0x4900;
    ri->cs = 0x0420;
    ri->ds = 0x0420;
    ri->es = 0x0420;
    ri->ax = 0x4200;
    ri->cx = 0x607;
    ri->bx = 1;
    ri->dx = 0x201;

    ri->bp = ri->sp;
    ri->ip = 0x00;


    struct RegisterImage* ri2 = &(PCB_manager.PCBList[1].register_image);

    ri2->ss = 0x00;
    ri2->sp = 0x5190;
    ri2->cs = 0x04A0;
    ri2->ds = 0x04A0;
    ri2->es = 0x04A0;
    ri2->ax = 0x4A00;
    ri2->cx = 0x607;
    ri2->bx = 1;
    ri2->dx = 0x201;

    ri2->bp = ri->sp;
    ri2->ip = 0x0000;

    struct RegisterImage* ri3 = &(PCB_manager.PCBList[2].register_image);
    ri3->cs = 0x0520;
    ri3->ds = 0x0520;
    ri3->es = 0x0520;
    ri3->sp = 0x5090;
    ri3->ss = 0;

    struct RegisterImage* ri4 = &(PCB_manager.PCBList[3].register_image);
    ri4->cs = 0x05A0;
    ri4->ds = 0x05A0;
    ri4->es = 0x05A0;
    ri4->sp = 0x0610;
    ri4->ss = 0;
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
    PCB_manager.cur_active = index;
    return &(PCB_manager.PCBList[index].register_image);
}