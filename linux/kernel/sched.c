#include "../include/linux/sched.h"
#include "../include/asm/system.h"
#include "../include/asm/io.h"
#include "../include/linux/signal.h"
#include "../include/linux/sys.h"

#define LATCH (1193180/HZ)
#define S(nr) (1 << ((nr)-1))

int system_call(void);
int timer_interrupt(void);
long volatile jiffies = 0;
long startup_time = 0;
uint32_t last_pid = 0;
long user_stack [PAGE_SIZE >> 2];

struct {
    long* a;
    short b;
} stack_start = {&user_stack[PAGE_SIZE >> 2], 0x10};

typedef struct PCB PCB_List_T;
PCB_List_T PCB_List[NR_TASKS] = {};
int32_t current = 0;

void sched_init() {
    last_pid = 0;
    current = 0;
    int i;
    struct desc_struct* p;
    set_tss_desc(gdt + FIRST_TSS_ENTRY, &(_MY_FIRST_TSS));
    set_ldt_desc(gdt+FIRST_LDT_ENTRY, &(_MY_FIRST_LDT));
    p = gdt+2+FIRST_TSS_ENTRY;
    for (i = 1; i < NR_TASKS; ++i) {
        PCB_List[i].state = TASK_NOT_USED;
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
void sys_save(
    int32_t esp,
    int32_t gs,
    int32_t fs,
    int32_t ds,
    int32_t ss,
    int32_t es,
    int32_t edi,
    int32_t esi,
    int32_t ebp,
    int32_t _,
    int32_t ebx,
    int32_t edx,
    int32_t ecx,
    int32_t eax,
    int32_t ip,
    int32_t cs
) {
    PCB_List[current].register_image.eax = eax;
    PCB_List[current].register_image.ecx = ecx;
    PCB_List[current].register_image.edx = edx;
    PCB_List[current].register_image.ebx = ebx;
    PCB_List[current].register_image.ebp = ebp;
    PCB_List[current].register_image.esi = esi;
    PCB_List[current].register_image.edi = edi;
    PCB_List[current].register_image.es = es;
    PCB_List[current].register_image.ss = ss;
    PCB_List[current].register_image.ds = ds;
    PCB_List[current].register_image.fs = fs;
    PCB_List[current].register_image.gs = gs;
    PCB_List[current].register_image.esp = esp;
    PCB_List[current].register_image.cs = cs;
}

void sys_restart(int32_t dst_pcb) {
    int32_t dst_ss = PCB_List[dst_pcb].register_image.ss;
    int32_t dst_sp = PCB_List[dst_pcb].register_image.esp;
    __asm__(
        "movl %0, %%ss\n"
        "movl %1, %%esp\n"
        "jmpl $0x08, $return_from_sys_restart\n"
        :/* not output */
        :"r"(dst_ss), "r"(dst_sp)
    );
}
int32_t schedule() {
    while (current < NR_TASKS && PCB_List[current].state != TASK_RUNNING) {
        current++;
    }
    if (PCB_List[current].state == TASK_RUNNING) {
        return current;
    }
    current = 0;
    return current;
}