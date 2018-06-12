//TODO: delete ALL OF THIS.
char arr[] = "hello!\n";
int printks(const char*);
int32_t first_empty_pcb();
void copy_process(int32_t, int32_t);
extern int32_t current;
int test_print() {
    printks("enter first sys call\n");
    printks("leave first sys call\n");
    return 0;
}
int print_hello() {
    printks(arr);
    arr[0] ++;
    return 0;
}

int sys_fork() {
    cli();
    printks("fork\n");
    int32_t pindex = first_empty_pcb();
    printks("after get empty pcb\n");
    if (pindex == -1) {
        return -1;
    }
    copy_process(pindex, current);
    printks("after copy_process\n");
    __asm__("xchgw %%bx, %%bx\n"::); //TODO: delete me
    sti();
    printks("after sti\n");
    return 1;
}

fn_ptr sys_call_table[] = {
    test_print, print_hello, sys_fork
};