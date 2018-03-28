#ifndef __FS_UTILITIES_H_
#define __FS_UTILITIES_H_
#include <stdint.h>
#define lgsector2sector(X) (((X-1)%18)+1)
#define lgsector2head(X) ((X-1)/18)
#define lgsector2track(X) ((X-1)/36)
void loadSector(uint16_t track, uint16_t head, uint16_t sector, uint16_t addr, uint16_t num);
static inline void loadLogicSector(uint16_t lgsector, uint16_t addr, uint16_t num) {
    uint16_t sectorN = lgsector2sector(lgsector);
    uint16_t headN = lgsector2head(lgsector);
    uint16_t trackN = lgsector2track(lgsector);
    loadSector(trackN, headN, sectorN, addr, num);
}
#endif