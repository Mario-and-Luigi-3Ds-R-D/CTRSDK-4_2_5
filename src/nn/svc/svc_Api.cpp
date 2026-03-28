#include <nn/svc/svc_Api.h>

namespace nn{
namespace svc{
    __asm Result ControlMemory(){
        push {r0, r4}
        ldr r0, [sp, #8]
        ldr r4, [sp, #0xc]
        swi 0x1
        ldr r2, [sp]
        str r1, [r2]
        add sp, sp, #4
        pop {r4}
        bx lr
    }

    __asm void QueryMemory(){
        push    {r0, r6}
        swi     0x2
        ldr     r6,[sp,#0x0]
        str     r1,[r6,#0x0]
        str     r2,[r6,#0x4]
        str     r3,[r6,#0x8]
        str     r4,[r6,#0xc]
        ldr     r6,[sp,#0x4]
        str     r5,[r6,#0x0]
        add     sp, sp, #8
        pop     {r4,r5,r6}
    }

    __asm void ExitProcess(){
        swi     0x3
        bx      lr
    }

    __asm void CreateThread(){
        push {r0, r4}
        ldr r0, [sp, #8]
        ldr r4, [sp, #0xc]
        swi 0x8
        ldr r2, [sp]
        str r1, [r2]
        add sp, sp, #4
        pop {r4}
        bx lr
    }

    __asm void ExitThread(){
        swi 0x1
        bx  lr
    }

    __asm void SleepThread(){
        swi 0xa
        bx lr
    }

    __asm Result GetThreadPriority(){
        push {r0}
        swi 0xb
        ldr r2, [sp]
        str r1, [r2]
        add sp, sp, #4
        bx lr
    }
} // svc
}; // nn