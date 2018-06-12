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


#endif