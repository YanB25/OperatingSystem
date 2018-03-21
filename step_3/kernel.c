#include "kernel.h"
#include "utilities.h"
#define true 1
#define false 0
int main() {
    clear_screen();
    _puts("hello world", 5, 10);
    while(true) {}
    return 0;
}