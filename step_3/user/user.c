#include "../include/utilities.h"
int sum(int end) {
    int sum = 0;
    for (int i = 0; i < end; ++i) {
        sum += i;
    }
    return sum;
}
void jumpToUser() {
    puts("if you see me, i will be very happy");
}