#include "x86.h"

int mainc(void) {
    tvinit();// trap vectors initialized here
}

static void
mpmain(void) {
    idtinit();
}

void
idtinit(void) {
    lidt(idt, sizeof(idt));
}

static inline void
lidt(struct gatedesc *p, int size) {
    volatile ushort pd[3];

    pd[0] = size - 1;
    pd[1] = (uint) p;
    pd[2] = (uint) p >> 16;

    asm volatile("lidt (%0)" : : "r" (pd));
}

