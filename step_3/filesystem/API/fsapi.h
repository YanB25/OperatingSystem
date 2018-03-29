#ifndef __FILE_SYSTEM_API_H_
#define __FILE_SYSTEM_API_H_

#include <stdint.h>

#include "../FATMacro.h"
#include "../filesystem.h"

#define TYPE_FLDR 0
#define TYPE_FILE 1

static inline FAT_ITEM* __get_root_dir() {
    return (FAT_ITEM*)(ROOT_AREA_ADDRESS);
}
static inline int16_t __has_next_item(const FAT_ITEM* p) {
    return (p+1)->filename[0] != S_UNUSED;
}

#define __next_item(FAT_ITEM_P) (FAT_ITEM_P+1)

static inline int16_t __FAT_item_type(const FAT_ITEM* p) {
    if (p->mod & FAT_fldr == 0x1) {
        return TYPE_FLDR;
    } 
    return TYPE_FILE;
}

#endif