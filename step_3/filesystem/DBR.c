#include <stdint.h>
extern uint16_t mydata;
uint16_t DBRkernelLoader() {
    uint16_t b = 2;
    uint16_t d = b + mydata;
    // int d = b + 3;
    return d;
}