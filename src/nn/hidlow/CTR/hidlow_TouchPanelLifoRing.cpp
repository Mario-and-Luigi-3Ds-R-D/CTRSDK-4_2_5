#include <nn/hidlow/CTR/hidlow_TouchPanelLifoRing.h>

namespace nn{
namespace hidlow{
namespace CTR{
__asm void TouchPanelLifoRing::ReadData(hid::CTR::TouchPanelStatus *status,s32 bufferNum,s32 *pReadCount,s64 *pTick,s32 *pIndex){
    PUSH            {R0-R11,LR}
    SUB             SP, SP, #4
    MOV             R12, #0
    CMP             R2, #0
    LDR             R3, [SP,#0x18]
    STR             R12, [R3]
    BLE             loc_10FFE0
    CMP             R2, #7
    MOVGT           R2, #7
    STR             R2, [SP,#0x0]

loc_10FE9C
    LDR             R9, [R0,#0x10]
    LDRD            R2, R3, [R0]
    SUBS            R4, R9, #0
    MOV             R5, R2
    ADD             R2, R0, #8
    MOV             LR, R3
    LDRD            R2, R3, [R2]
    MOV             R11, R2
    MOV             R10, R3
    BGT             loc_10FEE4
    BNE             loc_10FFE0
    EOR             R2, R5, R11
    EOR             R3, LR, R10
    ORRS            R2, R2, R3
    BNE             loc_10FEE4
    CMP             LR, #0
    MOVGE           R4, #7
    BLT             loc_10FFE0

loc_10FEE4
    LDR             R2, [SP,#0x38]
    LDR             R3, [R2]
    LDR             R2, [R2,#4]
    SUBS            R12, R3, R5
    SBCS            R12, R2, LR
    BLT             loc_10FF0C
    LDR             R2, [SP,#0x3C]
    LDR             R2, [R2]
    SUB             R8, R4, R2
    B               loc_10FF38

loc_10FF0C
    CMP             R10, #0
    ADDLT           R8, R4, #1
    BLT             loc_10FF38
    SUBS            R3, R3, R11
    SBCS            R2, R2, R10
    LDRLT           R8, [SP,#0x0]
    BLT             loc_10FF38
    LDR             R2, [SP,#0x3C]
    LDR             R2, [R2]
    SUB             R2, R4, R2
    ADD             R8, R2, #8

loc_10FF38
    LDR             R2, [SP,#0x0]
    MOV             R12, #0
    CMP             R8, R2
    MOVGT           R8, R2
    CMP             R8, #0
    BLE             loc_10FF94

loc_10FF50
    SUB             R2, R4, R12
    ADD             R2, R2, #8
    ADD             R7, R1, R12,LSL#3
    MOV             R3, R2,ASR#31
    ADD             R3, R2, R3,LSR#29
    BIC             R3, R3, #7
    SUB             R2, R2, R3
    ADD             R3, R0, R2,LSL#3
    LDRH            R6, [R3,#0x20]
    ADD             R12, R12, #1
    CMP             R8, R12
    STRH            R6, [R7]
    LDRH            R2, [R3,#0x22]
    STRH            R2, [R7,#2]
    LDRB            R2, [R3,#0x24]
    STRB            R2, [R7,#4]
    BGT             loc_10FF50

loc_10FF94
    LDR             R12, [R0,#0x10]
    LDRD            R2, R3, [R0]
    LDRD            R6, R7, [R0,#8]
    CMP             R12, R9
    BNE             loc_10FE9C
    EOR             R2, R2, R5
    EOR             R3, R3, LR
    ORRS            R2, R2, R3
    BNE             loc_10FE9C
    EOR             R2, R6, R11
    EOR             R3, R7, R10
    ORRS            R2, R2, R3
    BNE             loc_10FE9C
    LDR             R1, [SP,#0x18]
    LDR             R0, [SP,#0x30]
    STR             R8, [R1]
    STM             R0, {R5,LR}
    LDR             R0, [SP,#0x3C]
    STR             R4, [R0]

loc_10FFE0
    ADD             SP, SP, #0x14
    POP             {R4-R11,PC}
}
}
}
}