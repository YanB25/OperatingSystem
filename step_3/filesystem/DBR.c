#include <stdint.h>
#include "fsutilities.h"
#define BPB_ADDRESS (0x7E0B)
uint16_t DBRkernelLoader() {
    void* bpb = (void*)(BPB_ADDRESS);
    uint16_t reservedSector = *(uint16_t*)(bpb+3);
    uint16_t numberOfFAT = *(uint8_t*)(bpb + 5);
    uint16_t sectorPerFAT = *(uint8_t*)(bpb + 11);
    uint16_t hiddenSector = *(uint8_t*)(bpb + 17);
    return 0;
}