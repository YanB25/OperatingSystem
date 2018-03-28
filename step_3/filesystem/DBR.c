#include <stdint.h>
#include "fsutilities.h"
#include "FATMacro.h"

#define BPB_ADDRESS (0x7E0B)
#define ROOT_AREA_ADDRESS (0x8200)
#define KERNEL_ADDRESS (0xA100)
int16_t __fs_strcmp(const char* s1, const char* s2);

uint16_t DBRkernelLoader() {
    void* bpb = (void*)(BPB_ADDRESS);
    uint16_t sectorPerCluster = *(uint8_t*)(bpb+2);
    uint16_t reservedSector = *(uint16_t*)(bpb+3);
    uint16_t numberOfFAT = *(uint8_t*)(bpb + 5);
    uint16_t sectorPerFAT = *(uint8_t*)(bpb + 11);
    uint16_t hiddenSector = *(uint8_t*)(bpb + 17);
    uint16_t dataBlockBase = hiddenSector + reservedSector 
        + numberOfFAT * sectorPerFAT
        + 1;
    uint16_t rootSectorN = dataBlockBase + 2 * sectorPerCluster;


    // load datablock: root area into memory 0x8200
    loadLogicSector(rootSectorN, ROOT_AREA_ADDRESS, 1);

    //FIXME: IMPORTANT! do not assume file continues in datablock;
    // should be fix
    FAT_ITEM* pRootEntities = (FAT_ITEM*)(ROOT_AREA_ADDRESS);
    for (int16_t i = 0; i < 3; ++i) {
        FAT_ITEM* p = pRootEntities + i;
        if (__fs_strcmp(p->filename, "kernel") == 0) {
            uint16_t cluster = p->blow_cluster;
            uint16_t numOfSectors = filesize2sectors(p->filesize);
            uint16_t kernelSectorNth = dataBlockBase + (cluster * sectorPerCluster);
            uint16_t kernelInMem = KERNEL_ADDRESS;
            loadLogicSector(kernelSectorNth, kernelInMem, numOfSectors);
        }
    }
    __asm__("jmpl $0, $0xA100");
    return 0;
}

int16_t __fs_strcmp(const char* s1, const char* s2) {
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

