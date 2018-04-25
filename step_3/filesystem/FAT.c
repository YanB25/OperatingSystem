/** @file
 * @brief FAT table
 */
#include <stdint.h>
#include "FATMacro.h"
FAT_ITEM_T fat_items[] = {
    0xFFF0, //res
    0xFFF0, //res
    0xFFFF, // 2
    0xFFFF, // 3
    0x0005, // 4
    0x0006, // 5
    0x0007, // 6
    0x0008, // 7
    0x0009, // 8
    0x000A, // 9
    0x000B, // 10
    0x001E, // 11 //TODO: kernel jmp to 1E
    0xFFFF, // 12
    0xFFFF, // 13
    0x000F, // 14 // program Q start
    0x0010, // 15 
    0x0011, // 16
    0xFFFF, // 17 // program Q end
    0x0013, // 18 // program W start
    0x0014, // 19
    0x0015, // 20
    0xFFFF, // 21 // program W end
    0x0017, // 22 // program A start
    0x0018, // 23
    0x0019, // 24
    0xFFFF, // 25 // program A end
    0x001B, // 26 // program S start
    0x001C, // 27
    0x001D, // 28
    0xFFFF, // 29 // program S end
    0x001F, // 30 //TODO: kernel part 2
    0x0020, // 31
    0x0021, // 32
    0x0022, // 33
    0x0023, // 34
    0x0024, // 35
    0x0025, // 36
    0x0026, // 37
    0x0027, // 38
    0x0028, // 39
    0x0029, // 40
    0x002A, // 41
    0x002B, // 42
    0x002C, // 43
    0x002D, // 44
    0xFFFF, // 45 // kernel end
    0x002F, // 46 // terminal start
    0x0030, // 47
    0x0031, // 48
    0x0032, // 49
    0x0033, // 50
    0x0034, // 51
    0x0035, // 52
    0x0036, // 53
    0x0037, // 54
    0x0038, // 55
    0x0039, // 56
    0x003A, // 57
    0x003B, // 58
    0x003C, // 59
    0x003D, // 60
    0xFFFF, // 61 //terminal end
    0xFFFF, // 41
    0xFFFF, // 41
};
