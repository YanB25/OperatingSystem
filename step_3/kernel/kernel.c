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
    FAT_ITEM* root = __get_root_dir();
    if (__FAT_item_type(root) != TYPE_DOC) {
        putln(root->filename);
    }
    while (__has_next_item(root)) {
        int16_t ret = __rm_this_file(root);
        putiln(ret);
        root = __next_item(root);
        if (__FAT_item_type(root) != TYPE_DOC) {
            puts(root->filename);
        }
        if (__FAT_item_type(root) == TYPE_FLDR) {
            putln("/");
        } else if (__FAT_item_type(root) == TYPE_FILE) {
            puts(".");
            putn(root->extendname, 3);
            putln("");
        } else {
            putln("");
        }
    }
    int16_t ret = __rm_this_file(root);
    putiln(ret);

    root = __get_root_dir();
    if (__FAT_item_type(root) != TYPE_DOC) {
        putln(root->filename);
    }
    while (__has_next_item(root)) {
        int16_t ret = __rm_this_file(root);
        putiln(ret);
        root = __next_item(root);
        if (__FAT_item_type(root) != TYPE_DOC) {
            puts(root->filename);
        }
        if (__FAT_item_type(root) == TYPE_FLDR) {
            putln("/");
        } else if (__FAT_item_type(root) == TYPE_FILE) {
            puts(".");
            putn(root->extendname, 3);
            putln("");
        } else {
            putln("");
        }
    }
    draw_str("enter help to get help", 0, 30);
    putln("");
    terminal();
    return 0;
}