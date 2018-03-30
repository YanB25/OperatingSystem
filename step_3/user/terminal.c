#include "../include/utilities.h"
#include "../include/mystring.h"
#include "stone.h"
#include "../filesystem/API/fsapi.h"

#define BACK_SPACE 8
#define BUFFER_SIZE 64
#define PROMT "yb@yb-thinkpad-e450:~$ "
#define HELP_MSG "run q : run program q\n\r" \
    "ls : list all file in root directory"
char CMD_BUFFER[BUFFER_SIZE + 10] = {};
void parseCMD(int );

int terminal() {
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
    if (strstr(CMD_BUFFER, "run") == 0) {
        int16_t pos = strchr(CMD_BUFFER, ' ');
        const char* fn = CMD_BUFFER + pos + 1;
        int16_t code = __load_program(fn);
        putiln(code);
        if (code == 0) {
            int (*userProgram)() = (int (*)())(0x6c00);
            userProgram();
            clear_screen();
        } else {
            putln("error occur");
        }
    } else if (strcmp(CMD_BUFFER, "help") == 0) {
        putln(HELP_MSG);
    }
    else {
        puts("ybsh: command not found: ");
        putln(CMD_BUFFER);
        // putln(HELP_MSG);
    }
}