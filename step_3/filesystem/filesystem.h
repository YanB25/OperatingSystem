#ifndef __FILE_SYSTEM_H_
#define __FILE_SYSTEM_H_

// WARNING: should be the same with DBR.asm
#define BYTE_PER_SECTOR (512)
#define SECTOR_PER_CLUSTER (1)
#define RESERVED_SECTOR (2)
#define NUMBER_OF_FAT (2)
#define ROOT_ENTRIES (512)
#define SECTOR_PER_FAT (4)
#define SECTOR_PER_TRACK (36)
#define NUMBER_OF_HEAD (2)
#define HIDDEN_SECTOR (1)


#define BPB_ADDRESS (0x7E0B)
#define FAT_TABLE_ADDRESS (0x8200)
#define ROOT_AREA_ADDRESS (0x8600)
#define KERNEL_ADDRESS 0xA100

#define _TO_STRING(X) #X
#define TO_STRING(X) _TO_STRING(X)

#endif