#include <stdint.h>
#include "fsutilities.h"
#include "FATMacro.h"

#define BPB_ADDRESS (0x7E0B)
#define FAT_TABLE_ADDRESS (0x8200)
#define ROOT_AREA_ADDRESS (0x8600)
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
    uint16_t rootSectorNth = dataBlockBase + 2 * sectorPerCluster;

    // load FAT table into memory 0x8200
    uint16_t FATTableNth = hiddenSector + reservedSector + 1;
    loadLogicSector(FATTableNth, FAT_TABLE_ADDRESS, 2);
    FAT_ITEM_T* FAT_table = (FAT_ITEM_T*)(FAT_TABLE_ADDRESS);
    // load datablock: root area into memory 0x8600
    loadLogicSector(rootSectorNth, ROOT_AREA_ADDRESS, 1);

    // WARNING, IMPORTANT: if you change cluster into 2 sectors
    // you may also want to change the defination below:
    // loadLogicSector(.., .. 1)  1 -> sectorPerCluster
    // macro filesize2sectors()  func-name -> filesize2clusters()
    FAT_ITEM* pRootEntities = (FAT_ITEM*)(ROOT_AREA_ADDRESS);
    FAT_ITEM_T* FATRootItem = FAT_table + 4;
    for (int16_t i = 0; i < 3; ++i) {
        FAT_ITEM* p = pRootEntities + i;
        if (__fs_strcmp(p->filename, "kernel") == 0) {
            uint16_t cluster = p->blow_cluster;
            uint16_t numOfSectors = filesize2sectors(p->filesize);
            uint16_t kernelSectorNth = dataBlockBase + (cluster * sectorPerCluster);
            for (int16_t j = 0; j < numOfSectors; ++j) {
                loadLogicSector(kernelSectorNth, KERNEL_ADDRESS + j * 0x200, 1);
                cluster = *FATRootItem;
                FATRootItem = FAT_table + cluster;
                kernelSectorNth = dataBlockBase + (cluster * sectorPerCluster);
            }
            break;
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

