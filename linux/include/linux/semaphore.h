#ifndef __SEMAPHORE_H_
#define __SEMAPHORE_H_
#define NR_SEMAPHORE 256
#include "../asm/system.h"
#include "../linux/sched.h"
typedef struct Semaphone {
    int value;
    int block_processes[NR_TASKS];
    int bsize;
    int used;
} Semaphone;
int getsem(int );
int freesem(int );
int p(int );
int v(int );
#endif