#include <stdint.h>
#include "../include/asm/system.h"
int32_t fork() {
    cli();
    int32_t ret;
    __asm__(
        "movl $0x02, %%eax\n"
        "int $0x80\n"
        : "=r"(ret)
        : /* no input*/
    );
    sti();
    return ret;
}