/**
 * @file
 * \brief below define the api for filesystem.
 *  they are low level api. 
 */
#ifndef __FILE_SYSTEM_API_H_
#define __FILE_SYSTEM_API_H_

#include <stdint.h>

#include "../FATMacro.h"
#include "../filesystem.h"
#include "../fsutilities.h"
#include "../filesystem.h"
#include "../../include/mystring.h"
#include "fsErrorCode.h"
#include "../../include/utilities.h"
#include "../../include/stdio.h"
/**
 * @defgroup fileType
 * @brief file types for return value
 * 
 */
///@{
#define TYPE_FLDR 0 ///< type file directory
#define TYPE_FILE 1 ///< type file 
#define TYPE_DOC 2 ///< type (reserved) document for file system
///@}

/**
 * return a pointer pointed to root directory
 * @param None
 * @return pointer to fat item.
 */ 
static inline FAT_ITEM* __get_root_dir() {
    return (FAT_ITEM*)(ROOT_AREA_ADDRESS);
}
/**
 * whether a fat item has an available next item.
 * available means not deleted
 */
static inline int16_t __has_next_item(const FAT_ITEM* p) {
    while ((p+1)->filename[0] == S_DEL) {
        p++;
    }
    return (p+1)->filename[0] != S_UNUSED;
}
/**
 * @see __has_next_item
 */
static inline int16_t __has_prev_item(const FAT_ITEM* p) {
    while ((p-1)->filename[0] == S_DEL) {
        p--;
    }
    return (p-1)->filename[0] != S_UNUSED;
    //TODO: how to deal with it? return false forever
}
/**
 * get the next item of a fat item
 * @param p fat item pointer
 */
static inline FAT_ITEM* __next_item(FAT_ITEM* p) {
    while ((p+1)->filename[0] == S_DEL) {
        p++;
    }
    return p+1;
}
/**
 * @see __next_item
 */
static inline FAT_ITEM* __prev_item(FAT_ITEM* p) {
    while ((p-1)->filename[0] == S_DEL) {
        p--;
    }
    return p-1;
}

/**
 * return the type of a fat item
 * @return macro indicating the type
 * @see fileType
 */
static inline int16_t __FAT_item_type(const FAT_ITEM* p) {
    if (p->mod & FAT_fldr) {
        return TYPE_FLDR;
    } else if (p->mod & FAT_doc) {
        return TYPE_DOC;
    }
    return TYPE_FILE;
}
/** whether the item is showable
 * @return true only if it is not @ref TYPE_DOC
 * @see fileType
 */
static inline int16_t __FAT_showable_item(const FAT_ITEM* p) {
    return __FAT_item_type(p) != TYPE_DOC;
}
/** jump into the directory that the pointer points
 * @param p the directory that is currently pointing
 * @return a new pointer that point at the new directory entered
 */
static inline FAT_ITEM* __jmp_into_dir(const FAT_ITEM* p) {
    uint16_t cluster = p->blow_cluster;
    uint16_t numOfSector = filesize2sectors(p->filesize);
    uint16_t sectorNth = HIDDEN_SECTOR + RESERVED_SECTOR + 
        NUMBER_OF_FAT * SECTOR_PER_FAT + 
        cluster * SECTOR_PER_CLUSTER + 1;
    loadLogicSector(sectorNth, DATA_BLOCK_ADDRESS, numOfSector); 
    return (FAT_ITEM*)(DATA_BLOCK_ADDRESS);
}
/** try and delete a fat item (file or directory)
 * @return error code. defined in @ref fsErrorCode.h
 * @return return @ref NO_ERR if no error
 */
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
/**
 * helper function. no need to directly call it.
 * check whether it is run-able. load EVERY-SECTOR into memory.
 * @return forever return 0 currently.
 * @see fsErrorCode.h
 */
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
/** try and load the program. 
 * search from the root directory, trying to match filename.
 * if file is found, try runing it by calling @ref __run_this_file.
 * @param targetFilename the file to load. without '.ext'. no longer
 * than 5 bytes.
 * @return errorcode.
 * @return @ref NO_ERR if no error
 * @see @ref fsErrorCode.h
 */ 
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
/** no directly run it
 */
static inline void __print_file_cluster_list(const FAT_ITEM* pfat) {
    FAT_ITEM_T* FAT_table = (FAT_ITEM_T*)(FAT_TABLE_ADDRESS);
    int16_t cluster = pfat->blow_cluster;
    FAT_ITEM_T* pFAT_ITEM = FAT_table + cluster;
    puti(cluster);
    puts(" -> ");
    while (*pFAT_ITEM != 0xFFFF) {
        puti(*pFAT_ITEM);
        puts(" -> ");
        pFAT_ITEM = FAT_table + *pFAT_ITEM;
    }
    puts("NULL");

}
#endif