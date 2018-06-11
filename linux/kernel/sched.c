#include "../include/linux/sched.h"
#include "../include/asm/system.h"
#include "../include/asm/io.h"
#include "../include/linux/signal.h"
#include "../include/linux/sys.h"

#define LATCH (1193180/HZ)
#define S(nr) (1 << ((nr)-1))

int system_call(void);
int timer_interrupt(void);
union task_union {
    struct task_struct task;
    char stack[PAGE_SIZE];
};
static union task_union init_task = {INIT_TASK};
long volatile jiffies = 0;
long startup_time = 0;

struct task_struct* current = &(init_task.task);
struct task_struct* last_task_used_math = NULL;
struct task_struct* task[NR_TASKS] = {&(init_task.task), };

long user_stack [PAGE_SIZE >> 2];

struct {
    long* a;
    short b;
} stack_start = {&user_stack[PAGE_SIZE >> 2], 0x10};

void schedule() {
    int next = 0;
    while (1) {
        int c = -1;
        int i = NR_TASKS;
        struct task_struct **p;
        p = &task[NR_TASKS];
        while (--i) {
            if (!*--p)
                continue;
            if ((*p)->state == TASK_RUNNING && (*p)->counter > c) {
                c = (*p)->counter;
                next = i;
            }
        }
        if (c)
            break;
        for (p = &LAST_TASK; p > &FIRST_TASK; --p) {
            if (*p) {
                (*p)->counter = ((*p)->counter >> 1) + (*p)->priority;
            }
        }
    }
    switch_to(next); 
    int magic_number = 0x12345678;//TODO: delete me, magic number for following control flows
}
void do_timer(long cpl) {
    if (cpl) {
        current->utime++;
    } else {
        current->stime++;
    }
    if (--(current->counter) > 0) return;
    current->counter = 0;
    if (!cpl) return;
    schedule(); //NOTICE:important
}

void sched_init() {
    int i;
    struct desc_struct* p;
    set_tss_desc(gdt + FIRST_TSS_ENTRY, &(_MY_FIRST_TSS));
    set_ldt_desc(gdt+FIRST_LDT_ENTRY, &(_MY_FIRST_LDT));
    p = gdt+2+FIRST_TSS_ENTRY;
    for (i = 1; i < NR_TASKS; ++i) {
        task[i] = NULL;
        p->a = p->b = 0;
        p++;
        p->a = p->b = 0;
        p++;
    }
    __asm__(
        "pushfl\n"
        "andl $0xffffbfff, (%esp)\n"
        "popfl"
    );
    ltr(0);
    lldt(0);
    
    outb_p(0x36, 0x43);
    outb_p(LATCH & 0xff, 0x40);
    outb_p(LATCH >> 8, 0x40);
    set_intr_gate(0x20, &timer_interrupt);
    outb(inb_p(0x21)&~0x01, 0x21);
    set_system_gate(0x80, &system_call);
}