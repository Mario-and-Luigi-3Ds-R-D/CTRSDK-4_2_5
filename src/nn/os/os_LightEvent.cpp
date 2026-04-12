#include "nn/os/os_LightEvent.h"
#include <nn/svc/svc_Api.h>

namespace nn{
namespace os{
// non match

__asm void LightEvent::Initialize(bool pIsManualReset){
    PUSH            {R4-R6,LR}
    MOV             R4, R0
    MOV             R5, R1
    ADD             R0, R0, #4
    BL              __cpp(nn::os::SimpleLock::Initialize)
    CMP             R5, #0
    MOVNE           R1, #0xFFFFFFFE
    MOVEQ           R1, #0xFFFFFFFF

loc_120E68
    LDREX           R0, [R4]
    STREX           R2, R1, [R4]
    CMP             R2, #0
    BNE             loc_120E68
    POP             {R4-R6,PC}
}

__asm void LightEvent::Finalize(){
    PUSH            {R4,R5,LR}
    SUB             SP, SP, #0xC
    LDRSH           R2, [R0,#6]
    MOV             R3, R1

loc_118A60
    LDREX           R4, [R0]
    SUB             R5, R2, R3
    CMP             R5, R4
    MOV             R1, R2
    ADDGE           R1, R4, R3
    STREX           R5, R1, [R0]
    CMP             R5, #0
    BNE             loc_118A60
    CMP             R4, #0
    BLE             loc_118A94
    LDRSH           R1, [R0,#4]
    CMP             R1, #0
    BLE             loc_118AB8

loc_118A94
    LDR             R1, =__cpp(0x006d4b2c)
    MOV             R2, #0
    MOV             R5, R2
    LDR             R12, [R1]
    MOV             R1, R2
    STMEA           SP, {R1,R5}
    MOV             R1, R0
    MOV             R0, R12
    BL              __cpp(nn::svc::ArbitrateAddress)

loc_118AB8
    ADD             SP, SP, #0xC
    MOV             R0, R4
    POP             {R4,R5,PC}
}

__asm void LightEvent::ClearSignal(){
    PUSH            {R4-R6,LR}
    MOV             R4, R0
    LDR             R0, [R0]
    CMP             R0, #1
    BEQ             loc_120F90
    LDR             R0, [R4]
    CMP             R0, #0
    MOVEQ           R0, #0xFFFFFFFF
    BNE             locret_120F8C

loc_120F7C
    LDREX           R1, [R4]
    STREX           R2, R0, [R4]
    CMP             R2, #0
    BNE             loc_120F7C

locret_120F8C
    POP             {R4-R6,PC}

loc_120F90
    ADD             R5, R4, #4
    MOV             R0, R5
    BL              __cpp(nn::os::SimpleLock::Lock)
    MOV             R0, #0xFFFFFFFE

loc_120FA0
    LDREX           R1, [R4]
    STREX           R1, R0, [R4]
    CMP             R1, #0
    BNE             loc_120FA0
    MOV             R0, R5
    POP             {R4-R6,LR}
    B               __cpp(nn::os::SimpleLock::Unlock)
}

__asm void LightEvent::Wait(){
    PUSH            {R4-R6,LR}
    SUB             SP, SP, #8
    LDR             R5, =__cpp(0x006d4b2c)
    MOV             R4, R0

loc_120E8C
    LDR             R0, [R4]
    CMN             R0, #2
    BEQ             loc_120EC0
    CMN             R0, #1
    BEQ             loc_120F10
    CMP             R0, #0
    MOVEQ           R12, #0
    MOVEQ           R3, #0xFFFFFFFF
    BEQ             loc_120EE8
    CMP             R0, #1
    BNE             loc_120F10

loc_120EB8
    ADD             SP, SP, #8
    POP             {R4-R6,PC}

loc_120EC0
    MOV             R3, #0
    MOV             R1, R4
    LDR             R0, [R5]
    MOV             R4, R3
    MOV             R12, R3
    MOV             R2, #1
    STMEA           SP, {R4,R12}
    BL              __cpp(nn::svc::ArbitrateAddress)
    ADD             SP, SP, #8
    POP             {R4-R6,PC}

loc_120EE8

    LDREX           R2, [R4]
    CMP             R2, R12
    BNE             loc_120F04
    STREX           R6, R3, [R4]
    CMP             R6, #0
    BNE             loc_120EE8
    B               loc_120F08

loc_120F04
    CLREX

loc_120F08
    CMP             R2, #0
    BEQ             loc_120EB8

loc_120F10

    MOV             R3, #0
    LDR             R0, [R5]
    MOV             R6, R3
    MOV             R12, R3
    MOV             R1, R4
    MOV             R2, #1
    STMEA           SP, {R6,R12}
    BL              __cpp(nn::svc::ArbitrateAddress)
    NOP
    NOP
    B               loc_120E8C
}

__asm void nn::os::LightEvent::Signal() {
    PUSH            {R4-R6,LR}
    MOV             R4, R0
    LDR             R0, [R0]
    SUB             SP, SP, #8
    LDR             R5, =__cpp(0x006d4b2c)
    CMN             R0, #1
    MOVEQ           R0, #0
    BEQ             loc_118A14
    LDR             R0, [R4]
    CMN             R0, #2
    BNE             loc_118A44
    ADD             R6, R4, #4
    MOV             R0, R6
    BL              __cpp(nn::os::SimpleLock::Lock)
    MOV             R0, #1

loc_1189D4
    LDREX           R1, [R4]
    STREX           R3, R0, [R4]
    CMP             R3, #0
    BNE             loc_1189D4
    MOV             R2, #0
    MOV             R1, R4
    LDR             R0, [R5]
    MOV             R4, R2
    MOV             R12, R2
    MOV             R3, #0xFFFFFFFF
    STMEA           SP, {R4,R12}
    BL              __cpp(nn::svc::ArbitrateAddress)
    ADD             SP, SP, #8
    MOV             R0, R6
    POP             {R4-R6,LR}
    B               __cpp(nn::os::SimpleLock::Unlock)

loc_118A14

    LDREX           R1, [R4]
    STREX           R3, R0, [R4]
    CMP             R3, #0
    BNE             loc_118A14
    MOV             R2, #0
    MOV             R1, R4
    LDR             R0, [R5]
    MOV             R4, R2
    MOV             R12, R2
    MOV             R3, #1
    STMEA           SP, {R4,R12}
    BL              __cpp(nn::svc::ArbitrateAddress)

loc_118A44
    ADD             SP, SP, #8
    POP             {R4-R6,PC}
}

__asm bool LightEvent::TryWait(){
    PUSH            {R4}
    LDR             R1, [R0]
    CMP             R1, #1
    MOVNE           R2, #0
    MOVNE           R1, #0xFFFFFFFF
    BEQ             loc_12822C

loc_128200
    LDREX           R3, [R0]
    CMP             R3, R2
    BNE             loc_12821C
    STREX           R4, R1, [R0]
    CMP             R4, #0
    BNE             loc_128200
    B               loc_128220
loc_12821C
    CLREX

loc_128220
    CMP             R3, #0
    MOVNE           R0, #0
    BNE             loc_128230

loc_12822C
    MOV             R0, #1

loc_128230
    POP             {R4}
    BX              LR
}
    
// end non match
} // os
} // nn