#include "x86.h"
#include "mmu.h"

struct gate_desc idt[256];
extern uint vectors[];
struct spinlock tickslock;
uint ticks;

void tv_init(void) {
    int i;

    for (i = 0; i < 256; i++) {
        SETGATE(idt[i], 0, SEG_KCODE << 3, vectors[i], 0);
    }

    // this is the line we care about...
    SETGATE(idt[T_SYSCALL], 1, SEG_KCODE << 3, vectors[T_SYSCALL], DPL_USER);

    initlock(&tickslock, "time");
}

void idt_init(void) {
    lidt(idt, sizeof(idt));
}


void trap(struct trap_frame *tf) {
    if (tf->trap_no == T_SYSCALL) {
        if (cp->killed)
            exit();
        cp->tf = tf;
        syscall();
        if (cp->killed)
            exit();
        return;
    }
    // continues
}