#include "../../include/utilities.h"

#ifndef __STONE_HELPER_H_
#define __STONE_HELPER_H_

#if defined(LU)
    #define X (4)
    #define Y (5)
    #define LeftBound (0)
    #define RightBound (39)
    #define UpBound (0)
    #define DownBound (12)
    #define DelX (1)
    #define DelY (1)
    #define FN_NAME_SUFFIX Q
#elif defined(RU)
    #define X (65)
    #define Y (5)
    #define LeftBound (40)
    #define RightBound (79)
    #define UpBound (0)
    #define DownBound (13)
    #define DelX (-1)
    #define DelY (1)
    #define FN_NAME_SUFFIX W
#elif defined(LD)
    #define X (4)
    #define Y (20)
    #define LeftBound (0)
    #define RightBound (39)
    #define UpBound (13)
    #define DownBound (24)
    #define DelX (1)
    #define DelY (-1)
    #define FN_NAME_SUFFIX A
#elif defined(RD)
    #define X (75)
    #define Y (20)
    #define LeftBound (39)
    #define RightBound (79)
    #define UpBound (13)
    #define DownBound (24)
    #define DelX (-1)
    #define DelY (-1)
    #define FN_NAME_SUFFIX S
#else 
    #define X (75)
    #define Y (20)
    #define LeftBound (39)
    #define RightBound (79)
    #define UpBound (13)
    #define DownBound (24)
    #define DelX (-1)
    #define DelY (-1)
    #define FN_NAME_SUFFIX S
#endif


#define MAKE_FN_NAME(x) int stone ## x (void)
#define FUNCTION_NAME(signal) MAKE_FN_NAME(signal)

#define DELAY (4 * 1e5)
int x;
int y;
int deltax;
int deltay;

static inline int getKbHit() {
    int _try = kbhit();
    if (_try) {
        int key = readkb();
        return key;
    }
    return 0;
}
static inline void checkBound() {
    if (x == LeftBound) deltax = 1;
    if (x == RightBound) deltax = -1;
    if (y == UpBound) deltay = 1;
    if (y == DownBound) deltay = -1;
}
#endif