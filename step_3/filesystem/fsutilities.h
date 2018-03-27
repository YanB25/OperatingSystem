#ifndef __FS_UTILITIES_H_
#define __FS_UTILITIES_H_
#include <stdint.h>
void loadLogicSector(uint16_t lgsector, uint16_t addr);
void loadSector(uint16_t track, uint16_t head, uint16_t sector, uint16_t addr);
#endif