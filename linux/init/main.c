// init main function.
#include <stdint.h>
#include "../include/asm/system.h"
#include "../include/linux/fork.h"
#include "../include/debug.h"
const char* msg = "now in main function";
extern void trap_init();
extern void sched_init();
void test_write();
void I_AM_HERE(int32_t id);
int system_call();
int32_t printks(const char*);


void main() {
    //BochsBreak();
    trap_init();
    sched_init();
    printks("\nnow in protected mode!\n");
    int errno;
    __asm__ volatile(
        "movl $0x0, %%eax\n"
        "int $0x80\n"
        :"=a"(errno):
    );
    char arr[] = "hello!\n";

    sti();
    int id = fork();
    if (id == 1) {
        printks("111\n");
        int id2 = fork();
        if (id2 == 1) {
            printks("333\n");
        } else {
            printks("444\n");
        }
    } else {
        printks("222\n");
        int id2 = fork();
        if (id2 == 1) {
            printks("555\n");
        } else {
            printks("666\n");
        }
    }
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