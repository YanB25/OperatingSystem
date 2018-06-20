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
    BochsBreak();
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
    int lock = getsem(0);
    if (id == 1) {
        //testPV();
        int id = fork();
        if (id == 1) {
            p(lock);
            printks("111\n");
        } else {
            printks("222\n");
            v(lock);
        }
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
    end = next(end);
}
void pop() {
    beg = next(beg);
}
//#define D 1000000
#define D 100000
void testPV() {
    full_lock = getsem(15);
    empty_lock = getsem(0);
    puti(full_lock);
    puti(empty_lock);
    beg = end = 0;
    int id = fork();
    if (id == 1) {
        //while(1);
        while(1) {
            for (int i = 0; i < D; ++i) {}
            p(empty_lock);

            printks("push ");

            push();

            puti(beg);
            printks(" ");
            puti(end);
            printks("\n");

            v(full_lock);

        }        
    } else {
        //while(1);
        while (1) {
            for (int i = 0; i < D; ++i) {}
            p(full_lock);
            v(empty_lock);

            pop();
            printks("pop ");
            puti(beg);
            printks(" ");
            puti(end);
            printks("\n");
        }
    }
}