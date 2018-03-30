#include "kernel.h"
#include "../include/utilities.h"
#include "../user/user.h"
#include "../user/terminal.h"
#include "../include/mystring.h"
#include "../filesystem/API/fsapi.h"
#define true 1
#define false 0
int main() {
    clear_screen();
    FAT_ITEM* pfat = __get_root_dir();
    while (__fs_strcmp(pfat->filename, "stone") != 0) {
        putln(pfat->filename);
        pfat = __next_item(pfat);
        if (__fs_strcmp(pfat->filename, "msg") == 0) {
            putln("find msg");
            puti(pfat->blow_cluster);
            putln("finish");
        }
    }
    putln(pfat->filename);
    puti(pfat->blow_cluster);
    int16_t ret = __run_this_file(pfat);
    putiln(ret);

    draw_str("enter help to get help", 0, 30);
    putln("");

    terminal();
    return 0;
}