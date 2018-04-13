#ifndef __FS_UTILITIES_H_
#define __FS_UTILITIES_H_
#include <stdint.h>
#define lgsector2sector(X) (((X-1)%18)+1) ///< logic sector to sector
#define lgsector2head(X) (((X-1)/18)%2) ///< logic sector to head
#define lgsector2track(X) ((X-1)/36) ///< logic sector 2 track
void loadSector(uint16_t track, uint16_t head, uint16_t sector, uint16_t addr, uint16_t num);
static inline void loadLogicSector(uint16_t lgsector, uint16_t addr, uint16_t num) {
    uint16_t sectorN = lgsector2sector(lgsector);
    uint16_t headN = lgsector2head(lgsector);
    uint16_t trackN = lgsector2track(lgsector);
    loadSector(trackN, headN, sectorN, addr, num);
}

#define filesize2sectors(X) ((X+511)/512)

/**
 * strcmp only for file system
 */
static inline int16_t __fs_strcmp(const char* s1, const char* s2) {
    const char* lhs = s1;
    const char* rhs = s2;
    while (*lhs && *rhs) {
        if (*lhs != * rhs) {
            return *lhs - *rhs;
        }
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}


#endif