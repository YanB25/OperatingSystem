#ifndef __SCHED_H_
#define __SCHED_H_
#define NR_TASKS 64
#define HZ 100

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

#include "head.h"
#include "fs.h"
#include "signal.h"
#include "mm.h"

#define int32_t long
#define uint32_t unsigned long

#define TASK_RUNNING  0// running or ready
#define TASK_INTERRUPTIBLE 1// wait and interruptible
#define TASK_UNINTERRUPTIBLE 2// ;wait and no interruptible
#define TASK_ZOMBIE 3
#define TASK_STOPPED 4

#ifndef NULL
#define NULL ((void*)0)
#endif

extern void sched_init();
extern void schedule();
extern void trap_init();
extern void panic(const char*);
typedef int (*fn_ptr)();

struct i387_struct {
    long cwd;
    long swd;
    long twd;
    long fip;
    long fcs;
    long foo;
    long fos;
    long st_space[20];
};
struct tss_struct {
    int32_t back_link;
    int32_t esp0;
    int32_t ss0;
    int32_t esp1;
    int32_t ss1;
    int32_t esp2;
    int32_t ss2;
    int32_t cr3;
    int32_t eip;
    int32_t eflags;
    int32_t eax, ecx, edx, ebx;
    int32_t esp;
    int32_t ebp;
    int32_t esi;
    int32_t edi;
    int32_t es;
    int32_t cs;
    int32_t ss;
    int32_t ds;
    int32_t fs;
    int32_t gs;
    int32_t ldt;
    int32_t trace_bitmap;
    struct i387_struct i387;
};
struct task_struct {
    int32_t state;
    int32_t counter;
    int32_t priority;
    int32_t signal;
    struct sigaction sigaction[32];//TODO: not imple
    int32_t blocked;
/* various fields */
    int exit_code;
    uint32_t start_code, end_code, end_data, brk, start_stack;
    int32_t pid, father, pgrp, session, leader;
    unsigned short uid, euid, suid;
    unsigned short gid, egid, sgid;
    int32_t alarm;
    int32_t utime, stime, cutime, sctime, start_time;
    unsigned short used_math;
/* file system info */
    int tty;
    unsigned short umask;
    struct m_inode* pwd;
    struct m_inode* root;
    struct m_inode* executable;
    unsigned long close_on_exec;
    struct file* filp[NR_OPEN];
    struct desc_struct ldt[3];
    struct tss_struct tss;
};
#define INIT_TASK \
{ 0, 15, 15, \
    0, {{}, }, 0, \
    0, 0, 0, 0, 0, 0,\
    0, -1, 0, 0, 0,\
    0, 0, 0, 0, 0, 0,\
    0, 0, 0, 0, 0, 0,\
    0,\
    -1, 0022, NULL, NULL, NULL, 0,\
    {NULL, }, \
\
    {\
        {0, 0},\
        {0x9f, 0xc0fa00},/*code length 640k, base 0, G=1, D=1, DPL=3, P=1, type=0x0a */ \
        {0x9f, 0xc0f200},/*640k base 0, G=1, D=1, DPL=3, P=1, type=0x02  */\
    },\
    {0, PAGE_SIZE + (long)&init_task, 0x10, 0, 0, 0, 0, (long)&pg_dir,\
        0, 0, 0, 0, 0, 0, 0, 0,\
        0, 0, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,/*ds~gs 0x17*/ \
        _LDT(0), 0x80000000, \
        {}\
    },\
}

extern struct task_struct* task[NR_TASKS];
extern struct task_struct* last_task_used_math;
extern struct task_struct* current;
extern long volatile jiffies;
extern long startup_time; // boot time

#define FIRST_TSS_ENTRY 6 //TODO: warning, is it correct?
#define FIRST_LDT_ENTRY (FIRST_TSS_ENTRY + 1)
#define _TSS(n) ((((unsigned long) n) << 4) + (FIRST_TSS_ENTRY << 3))
#define _LDT(n) ((((unsigned long) n) << 4) + (FIRST_LDT_ENTRY << 3))
#define ltr(n) __asm__("ltr %%ax"::"a"(_TSS(n)))
#define lldt(n) __asm__("lldt %%ax"::"a"(_LDT(n)))
#define switch_to(n) {\
    struct {long a,b; } __tmp;\
    __asm__(\
        "cmpl %%ecx, current\n"\
        "je 1f\n"\
        "movw %%dx, %1\n"\
        "xchgl %%ecx, current\n"\
        "ljmp %0\n"\
        "1:\n"\
        /* TODO: I let out some code here */ \
        ::"m"(*&__tmp.a), "m"(*&__tmp.b), \
        "d"(_TSS(n)), "c"((long) task[n]));\
}
#endif