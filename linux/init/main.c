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

    while(1) {}
    return;
}

