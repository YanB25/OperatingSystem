#include <stdint.h>
#include "FATMacro.h"
struct FAT_ITEM {
    char filename[8];
    char extendname[3];
    uint8_t mod;
    
    uint8_t res; //reserved
    uint8_t created_time; // ms
    uint16_t hms; // hour minute second
    uint16_t ymd; // year month day
    uint16_t recent_access_ymd;
    uint16_t bhigh_cluster;

    uint16_t modify_hms;
    uint16_t modify_ymd;
    uint16_t blow_cluster;
    uint32_t filesize; // in bytes
}__attribute__((packed));
typedef struct FAT_ITEM FAT_ITEM;

FAT_ITEM media_type = {
    "__media_","res",0,0,0,0,0,0,0,0,0,0,0
};
FAT_ITEM error_flags = {
    "__error_","res",0,0,0,0,0,0,0,0,0,0,0
};
FAT_ITEM kernel_bin= {
    "kernel",
    "bin",
    FAT_rw || FAT_sys,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    3,
    1024
};

FAT_ITEM home_dir= {
    "home",
    "",
    FAT_rw || FAT_fldr,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    5,
    512
};