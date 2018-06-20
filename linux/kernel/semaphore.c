#include "../include/linux/sched.h"
#include "../include/linux/fork.h"
#include "../include/asm/system.h"
#include "../include/linux/semaphore.h"
extern int current;
typedef struct PCB PCB_List_T;
extern PCB_List_T PCB_List[NR_TASKS];
int printks(const char*);

Semaphone semaphone_list[NR_SEMAPHORE];

void init_semaphore() {
    for (int i = 0; i < NR_SEMAPHORE; ++i) {
        semaphone_list[i].bsize = 0;
        semaphone_list[i].used = 0; // false
    }
}

int getsem(int value) {
    // for (int i = 0; i < NR_SEMAPHORE; ++i) {
    //     if(semaphone_list[i].used == 0) {
    //         semaphone_list[i].used = 1;
    //         semaphone_list[i].value = value;
    //         semaphone_list[i].bsize = 0;
    //         return i;
    //     }
    // }
    // return -1;
    int ret;
    __asm__(
        "movl $0x05, %%eax\n"
        "int $0x80\n"
        :"=r"(ret)
        :"b"(value)
    );
    return ret;
}

int freesem(int id) {
    //TODO: should be refine
    int ret;
    __asm__(
        "movl $0x06, %%eax\n"
        "int $0x80\n"
        :"=r"(ret)
        :"b"(id)
    );
    return ret;
}
void puti(int number) {
    char buffer[20];
    int length = 0;
    int num = number < 0 ? -number : number;
    while (num) {
        buffer[length++] = (num % 10) + '0';
        num /= 10;
    }
    buffer[length] = 0;
    int i = 0;
    int j = length - 1;
    while (i < j) {
        int tmp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = tmp;
        i++;
        j--;
    }
    if (number <0) {
        printks("-");
    }
    printks(buffer);
    if (number == 0) {
        printks("0");
    }
}
int p(int id) {
    int ret;
    __asm__(
        "movl $0x07, %%eax\n"
        "int $0x80\n"
        :"=r"(ret)
        :"b"(id)
    );
    return ret;
}

int v(int id) {
    int ret;
    __asm__(
        "movl $0x08, %%eax\n"
        "int $0x80\n"
        :"=r"(ret)
        :"b"(id)
    );
    return ret;
}