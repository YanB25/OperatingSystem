#include <stdint.h>
int32_t fork() {
    int32_t ret;
    __asm__(
        "movw $0x02, %%eax\n"
        "int $0x80\n"
        : "=r"(ret)
        : /* no input*/
    );
    return ret;
}