#include <stdint.h>
#include "FATMacro.h"

FAT_ITEM media_type = {
    "__media_","res",
    FAT_doc,
    0,0,0,0,0,0,0,0,0,0
};
FAT_ITEM error_flags = {
    "__error_","res",
    FAT_doc
    ,0,0,0,0,0,0,0,0,0,0
};
FAT_ITEM kernel_bin= {
    "kernel",
    "bin",
    FAT_rw | FAT_sys,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    4,
    512*24 // 8 sectors
};

FAT_ITEM home_dir= {
    "home",
    "",
    FAT_rw | FAT_fldr,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    12,
    512
};

FAT_ITEM dot = {
    ".",
    "",
    FAT_fldr
    , 0, 0, 0, 0, 0, 0,
    0, 
    0, 
    2, 
    512
};
FAT_ITEM dotdot = {
    "..",
    "",
    FAT_fldr
    , 0, 0, 0, 0, 0, 0, 
    0, 
    0,
    2, 
    512
};
FAT_ITEM msg = {
    "\xE5sg",
    "txt",
    FAT_rw,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    13,
    0
};
FAT_ITEM user_programQ = {
    "stoneQ",
    "bin",
    FAT_rw,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    14,
    512*4 // 4 sectors
};

FAT_ITEM user_programW = {
    "stoneW",
    "bin",
    FAT_rw,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    18,
    512*4 // 4 sectors
};
FAT_ITEM user_programA = {
    "stoneA",
    "bin",
    FAT_rw,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    22,
    512*4 // 4 sectors
};
FAT_ITEM user_programS = {
    "stoneS",
    "bin",
    FAT_rw,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    26,
    512*4 // 4 sectors
};