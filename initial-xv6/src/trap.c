
void tvinit(void) {
    int i;

    for (i = 0; i < 256; i++)
        SETGATE(idt[i], 0, SEG_KCODE << 3, vectors[i], 0);

    // this is the line we care about...
    SETGATE(idt[T_SYSCALL], 1, SEG_KCODE << 3, vectors[T_SYSCALL], DPL_USER);

    initlock(&tickslock, "time");
}

void trap(struct trapframe *tf) {
    if (tf->trapno == T_SYSCALL) {
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