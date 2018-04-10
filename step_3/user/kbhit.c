#include <stdint.h>
#include "../include/utilities.h"
int16_t row = 8;
int16_t column = 10;
int16_t evenFlag = 1;
void kb_custom_interupt() {
    if (evenFlag) {
        draw_str_style("ouch!", row, column, TO_FN(G_RED));
        column += 8;
        if (column > 79-10) {
            column = 10;
            row++;
        }
    }
    evenFlag = !evenFlag;
    return;
}