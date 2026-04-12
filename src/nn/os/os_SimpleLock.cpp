/* Simple Lock */

/*
FileName: nn/os/os_SimpleLock.cpp

You will not need to use this, the SDK will branch to these for you. Such as CriticalSection and LightEvent*/

#include <nn/os/os_SimpleLock.h>
#include <nn/svc/svc_Api.h>

namespace nn{
namespace os{

__asm void SimpleLock::Initialize(void) {
    MOV             R1,#1

loc_120F44
    LDREX           R2, [R0]
    STREX           R3, R1, [R0]
    CMP             R3, #0 // if R3 != 0 then loop.
    BNE             loc_120F44
    BX              LR
}

__asm void SimpleLock::Lock(){
    MOV             R2,R0

LAB_0012823c
    LDREX           R1,[R0]
    CMP             R1,#0 // If R1 < 0 skip to LAB_0012825c
    BLE             LAB_0012825c
    RSB             R1,R1,#0
    STREX           R3,R1,[R0]
    CMP             R3,#0 // If R3 != then loop.
    BNE             LAB_0012823c
    BX              LR
LAB_0012825c
    CLREX
    MOV             R0,R2
    B               __cpp(nn::os::SimpleLock::LockImpl) // Branch off to LockImpl, continue there.
}

__asm void SimpleLock::LockImpl(){

    PUSH            {R4, R5, R6, LR}
    SUB             SP,SP,#8 // Initialize onto the Stack
    MOV             R4,R0
loc_128274
    LDREX           R2, [R4]
    CMP             R2, #0
    BGE             loc_128298
    SUB             R1, R2, #1
    STREX           R2, R1, [R4]
    CMP             R2, #0
    BNE             loc_128274
    LDR             R5, =__cpp(0x006d4b2c)
    B               loc_1282C8

loc_128298
    CLREX

loc_12829C
    LDREX           R2, [R4]
    CMP             R2, #0
    BLE             loc_1282C0
    RSB             R1, R2, #0
    STREX           R2, R1, [R4]
    CMP             R2, #0
    BNE             loc_12829C
    ADD             SP, SP, #8
    POP             {R4-R6,PC}

loc_1282C0
    CLREX
    B               loc_128274

loc_1282C8

    MOV             R3, #0
    LDR             R0, [R5]
    MOV             R6, R3
    MOV             R12, R3
    MOV             R1, R4
    MOV             R2, #1
    STMEA           SP, {R6,R12}
    BL              __cpp(nn::svc::ArbitrateAddress)

loc_1282E8
    LDREX           R2, [R4]
    CMP             R2, #0
    BLE             loc_12830C
    RSB             R1, R2, #1
    STREX           R2, R1, [R4]
    CMP             R2, #0
    BNE             loc_1282E8
    ADD             SP, SP, #8
    POP             {R4-R6,PC}

loc_12830C
    CLREX
    B               loc_1282C8
}

__asm bool SimpleLock::TryLock(){
    LDREX           R1,[R0]
    CMP             R1,#0
    BLE             LAB_00125410
    RSB             R1,R1,#0
    STREX           R2,R1,[R0]
    CMP             R2,#0
    BNE             __cpp(nn::os::SimpleLock::TryLock)
    MOV             R0,#1
    BX              LR
LAB_00125410
    CLREX
    MOV             R0,#0
    BX              LR
}

// Unlocks the Simplelock, go figure.

__asm void SimpleLock::Unlock(){
    PUSH            {R4,LR}
    SUB             SP, SP, #8

loc_120FC4
    LDREX           R1, [R0]
    RSB             R2, R1, #0
    STREX           R1, R2, [R0]
    CMP             R1, #0
    BNE             loc_120FC4
    CMP             R2, #1
    BLE             loc_121004
    MOV             R1, R0
    LDR             R0, =__cpp(0x006d4b2c)
    MOV             R2, #0
    MOV             R4, R2
    MOV             R12, R2
    LDR             R0, [R0]
    MOV             R3, #1
    STMEA           SP, {R4,R12}
    BL              __cpp(nn::svc::ArbitrateAddress)

loc_121004
    ADD             SP, SP, #8
    POP             {R4,PC}
}

// end nonmatch
} // os
} // nn