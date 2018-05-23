//TODO: delete ALL OF THIS.
int printks(const char*);
int test_print() {
    printks("enter first sys call\n");
    printks("leave first sys call\n");
    return 0;
}
fn_ptr sys_call_table[] = {
    test_print
};