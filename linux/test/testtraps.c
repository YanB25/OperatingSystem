void test_divide_zero() {
    __asm__ volatile(
        "movl $0, %%edx\n"
        "divl %%edx\n"
        ::
    );
}