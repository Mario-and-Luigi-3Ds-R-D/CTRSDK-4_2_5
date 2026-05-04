/* Simple Lock */

#include <nn/os/os_SimpleLock.h>
#include <nn/svc/svc_Api.h>

namespace nn{
namespace os{

namespace{
        struct ReverseIfPositiveUpdater{
            bool operator()(s32& x){
                if(x > 0){
                    x = -x;
                    return true;
                }
                else{
                    return false;
                }
            }
        };

        struct ReverseUpdater{
            s32 afterUpdate;
            bool operator()(s32& x){
                x = -x;
                afterUpdate = x;
                return true;
            }
        };

        struct DecrementIfNegativeUpdater{
            bool operator()(s32& x){
            if( x < 0 ){
                --x;
                return true;
            }
            else{
                return false;
            }
        }
    };

        struct ReverseAndIncrementIfPositiveUpdater{
            bool operator()(s32& x){
            if( x > 0 ){
                x = -x + 1;
                return true;
                }
            else{
                return false;
            }
        }
    };
}

void SimpleLock::Initialize(void) {
    *this->mCounter = 1; // ultimate ASM this creates lmao
}

__asm void SimpleLock::Lock(){
    MOV             R2, R0

loc_12823C
    LDREX           R1, [R0]
    CMP             R1, #0
    BLE             loc_12825C
    RSB             R1, R1, #0
    STREX           R3, R1, [R0]
    CMP             R3, #0
    BNE             loc_12823C
    BX              LR

loc_12825C
    CLREX
    MOV             R0, R2
    B               __cpp(nn::os::SimpleLock::Lock)
}

__asm void SimpleLock::LockImpl(){
    PUSH            {R4-R6,LR}
    SUB             SP, SP, #8
    MOV             R4, R0

loc_128274
    LDREX           R2, [R4]
    CMP             R2, #0
    BGE             loc_128298
    SUB             R1, R2, #1
    STREX           R2, R1, [R4]
    CMP             R2, #0
    BNE             loc_128274
    LDR             R5, =__cpp(&nn::os::WaitableCounter::sHandle)
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
    LDREX           R1, [R0]
    CMP             R1, #0
    BLE             loc_10DCD0
    RSB             R1, R1, #0
    STREX           R2, R1, [R0]
    CMP             R2, #0
    BNE             __cpp(nn::os::SimpleLock::TryLock)
    MOV             R0, #1
    BX              LR

loc_10DCD0
    CLREX
    MOV             R0, #0
    BX              LR
}

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
    LDR             R0, =__cpp(&nn::os::WaitableCounter::sHandle)
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