// init main function.
const char* msg = "now in main function";
extern void init(void);
void main() {
    // here's what I think I should do

    //mm_init(...)
    trap_init();
    blk_dev_init();
    chr_dev_init();
    return;
}

