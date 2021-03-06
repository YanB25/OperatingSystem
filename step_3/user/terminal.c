//TODO: CRITICAL IMPORTANT. no enough space. plz extend!
/**
 * @file
 * @brief
 * terminal.
 * 
 * parce user command.
 * load files into memory.
 * run files.
 * do whatever and never really returned
 */
__asm__(
    ".intel_syntax noprefix\n"
    "mov ax, cs\n"
    "mov ds, ax\n"
    "mov es, ax\n"
    "jmp terminal\n"
    ".att_syntax\n"
);
#include "../include/utilities.h"
#include "../include/mystring.h"
#include "../filesystem/API/fsapi.h"
#include "../kernel/PCB.h"
#include "../include/kmm.h"

#define BACK_SPACE 8 ///< '\b' ascii
#define BUFFER_SIZE 64 ///< buffer size for parcing command
#define PROMT "yb@yb-thinkpad-e450:~$ "
#define HELP_MSG "  run <program> : run program <program>\n\r" \
    "  \t e.g. run stoneQ: run program stoneQ.bin\n\r" \
    "  ls : list all file in root directory\n\r"\
    "  showinfo: print my id 16337269 in 3-D mod\n\r"\
    "  pc: print process information\n\r" \
    "  clear: clear screen \n\r"\
    "  kill <pid>: kill a process by its pid"
#define LOW_8_MASK (0b11111111)
#define GET_LOW_8BITS(X) (X & LOW_8_MASK)
#define GET_HIGH_8BITS(X) (X >> 8)
#include "../include/stdio.h"
#include "../include/graphic.h"
#define TERMINAL_STYLE (TO_FN(G_PINKISH))
//TODO: disable install and uninstall interupt
// extern void kb_interupt_install();
// extern void kb_interupt_uninstall();
char CMD_BUFFER[BUFFER_SIZE + 10] = {};
void parseCMD(int );
static FAT_ITEM* CUR_DIR = 0; ///< current directory pointer
void resetTerminal(); 
int terminal() {
    //TODO: delete me

    CUR_DIR = __get_root_dir();

    puts_style(PROMT, TERMINAL_STYLE);
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
                puts_style(PROMT, TERMINAL_STYLE);

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
    char fn[10];
    int32_t kpid;
    if (sscanf(CMD_BUFFER, "run %s", fn) == 1) {
        int16_t pos = strchr(CMD_BUFFER, ' ');
        const char* fn = CMD_BUFFER + pos + 1;
        int32_t pid = -1;
        //TODO: need to be changed here
        // it is badly designed, file location is determined by filename
        // after finish auto load and memory allocation
        // here should change
        //TODO: remember to change makefile ld accordingly
        //      uint32_t segment = 0;
        //      if (fn[5] == 'Q') segment = 0x1000 ;
        //      else if (fn[5] == 'W') segment = 0x1100;
        //      else if (fn[5] == 'A') segment = 0x1200;
        //      else segment = 0x1300;
        uint32_t address = mm_malloc(0x800);

        int16_t code = __load_program(fn, (address >> 4) << 16);
        switch(code) {
            case ERR_SYS_PROTC:
                putln("ERROR: system protect file");
                mm_free(address, 0x800);
                break;
            case ERR_TYPE_FLDR:
                putln("ERROR: folder not executable");
                mm_free(address, 0x800);
                break;
            case ERR_TYPE_DOC:
                putln("ERROR: partition info protect");
                mm_free(address, 0x800);
                break;
            case ERR_NOT_FOUND:
                putln("ERROR: file not found");
                mm_free(address, 0x800);
                break;
            case NO_ERR:
                //TODO: disable install and uninstall interupt
                //kb_interupt_install();
                // __asm__ volatile (
                //     "calll $0x06C0, $0"
                // );
                //    userProgram();
                // kb_interupt_uninstall();
                //    resetTerminal();


                pid = add_new_process(address);
                printf("new process created. pid is %x\n", pid);
                printf("new program at memory %d\n", address);
                break;
        }
    } else if (strcmp(CMD_BUFFER, "help") == 0) {
        putln(HELP_MSG);
    } 
    else if (sscanf(CMD_BUFFER, "kill %d", &kpid) == 1) {
        int8_t errno = kill_process(kpid);
        if (errno == 1) {
            printf("ERROR: no this pid %d\n", kpid);
        }
    } else if (strcmp(CMD_BUFFER, "test") == 0) {
        putln("test command catch");
        __load_program("stoneQ", 0x1000 << 16);
        int32_t pid = add_new_process(0x10000);
        printf("new process created. pid is %d\n", pid);
    } else if (strcmp(CMD_BUFFER, "pc") == 0) {
        printf("there are currently %d process running\n", get_process_num());
        __print_process_info();
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
    else if (strcmp(CMD_BUFFER, "clear") == 0) {
        resetTerminal();
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
    } else if (strcmp(CMD_BUFFER, "showinfo") == 0) {
        __asm__ volatile(
            "pushw %%ax\n"
            "movb $2, %%ah\n"
            "int $0x2B\n"
            "popw %%ax\n"
            : /* no output */
            : /* no input */
            : "cc"
        );
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