LD=ld 
LDFLAGS=-melf_i386 -N
CC=gcc
CCFLAGS=-m32 -mpreferred-stack-boundary=2 -ffreestanding
#TODO: in pm, here should be -m32 not -m16
#TODO: delete -march=i386
AS=nasm
ASFLAGS=

all: asm.o traps.o printk.o printk_tmp.o system_call.o sched.o
asm.o: asm.s 
	$(AS) $(ASFLAGS) -f elf -o $@ $^
traps.o: traps.c
	$(CC) $(CCFLAGS) -c $^
fork.o: fork.c
	$(CC) $(CCFLAGS) -c $^
# sched.o: sched.c
# 	$(CC) $(CCFLAGS) -c $^
sched.o: sched.c ../include/linux/sys.h
	gcc -m32 -fno-builtin -fno-stack-protector -fomit-frame-pointer -fstrength-reduce  -I../include -c -o sched.o sched.c

printk.o: printk.c
	$(CC) $(CCFLAGS) -c $^
printk_tmp.o: printk.s #TODO: only as workaround. delete me.
	$(AS) $(ASFLAGS) -f elf -o $@ $^
system_call.o: system_call.s
	$(AS) $(ASFLAGS) -f elf -o $@ $^