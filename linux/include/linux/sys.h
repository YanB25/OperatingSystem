//TODO: delete ALL OF THIS.
#ifndef __SYS_H_
#define __SYS_H_
#include "../linux/sched.h"
#include "../linux/semaphore.h"
#include "../linux/fork.h"
char arr[] = "hello!\n";
int printks(const char*);
int32_t first_empty_pcb();
void copy_process(int32_t, int32_t);
extern int32_t current;

typedef struct PCB PCB_LIST_T;
extern PCB_LIST_T PCB_List[NR_TASKS];

extern Semaphone semaphone_list[NR_SEMAPHORE];

#define reschedule()\
__asm__("jmpl $0x08, $return_from_timer_interrupt\n"::)

int test_print() {
    printks("enter first sys call\n");
    printks("leave first sys call\n");
    return 0;
}
int print_hello() {
    printks(arr);
    arr[0] ++;
    return 0;
}

int sys_fork() {
    printks("[debug]fork\n");
    int32_t pindex = first_empty_pcb();
    if (pindex == -1) {
        return -1;
    }
    copy_process(pindex, current);
    return PCB_List[current].register_image.eax;
}

int sys_wait() {
    PCB_List[current].state = TASK_UNINTERRUPTIBLE;
    reschedule(); //TODO: maybe bug;
    return 1;
}

int sys_exit() {
    PCB_List[current].state = TASK_NOT_USED;
    int parent_id = PCB_List[current].parent_id;
    if (parent_id != -1) {
        if (PCB_List[parent_id].state == TASK_UNINTERRUPTIBLE) {
            PCB_List[parent_id].state = TASK_INTERRUPTIBLE;
        }
    }
    reschedule();
    return 1;
}

extern Semaphone semaphone_list[NR_SEMAPHORE];
int do_getsem(int value) {
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
int do_free_sem(int id) {
    semaphone_list[id].used = 0;
    return 0;
}
int do_p(int id) {
    cli(); //TODO: maybe bug
    // printks("p ");
    // puti(id);
    // printks(" ");
    //puti(semaphone_list[id].value);
    semaphone_list[id].value--;
    //puti(semaphone_list[id].value);
    // puti(semaphone_list[id].value);
    // printks("\n");
    if (semaphone_list[id].value < 0) {
        int size = semaphone_list[id].bsize;
        semaphone_list[id].block_processes[size] = current;
        semaphone_list[id].bsize++;
        // printks(" !!!wait!! \n");
        wait(); //TODO: sti??
    }
    sti();
    return 0;
}
int do_v(int id) {
    cli();
    // printks("v ");
    // puti(id);
    // printks(" ");
    // printks("v, id is ");
    // puti(id);
    // printks("\n");
    // printks("v operation\n");
    semaphone_list[id].value++;
    //puti(semaphone_list[id].value);
    int val = semaphone_list[id].value;
    // printks("after is  ");
    // puti(val);
    // printks("\n");
    if (semaphone_list[id].value <= 0) {
        semaphone_list[id].bsize--;
        int size = semaphone_list[id].bsize;
        int block_processes_id = semaphone_list[id].block_processes[size];
        // printks("wake up id is ");
        // puti(block_processes_id);
        PCB_List[block_processes_id].state = TASK_INTERRUPTIBLE;
        // printks("   ");
        // printks(" v-work ");
    }
    // puti(semaphone_list[id].value);
    // printks("\n");
    sti();
    return 0;
}
fn_ptr sys_call_table[] = {
    test_print, print_hello, sys_fork, sys_wait, sys_exit, do_getsem, do_free_sem, do_p, do_v
};

#endif