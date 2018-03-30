#ifndef __FILE_SYSTEM_API_H_
#define __FILE_SYSTEM_API_H_

#include <stdint.h>

#include "../FATMacro.h"
#include "../filesystem.h"
#include "../fsutilities.h"
#include "../filesystem.h"
#include "../../include/mystring.h"
#include "fsErrorCode.h"

#define TYPE_FLDR 0
#define TYPE_FILE 1
#define TYPE_DOC 2

static inline FAT_ITEM* __get_root_dir() {
    return (FAT_ITEM*)(ROOT_AREA_ADDRESS);
}
static inline int16_t __has_next_item(const FAT_ITEM* p) {
    while ((p+1)->filename[0] == S_DEL) {
        p++;
    }
    return (p+1)->filename[0] != S_UNUSED;
}
static inline int16_t __has_prev_item(const FAT_ITEM* p) {
    while ((p-1)->filename[0] == S_DEL) {
        p--;
    }
    return (p-1)->filename[0] != S_UNUSED;
    //TODO: how to deal with it? return false forever
}
static inline FAT_ITEM* __next_item(FAT_ITEM* p) {
    while ((p+1)->filename[0] == S_DEL) {
        p++;
    }
    return p+1;
}
static inline FAT_ITEM* __prev_item(FAT_ITEM* p) {
    while ((p-1)->filename[0] == S_DEL) {
        p--;
    }
    return p-1;
}

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
static inline int16_t __rm_this_file(FAT_ITEM* p) {
    uint16_t mod = p->mod;
    if (mod & FAT_fldr) {
        return ERR_TYPE_FLDR;
    }
    if (mod & FAT_sys) {
        return ERR_SYS_PROTC;
    }
    if (mod & FAT_doc) {
        return ERR_TYPE_DOC;
    }
    const uint8_t* const fn = p->filename;
    if (fn[0] == S_UNUSED) {
        return ERR_NOT_FOUND;
    }
    if (fn[0] == S_DEL) {
        return ERR_NOT_FOUND;
    }
    (p->filename[0]) = S_DEL;
    return NO_ERR;
}
static inline int16_t __run_this_file(FAT_ITEM* p) {
    uint16_t mod = p->mod;
    if (mod & FAT_sys) {
        return ERR_SYS_PROTC;
    }
    if (mod & FAT_fldr) {
        return ERR_TYPE_FLDR;
    }
    if (mod & FAT_doc) {
        return ERR_TYPE_DOC;
    }
    uint16_t cluster = p->blow_cluster;
    uint16_t sectorNth = HIDDEN_SECTOR + RESERVED_SECTOR + 
        NUMBER_OF_FAT * SECTOR_PER_FAT + 
        cluster * SECTOR_PER_CLUSTER + 1;
    uint16_t numOfSector = filesize2sectors(p->filesize);
    loadLogicSector(sectorNth, USER_PROGRAM_ADDRESS, numOfSector);
    return 0;

}
static inline int16_t __load_program(const char* targetFilename) {
    FAT_ITEM* pfat = __get_root_dir();
    if (strcmp(pfat->filename, targetFilename) == 0) {
        return __run_this_file(pfat);
    }
    while (__has_next_item(pfat)) {
        pfat = __next_item(pfat);
        if (strcmp(pfat->filename, targetFilename) == 0) {
            return __run_this_file(pfat);
        }
    }
    return ERR_NOT_FOUND;

}
#endif