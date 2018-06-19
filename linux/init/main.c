// init main function.
#include <stdint.h>
#include "../include/asm/system.h"
#include "../include/linux/fork.h"
#include "../include/debug.h"
#include "../include/linux/semaphore.h"
#include "../include/linux/sched.h"
const char* msg = "now in main function";
extern void trap_init();
extern void sched_init();
void test_write();
void I_AM_HERE(int32_t id);
void testPV();
int system_call();
int32_t printks(const char*);
extern int current;
typedef struct PCB PCB_List_T;
extern PCB_List_T PCB_List[NR_TASKS];


void puti(int number) ;

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
    // int id = fork();
    // if (id == 1) {
    //     printks("111\n");
    //     int id2 = fork();
    //     if (id2 == 1) {
    //         printks("333\n");
    //     } else {
    //         printks("444\n");
    //     }
    // } else {
    //     printks("222\n");
    //     int id2 = fork();
    //     if (id2 == 1) {
    //         printks("555\n");
    //     } else {
    //         printks("666\n");
    //     }
    // }
    // p(lock);
    // p(lock);
    // p(lock);
    //int mgnum = 1234;
    //int mgnum2 = 5678;
    int id = fork();
    if (id == 1) {
        testPV();
    }
    while(1);
    return;
}

void test_second_process() {
    // printks("enter test\n");
    // int id = fork();
    // if (id == 1) {
    //     printks("I am 1\n");
    //     while(1);
    // } else {
    //     printks("I am not 1\n");
    //     while(1);
    // }

    // int id = fork();
    // if (id == 1) {
    //     printks("777\n");
    //     exit();
    // } else {
    //     wait();
    //     printks("888\n");
    // }
    while(1) {
        printks("bb\n");
        // __asm__(
        //     "movl $0x1, %%eax\n"
        //     "int $0x80\n"
        //     ::
        // );
    }
}
int full_lock;
int empty_lock;
int queue[25];
int beg = 0;
int end = 0;
int next(int i) { return (i + 1) % 20; }
int full() {
    return next(end) == beg;
}
int empty() {
    return beg == end;
}
void push() {
    if (full())
        p(full_lock);
    if (empty()) {
        v(empty_lock);
    }
    end = next(end);
}
void pop() {
    if (empty()) {
        p(empty_lock);
    }
    if (full()) {
        v(full_lock);
    }
    beg = next(beg);
}
#define D 1000000
void testPV() {
    full_lock = getsem(1);
    empty_lock = getsem(1);
    beg = end = 0;
    int id = fork();
    if (id == 1) {
        while(1) {
            for (int i = 0; i < D; ++i) {}
            push();
            printks("push ");
            puti(beg);
            printks(" ");
            puti(end);
            printks("\n");
        }        
    } else {
        while (1) {
            for (int i = 0; i < D; ++i) {}
            pop();
            printks("pop\n");
            puti(beg);
            printks(" ");
            puti(end);
            printks("\n");
        }
    }
}