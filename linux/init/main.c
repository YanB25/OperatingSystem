// init main function.
#include <stdint.h>
#include "../include/asm/system.h"
const char* msg = "now in main function";
extern void trap_init();
extern void sched_init();
void test_write();
void I_AM_HERE(int32_t id);
int32_t printks(const char*);
void main() {
    // b 0x14d5
    // here's what I think I should do

    //mm_init(...)
    trap_init();
    sched_init();
    //blk_dev_init();
    //chr_dev_init();
    //test_write();
    //printks("hello world\nnewline");
    // __asm__ volatile(
    //     "movb $0x0, %%ah\n"
    //     "div %%ah\n"
    //     ::
    // );
    // __asm__ volatile(
    //     "movl 0x28, %%eax\n"
    //     "movw %%ax, %%ds\n"
    //     "movl (0xFFFF), %%eax\n"
    //     ::
    // );
    printks("\nnow in protected mode!");
    sti();
    while(1) {
        //__asm__ volatile(
        //    "int $0x20\n"
        //);
        //I_AM_HERE(6);
    }
    return;
}

