#ifndef __FORK_H_
#define __FORK_H_

#define fork() \
({\
    cli();\
    int32_t __fork_ret;\
    __asm__(\
        "movl $0x02, %%eax\n"\
        "int $0x80\n"\
        : "=r"(__fork_ret)\
        :\
    );\
    sti();\
    __fork_ret;\
})

#define wait() \
({\
    cli();\
    int32_t __wait_ret;\
    __asm__(\
        "movl $0x03, %%eax\n"\
        "int $0x80\n"\
        : "=r"(__wait_ret)\
        :);\
    sti();\
    __wait_ret;\
})

#define exit() \
__asm__("movl $0x04, %%eax\n"\
    "int $0x80\n"\
    ::);

#endif