// init main function.
#include <stdint.h>
#include "../include/asm/system.h"
const char* msg = "now in main function";
extern void trap_init();
extern void sched_init();
void test_write();
void I_AM_HERE(int32_t id);
int system_call();
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
    printks("\nnow in protected mode!\n");
    sti();
    int errno;
    __asm__ volatile(
        "movl $0x0, %%eax\n"
        "int $0x80\n"
        :"=a"(errno):
    );
    __asm__("int $0x20\n"::);
    char arr[] = "hello!\n";
    //move_to_user_mode();

    while(1) {
        __asm__(
            "movl $0x1, %%eax\n"
            "int $0x80\n"
            ::
        );
    }
    //while (1);
    return;
}