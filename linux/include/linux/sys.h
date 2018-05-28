//TODO: delete ALL OF THIS.
char arr[] = "hello!\n";
int printks(const char*);
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

fn_ptr sys_call_table[] = {
    test_print, print_hello
};