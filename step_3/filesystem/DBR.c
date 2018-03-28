#include <stdint.h>
#include "fsutilities.h"
#include "FATMacro.h"

#define BPB_ADDRESS (0x7E0B)
#define FAT_TABLE_ADDRESS (0x8000)

uint16_t DBRkernelLoader() {
    void* bpb = (void*)(BPB_ADDRESS);
    uint16_t reservedSector = *(uint16_t*)(bpb+3);
    uint16_t numberOfFAT = *(uint8_t*)(bpb + 5);
    uint16_t sectorPerFAT = *(uint8_t*)(bpb + 11);
    uint16_t hiddenSector = *(uint8_t*)(bpb + 17);
    uint16_t blockSectorN = hiddenSector + reservedSector + numberOfFAT * sectorPerFAT + 1;

    uint16_t loadAddr = 0x8000;
    loadLogicSector(blockSectorN, loadAddr, 1);

    void* FAT_table = (void*)(FAT_TABLE_ADDRESS);
    struct FAT_ITEM* pFATItem = (struct FAT_ITEM*)(FAT_table + (FAT_ITEM_SIZE * 2));

    return 0;
}