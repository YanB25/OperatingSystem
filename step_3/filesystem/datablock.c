#include <stdint.h>
#include "FATMacro.h"
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