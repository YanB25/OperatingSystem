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
extern void test_second_process();
void temp_generate_second_process();
extern uint32_t tmp_STACK_end;
uint32_t last_pid = 2; //important. do not start at one.
#define ProcessStack(id) (id==0? ((uint32_t) &tmp_STACK_end) : (0x20000) + (0x400*id))
typedef struct PCB PCB_List_T;
PCB_List_T PCB_List[NR_TASKS] = {};
int32_t current = 0;
void init_first_process();

void sched_init() {
    last_pid = 2;
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
    init_first_process();
    //temp_generate_second_process(); //TODO: delete me!!
}
void init_first_process() {
    PCB_List[0].pid = 0;
    PCB_List[0].state = TASK_RUNNING;
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
    while (++current < NR_TASKS) {
        if (PCB_List[current].state != TASK_RUNNING) {
            continue;
        } else {
            return current;
        }
    }
    current = 0;
    return 0;
}

void temp_generate_second_process() {
    PCB_List[1].register_image.cs = 0x08;
    PCB_List[1].register_image.ss = 0x10;
    uint32_t p_esp = (0x20800) - 17 * 4;
    PCB_List[1].register_image.esp = p_esp;

    *((uint32_t*)p_esp) = 0x01; // trivial, will not be used
    *((uint32_t*)p_esp+1) = 0x10;
    *((uint32_t*)p_esp+2) = 0x10;
    *((uint32_t*)p_esp+3) = 0x10;
    *((uint32_t*)p_esp+4) = 0x10;
    *((uint32_t*)p_esp+5) = 0x10;
    *((uint32_t*)p_esp+14) = (uint32_t)test_second_process;
    *((uint32_t*)p_esp+15) = 0x08;
    *((uint32_t*)p_esp+16) = 0x00000206;
    PCB_List[1].state = TASK_RUNNING;
    PCB_List[1].pid = last_pid++;
}

int32_t first_empty_pcb() {
    for (int i = 0; i < NR_TASKS; ++i) {
        if (PCB_List[i].state == TASK_ZOMBIE || PCB_List[i].state == TASK_NOT_USED)
            return i;
    }
    return -1;
}
void _rev_memcpy(void*, void*, int);

void copy_process(int32_t dst_index, int32_t src_index) {
    struct RegisterImage* dst = &PCB_List[dst_index].register_image;
    struct RegisterImage* src = &PCB_List[src_index].register_image; 
    int32_t new_pid = last_pid++;

    //TODO: take care of pid
    dst->eax = new_pid;
    src->eax = 1;
    dst->ecx = src->ecx;
    dst->edx = src->edx;
    dst->ebx = src->ebx;
    dst->esi = src->esi;
    dst->edi = src->edi;
    dst->es = src->es;
    dst->ss = src->ss;
    dst->ds = src->ds;
    dst->fs = src->fs;
    dst->gs = src->gs;
    dst->cs = src->cs;

    int32_t esp_offset = ProcessStack(src_index) - src->esp;
    int32_t ebp_offset = ProcessStack(src_index) - src->ebp;
    _rev_memcpy((void*)ProcessStack(dst_index), (void*)ProcessStack(src_index), 1024);
    dst->esp = ProcessStack(dst_index) - esp_offset;
    dst->ebp = ProcessStack(dst_index) - ebp_offset;

    uint32_t* pesp = (uint32_t*)dst->esp;
    *(pesp + OFFSET_EBP) = dst->ebp;
    *(pesp + OFFSET_EAX) = dst->eax;

    PCB_List[dst_index].state = TASK_RUNNING;
    PCB_List[dst_index].pid = new_pid;
}

void _rev_memcpy(void* dst, void* src, int size) {
    for (int i = 0; i < size; ++i) {
        ((char*)dst)[-i-1] = ((char*)src)[-i-1];
    }
}