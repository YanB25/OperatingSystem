#ifndef __FILE_SYSTEM_API_H_
#define __FILE_SYSTEM_API_H_

#include <stdint.h>

#include "../FATMacro.h"
#include "../filesystem.h"
#include "../fsutilities.h"
#include "../filesystem.h"

#define TYPE_FLDR 0
#define TYPE_FILE 1
#define TYPE_DOC 2

static inline FAT_ITEM* __get_root_dir() {
    return (FAT_ITEM*)(ROOT_AREA_ADDRESS);
}
static inline int16_t __has_next_item(const FAT_ITEM* p) {
    return (p+1)->filename[0] != S_UNUSED;
}

#define __next_item(FAT_ITEM_P) (FAT_ITEM_P+1)

static inline int16_t __FAT_item_type(const FAT_ITEM* p) {
    if (p->mod & FAT_fldr) {
        return TYPE_FLDR;
    } else if (p->mod & FAT_doc) {
        return TYPE_DOC;
    }
    return TYPE_FILE;
}
static inline FAT_ITEM* __jmp_into_dir(const FAT_ITEM* p) {
    uint16_t cluster = p->blow_cluster;
    uint16_t numOfSector = filesize2sectors(p->filesize);
    uint16_t sectorNth = HIDDEN_SECTOR + RESERVED_SECTOR + 
        NUMBER_OF_FAT * SECTOR_PER_FAT + 
        cluster * SECTOR_PER_CLUSTER + 1;
    loadLogicSector(sectorNth, DATA_BLOCK_ADDRESS, numOfSector); 
    return (FAT_ITEM*)(DATA_BLOCK_ADDRESS);
}
#endif