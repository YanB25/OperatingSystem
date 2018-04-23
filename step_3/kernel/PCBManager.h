#ifndef __PCB_MANAGER_H_
#define __PCB_MANAGER_H_
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
void try_context_switch() {
    if (PCB_manager.psize <= 1) return;
}
#endif