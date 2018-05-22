// init main function.
const char* msg = "now in main function";
extern void trap_init();
void main() {
    // b 0x14d5
    // here's what I think I should do

    //mm_init(...)
    trap_init();
    //blk_dev_init();
    //chr_dev_init();

    // __asm__ volatile(
    //     "movl $0x8003, %%eax\n"
    //     "movl $0, %%ecx\n"
    //     "divl %%ecx\n"
    //     ::
    // );
    __asm__ volatile(
        "movl $0, %%edx\n"
        "divl %%edx\n"
        ::
    );
    while(1) {}
    return;
}

