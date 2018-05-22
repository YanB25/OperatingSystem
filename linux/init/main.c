// init main function.
#include <stdint.h>
const char* msg = "now in main function";
extern void trap_init();
void test_write();
int32_t printks(const char*);
void main() {
    // b 0x14d5
    // here's what I think I should do

    //mm_init(...)
    trap_init();
    //blk_dev_init();
    //chr_dev_init();
    //test_write();
    printks("hello world\nnewline");
    while(1) {}
    return;
}

