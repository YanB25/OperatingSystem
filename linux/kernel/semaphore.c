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
    semaphone_list[id].used = 0;
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
void p(int id) {
    cli(); //TODO: maybe bug
    // printks("p ");
    // puti(id);
    // printks(" ");
    //puti(semaphone_list[id].value);
    semaphone_list[id].value--;
    //puti(semaphone_list[id].value);
    // puti(semaphone_list[id].value);
    // printks("\n");
    if (semaphone_list[id].value < 0) {
        int size = semaphone_list[id].bsize;
        semaphone_list[id].block_processes[size] = current;
        semaphone_list[id].bsize++;
        // printks(" !!!wait!! \n");
        wait(); //TODO: sti??
    }
    sti();
}

void v(int id) {
    cli();
    // printks("v ");
    // puti(id);
    // printks(" ");
    // printks("v, id is ");
    // puti(id);
    // printks("\n");
    // printks("v operation\n");
    semaphone_list[id].value++;
    //puti(semaphone_list[id].value);
    int val = semaphone_list[id].value;
    // printks("after is  ");
    // puti(val);
    // printks("\n");
    if (semaphone_list[id].value <= 0) {
        semaphone_list[id].bsize--;
        int size = semaphone_list[id].bsize;
        int block_processes_id = semaphone_list[id].block_processes[size];
        // printks("wake up id is ");
        // puti(block_processes_id);
        PCB_List[block_processes_id].state = TASK_INTERRUPTIBLE;
        // printks("   ");
        // printks(" v-work ");
    }
    // puti(semaphone_list[id].value);
    // printks("\n");
    sti();
}