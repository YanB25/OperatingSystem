/**
 * @file
 * @brief all the macro needed by FAT inner implementation
 */
#ifndef __FAT_MACRO_H_
#define __FAT_MACRO_H_
#include <stdint.h>

typedef uint16_t FAT_ITEM_T;

/**
 * @defgroup FATItemState
 * @brief describe the fat item state. whether current item is 
 * unused, '.' and '..', or deleted
 */
///@{
#define S_UNUSED ((uint8_t)0x00) ///< item unused
#define S_DOTS ((uint8_t)0x2E) ///< it is '.' or '..'
#define S_DEL ((uint8_t)0xE5) ///< has been deleted, can be reused
///@}
struct FAT_ITEM {
    uint8_t filename[8];
    uint8_t extendname[3];
    uint8_t mod;
    
    uint8_t res; ///< reserved
    uint8_t created_time; ///< ms
    uint16_t hms; ///< hour minute second
    uint16_t ymd; ///< year month day
    uint16_t recent_access_ymd;
    uint16_t bhigh_cluster;

    uint16_t modify_hms;
    uint16_t modify_ymd;
    uint16_t blow_cluster;
    uint32_t filesize; ///< in bytes
}__attribute__((packed));

typedef struct FAT_ITEM FAT_ITEM;

/** @defgroup fileMod
 * @brief mod of a file(directory)
 */
///@{
#define FAT_rw (0) ///< readable and writable
#define FAT_ro (1) ///< read only
#define FAT_hid (1 << 1) ///< hidden file
#define FAT_sys (1 << 2) ///< system file
#define FAT_fldr (1 << 4) ///< folder
#define FAT_doc (1 << 5) ///< partition reserved doc
#define FAT_ITEM_EMPTY {0,0,0,0,0,0,0,0,0,0,0,0,0}

#define FAT_ITEM_SIZE (32)
///@}

#endif