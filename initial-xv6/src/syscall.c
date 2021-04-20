//
// Created by lvchao on 2021/4/15.
//


static int (*syscalls[])(void) = {
        [SYS_chdir]   sys_chdir,
        [SYS_close]   sys_close,
        [SYS_dup]     sys_dup,
        [SYS_exec]    sys_exec,
        [SYS_exit]    sys_exit,
        [SYS_fork]    sys_fork,
        [SYS_fstat]   sys_fstat,
        [SYS_getpid]  sys_getpid,
        [SYS_kill]    sys_kill,
        [SYS_link]    sys_link,
        [SYS_mkdir]   sys_mkdir,
        [SYS_mknod]   sys_mknod,
        [SYS_open]    sys_open,
        [SYS_pipe]    sys_pipe,
        [SYS_read]    sys_read,
        [SYS_sbrk]    sys_sbrk,
        [SYS_sleep]   sys_sleep,
        [SYS_unlink]  sys_unlink,
        [SYS_wait]    sys_wait,
        [SYS_write]   sys_write,
};

void syscall(void)
{
    int num;

    num = cp->tf->eax;
    if(num >= 0 && num < NELEM(syscalls) && syscalls[num])
        cp->tf->eax = syscalls[num]();
    else {
        cprintf("%d %s: unknown sys call %d\n",
                cp->pid, cp->name, num);
        cp->tf->eax = -1;
    }
}