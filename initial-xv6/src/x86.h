#define uint unsigned int
#define ushort unsigned short

struct trap_frame {
    // registers as pushed by pusha
    uint edi;
    uint esi;
    uint ebp;
    uint oesp;      // useless & ignored
    uint ebx;
    uint edx;
    uint ecx;
    uint eax;

    // rest of trap frame
    ushort es;
    ushort padding1;
    ushort ds;
    ushort padding2;
    uint trap_no;

    // below here defined by x86 hardware
    uint err;
    uint eip;
    ushort cs;
    ushort padding3;
    uint eflags;

    // below here only when crossing rings, such as from user to kernel
    uint esp;
    ushort ss;
    ushort padding4;
};