#ifndef __SIGNAL_H_
#define __SIGNAL_H_
typedef unsigned int sigset_t;
struct sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};
#endif