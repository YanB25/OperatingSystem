//TODO: delete ALL OF THIS.
#ifndef __SYS_H_
#define __SYS_H_
#include "../linux/sched.h"
char arr[] = "hello!\n";
int printks(const char*);
int32_t first_empty_pcb();
void copy_process(int32_t, int32_t);
extern int32_t current;

typedef struct PCB PCB_LIST_T;
extern PCB_LIST_T PCB_List[NR_TASKS];

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
    return 1;
}

int sys_exit() {
    PCB_List[current].state = TASK_NOT_USED;
    reschedule();
    return 1;
}
fn_ptr sys_call_table[] = {
    test_print, print_hello, sys_fork, sys_wait, sys_exit
};


#endif