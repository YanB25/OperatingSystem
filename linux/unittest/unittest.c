// NOTICE:
// NOT USE.
// when trap trigger, it dies. so, can no test 
// all testcase once.
#include <stdint.h>
int32_t printks(const char*);
void test_divide_zero_trap() {
    printks("begin to test divide 0\n");
    __asm__ volatile(
        "movb $0x0, %%ah\n"
        "div %%ah\n"
        ::
    );
    printks("test end.\n");
}

void test_general_protection_trap() {
    printks("begin to test general protection trap\n");
    __asm__ volatile(
        "movl 0x28, %%eax\n"
        "movw %%ax, %%ds\n"
        "movl (0xFFFF), %%eax\n"
        ::
    );
    printks("test end.\n");
}

void unittest_testall() {
    test_divide_zero_trap();
    test_general_protection_trap();
}