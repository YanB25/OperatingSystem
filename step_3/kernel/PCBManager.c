#include <stdint.h>
#include <stddef.h>
#include "PCB.h"
/**
 * @brief global infomation and high lever manager
 */


typedef struct PCBManager PCBManager;
PCBManager PCB_manager = {};

void init_terminal_process();
/**
 * warning:
 *     PCBList not initialized
 */
void init_PCBManager() {
    PCB_manager.psize = 1;
    PCB_manager.cur_active = 0; //TODO: this asume at least one p is exist
    PCB_manager.init_id = 1;
    PCB_manager.PCBList[0].pid = 0;
}

// void add_new_process(uint32_t segment) {
//     segment /= 16;
//     PCB_manager.psize++;
//     if (PCB_manager.cur_active == -1) PCB_manager.cur_active = PCB_manager.psize-1;
//     int16_t index = PCB_manager.psize - 1;
//     struct RegisterImage* ri = &(PCB_manager.PCBList[index].register_image);
//     ri->ss = 0;
//     ri->sp = 16*segment + 2048;
//     ri->cs = segment;
//     ri->ds = segment;
//     ri->es = segment;
//     ri->gs = segment;
//     ri->fs = segment;
//     ri->ip = 0;
// 
// 
//     PCB_manager.PCBList[index].pid = PCB_manager.init_id++;
// }
void init_INIT_process() {
    //PCB_manager.psize = 1;
    //PCB_manager.cur_active = 0;
    //struct RegisterImage* ri = &(PCB_manager.PCBList[0].register_image);
    //ri->ip = 0x4200;
    //ri->ss = 0;
    //ri->sp = 3000;
    //ri->cs = 0;
    //ri->es = 0;
    //ri->es = 0;

    //add_new_process(0x10000); ///< for stoneQ
    //TODO: just for test. please change me

    //    PCB_manager.psize = 4;
    //    PCB_manager.cur_active = 0;
    //    struct RegisterImage* ri = &(PCB_manager.PCBList[PCB_manager.cur_active].register_image);

    //    ri->ss = 0;
    //    ri->sp = 0x4000;
    //    ri->cs = 0x1000;
    //    ri->ds = 0x1000;
    //    ri->es = 0x1000;
    //    ri->ax = 0x0000;
    //    ri->cx = 0x1000;
    //    ri->dx = 0x1000;

    //    ri->bp = ri->sp;
    //    ri->ip = 0x00;


    //    struct RegisterImage* ri2 = &(PCB_manager.PCBList[1].register_image);

    //    ri2->ss = 0x00;
    //    ri2->sp = 0x5000;
    //    ri2->cs = 0x1100;
    //    ri2->ds = 0x1100;
    //    ri2->es = 0x1100;

    //    ri2->bp = ri->sp;
    //    ri2->ip = 0x0000;

    //    struct RegisterImage* ri3 = &(PCB_manager.PCBList[2].register_image);
    //    ri3->cs = 0x1200;
    //    ri3->ds = 0x1200;
    //    ri3->es = 0x1200;
    //    ri3->sp = 0x6000;
    //    ri3->ss = 0;

    //    struct RegisterImage* ri4 = &(PCB_manager.PCBList[3].register_image);
    //    ri4->cs = 0x1300;
    //    ri4->ds = 0x1300;
    //    ri4->es = 0x1300;
    //    ri4->sp = 0x7000;
    //    ri4->ss = 0;
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
    do{
        index = (index + 1) % psize;
    } while (PCB_manager.PCBList[index].state == P_DEAD);
    PCB_manager.cur_active = index;
    return &(PCB_manager.PCBList[index].register_image);
}

int32_t get_process_num() {
    return PCB_manager.psize;
}