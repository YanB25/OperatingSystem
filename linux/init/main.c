// init main function.
#include <stdint.h>
#include "../include/asm/system.h"
const char* msg = "now in main function";
extern void trap_init();
extern void sched_init();
void test_write();
void I_AM_HERE(int32_t id);
int system_call();
extern uint32_t tmp_STACK_end;
int32_t printks(const char*);
#define BochsBreak() \
__asm__("xchgw %%bx, %%bx\n"::)
int fork();
void main() {
    uint32_t tmp = (uint32_t)&tmp_STACK_end;
    trap_init();
    sched_init();
    printks("\nnow in protected mode!\n");
    int errno;
    BochsBreak();
    __asm__ volatile(
        "movl $0x0, %%eax\n"
        "int $0x80\n"
        :"=a"(errno):
    );
    char arr[] = "hello!\n";

    // while(1) {
    //     printks("Notice me please!!!!\n");
    // }
    sti();
    int id = fork();

    // if (id == 1) {
    //     printks("I am 1\n");
    //     while(1);
    // } else {
    //     printks("I am not 1\n");
    //     while(1);
    // }
    while(1);
    return;
}

void test_second_process() {
    BochsBreak();
    // printks("enter test\n");
    // int id = fork();
    // if (id == 1) {
    //     printks("I am 1\n");
    //     while(1);
    // } else {
    //     printks("I am not 1\n");
    //     while(1);
    // }

    while(1) {
        // __asm__(
        //     "movl $0x1, %%eax\n"
        //     "int $0x80\n"
        //     ::
        // );
    }
}