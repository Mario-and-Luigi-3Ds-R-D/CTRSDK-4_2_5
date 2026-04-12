#include <nn/svc/svc_Api.h>

/*

CTRSDK-4_2_5/src/nn/svc_Api.cpp

This is used for memory control concerning software interrtuption. Written in ASM.

*/

namespace nn{
namespace svc{
    // ControlMemory
    __asm Result ControlMemory(uint*,uint,uint,uint,uint,uint){
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

    // QueryMemory
    __asm void QueryMemory(nn::os::MemoryInfo*,nn::os::PageInfo*,uint){
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

    // ExitProcess
    __asm void ExitProcess(){
        swi     0x3
        bx      lr
    }

    // CreateThread
    __asm void CreateThread(nn::Handle*, void*, uint, uint,uint,int,int){
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

    // ExitThread
    __asm void ExitThread(){
        swi 0x9
        bx  lr
    }

    // SleepThread
    __asm void SleepThread(long long){
        swi 0xa
        bx lr
    }

    // GetThreadPriority - look for priority of a Thread #
    __asm Result GetThreadPriority(){
        push {r0}
        swi 0xb
        ldr r2, [sp]
        str r1, [r2]
        add sp, sp, #4
        bx lr
    }

    // CreateMutex
    __asm Result CreateMutex(nn::Handle*,bool){
        push {r0}
        swi 0x13
        ldr r2,[sp,#4]
        str r1,[r2]
        add sp, sp, #4
        bx lr
    }

    // CreateEvent - Create / Load New Memory event
    __asm Result CreateEvent(nn::Handle*,nn::os::ResetType){
        push {r0}
        swi 0x17
        ldr r2,[sp,#4]
        str r1,[r2]
        add sp, sp, #4
        bx lr
    }

    // CreateAddressArb. Create New Arb Address for Memory
    __asm s32 CreateAddressArbiter(nn::Handle*){
        str r0,[sp,#4]!
        swi 0x21
        ldr r2,[sp,#0]
        str r1,[r2,#0]
        add sp,sp,#0x4
        bx lr
    }

    // ArbitrateAddress - Arb New Addr
    __asm void ArbitrateAddress(nn::Handle,uint,nn::os::ArbitrationType,int,long long){
        push {r4,r5}
        ldr r4,[sp,#0]
        ldr r5,[sp,#4]
        swi 0x22
        pop {r4,r5}
        bx lr
    }

    // Break - like nn::dbg::Break but swi
    __asm Result Break(nn::dbg::BreakReason,const void*,int){
        swi 0x3c
        bx lr
    }

    // CloseHandle
    __asm void CloseHandle(nn::Handle){
        swi 0x23
        bx lr
    }

    // ConnectToPort
    __asm void ConnectToPort(nn::Handle*, const char*){
        str r0,[sp,#4]
        swi 0x2d
        ldr r2,[sp,#0]
        str r1,[r2,#0]
        add sp, sp, #4
        bx lr
    }

    // DuplicateHandle - dupes handle.
    __asm void DuplicateHandle(nn::Handle*){
        str r0,[sp,#4]
        swi 0x27
        ldr r2,[sp,#0]
        str r1,[r2,#0]
        add sp,sp,#4
        bx lr
    }

    // GetProcessId
    __asm void GetProcessId(uint*, nn::Handle){
        str r0,[sp,#4]
        swi 0x35
        ldr r2,[sp,#0]
        str r1,[r2,#0]
        add sp,sp,#4
        bx lr
    }

    // GetResourceLimit - Fetches limit
    __asm void GetResourceLimit(nn::Handle*){
        str r0,[sp,#4]
        swi 0x38
        ldr r2,[sp,#0]
        str r1,[r2,#0]
        add sp,sp,#4
        bx lr
    }

    // GetSystemTick - Gets current Tisk
    __asm void GetSystemTick(){
        swi 0x28
        bx lr
    }

    // GetThreadId
    __asm void GetThreadId(uint*,nn::Handle){
        str r0,[sp,#4]
        swi 0x37
        ldr r2,[sp,#0]
        str r1,[r2,#0]
        add sp,sp,#4
        bx lr
    }

    // WaitSynchronizationN - Waits for Sync.
    __asm Result WaitSynchronizationN(int*, const nn::Handle*, int,bool,long long){
        push {r0,r4}
        ldr r0,[sp,#0]
        ldr r4,[sp,#4]
        swi 0x25
        ldr r2,[sp,#0]
        str r1,[r2,#0]
        add sp,sp,#4
        ldr r4,[sp],#4
        bx lr
    }
} // svc
}; // nn