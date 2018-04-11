#include "../include/utilities.h"
#include "../include/mystring.h"
#include "../filesystem/API/fsapi.h"

#define BACK_SPACE 8
#define BUFFER_SIZE 64
#define PROMT "yb@yb-thinkpad-e450:~$ "
#define HELP_MSG "run <program> : run program <program>\n\r" \
    "run stoneQ: run program stoneQ.bin\n\r" \
    "ls : list all file in root directory"
#define LOW_8_MASK (0b11111111)
#define GET_LOW_8BITS(X) (X & LOW_8_MASK)
#define GET_HIGH_8BITS(X) (X >> 8)
#include "../include/stdio.h"
extern void kb_interupt_install();
extern void kb_interupt_uninstall();
char CMD_BUFFER[BUFFER_SIZE + 10] = {};
void parseCMD(int );

static FAT_ITEM* CUR_DIR = 0;
void resetTerminal();
int terminal() {
    if (CUR_DIR == 0) {
        CUR_DIR = __get_root_dir();
    }
    puts(PROMT);
    int offsetx = 0;
    int offsety = 0;
    int CMDindex = 0;

    while(1) {
        int try = kbhit();
        if (!try) continue;

        int key = readkb();
        switch(key) {
            case('\r'):
                putch('\n');
                putch('\r');

                offsetx = 0;
                offsety++;

                parseCMD(CMDindex);
                puts(PROMT);

                CMDindex = 0;
                CMD_BUFFER[CMDindex] = 0;

            break;
            case(BACK_SPACE):
                if (offsetx > 0) {
                    putch(8);
                    putch(' ');
                    putch(8);
                    offsetx--;

                    CMDindex--;
                    CMD_BUFFER[CMDindex] = 0;
                }
            break;
            case('\t'):
            break;
            default:
                putch(key);
                offsetx++;
                CMD_BUFFER[CMDindex++] = key;
                CMD_BUFFER[CMDindex] = 0;
        }
    }
    return 0;
}

void parseCMD(int CMDindex) {
    if (CMDindex == 0) return;
    if (strstr(CMD_BUFFER, "run") == 0 && strchr(CMD_BUFFER, ' ') == 3) {
        int16_t pos = strchr(CMD_BUFFER, ' ');
        const char* fn = CMD_BUFFER + pos + 1;
        int16_t code = __load_program(fn);
        int (*userProgram)() = (int (*)())(0x6c00);
        switch(code) {
            case ERR_SYS_PROTC:
                putln("ERROR: system protect file");
                break;
            case ERR_TYPE_FLDR:
                putln("ERROR: folder not executable");
                break;
            case ERR_TYPE_DOC:
                putln("ERROR: partition info protect");
                break;
            case ERR_NOT_FOUND:
                putln("ERROR: file not found");
                break;
            case NO_ERR:
                kb_interupt_install();
                userProgram();
                kb_interupt_uninstall();
                resetTerminal();
                break;
        }
    } else if (strcmp(CMD_BUFFER, "help") == 0) {
        putln(HELP_MSG);
    } else if (strcmp(CMD_BUFFER, "ls") == 0) {
        printf("%10s|%20s|%10s\n", "filename", "filesize(bytes)", "begin cluster");
        FAT_ITEM* pfat = CUR_DIR;
        if (__FAT_showable_item(pfat)) {
            printf("%10s|%20d|%10d\n", pfat->filename, pfat->filesize, pfat->blow_cluster);
            // __print_file_cluster_list(pfat);
            newline();
        }
        while (__has_next_item(pfat)) {
            pfat = __next_item(pfat);
            if (__FAT_showable_item(pfat)) {
                printf("%10s|%20d|%10d\n", pfat->filename, pfat->filesize, pfat->blow_cluster);
                // __print_file_cluster_list(pfat);
                newline();
                // putiln(pfat->blow_cluster);
                // putiln(pfat->filesize);
            }
        }
    }
    else if (strcmp(CMD_BUFFER, "gc") == 0) {
        uint16_t cursor_position = get_cursor();
        uint16_t col = GET_LOW_8BITS(cursor_position);
        uint16_t row = GET_HIGH_8BITS(cursor_position);
        printf("cursor row is %d, col is %d\n", row, col);
    }
    else if (strcmp(CMD_BUFFER, "scu") == 0) {
        uint16_t ocursor_position = get_cursor();
        uint16_t ocol = GET_LOW_8BITS(ocursor_position);
        uint16_t orow = GET_HIGH_8BITS(ocursor_position);
        __screen_scroll(0, (24 << 8) + 79, 1, 0);
        uint16_t ncursor_position = get_cursor();
        uint16_t ncol = GET_LOW_8BITS(ncursor_position);
        uint16_t nrow = GET_HIGH_8BITS(ncursor_position);
        printf("old row %d col %d, new row %d col %d\n", orow, ocol, nrow, ncol);
    }
    else {
        puts("ybsh: command not found: ");
        putln(CMD_BUFFER);
    }
}
void resetTerminal() {
    clear_screen();
    set_cursor(1, 1);
}