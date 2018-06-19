#include "../include/linux/sched.h"
#include "../include/linux/fork.h"
#include "../include/asm/system.h"
#define NR_SEMAPHORE 256
extern int current;
typedef struct PCB PCB_List_T;
extern PCB_List_T PCB_List[NR_TASKS];
typedef struct Semaphone {
    int value;
    int block_processes[NR_TASKS];
    int bsize;
    int used;
} Semaphone;

Semaphone semaphone_list[NR_SEMAPHORE];

void init_semaphore() {
    for (int i = 0; i < NR_SEMAPHORE; ++i) {
        semaphone_list[i].bsize = 0;
        semaphone_list[i].used = 0; // false
    }
}

int getsem(int value) {
    for (int i = 0; i < NR_SEMAPHORE; ++i) {
        if(semaphone_list[i].used == 0) {
            semaphone_list[i].used = 1;
            semaphone_list[i].value = value;
            semaphone_list[i].bsize = 0;
            return i;
        }
    }
    return -1;
}

int freesem(int id) {
    //TODO: should be refine
    semaphone_list[id].used = 0;
}

void p(int id) {
    cli(); //TODO: maybe bug
    semaphone_list[id].value--;
    if (semaphone_list[id].value < 0) {
        int size = semaphone_list[id].bsize;
        semaphone_list[id].block_processes[size] = current;
        semaphone_list[id].bsize++;
        wait(); //TODO: sti??
    }
}
void v(int id) {
    cli();
    semaphone_list[id].value++;
    if (semaphone_list[id].value <= 0) {
        semaphone_list[id].bsize--;
        int size = semaphone_list[id].bsize;
        PCB_List[size].state == TASK_INTERRUPTIBLE;
    }
}