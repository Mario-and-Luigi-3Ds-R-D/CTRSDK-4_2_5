#include <nn/hidlow/CTR/hidlow_PadLifoRing.h>

namespace nn{
namespace hidlow{
namespace CTR{
__asm void PadLifoRing::ReadData(hid::CTR::PadStatus *status,s32 bufferNum,s32 *pReadCount,s64 *pTick,s32 *pIndex){
    PUSH            {R0-R11,LR}
    SUB             SP, SP, #0x14
    MOV             R12, #0
    CMP             R2, #0
    LDR             R3, [SP,#0x20]
    STR             R12, [R3]
    BLE             loc_10FE6C
    CMP             R2, #7
    MOVGT           R2, #7
    STR             R2, [SP,#0x4]

loc_10FCF4
    LDR             R4, [R0,#0x10]
    STR             R4, [SP,#0xC]
    LDRD            R8, R9, [R0]
    LDRD            R2, R3, [R0,#8]
    MOV             R6, R9
    CMP             R4, #0
    STR             R2, [SP,#0x8]
    STR             R3, [SP,#0x0]
    BGT             loc_10FD40
    BNE             loc_10FE6C
    MOV             R3, R2
    LDR             R2, [SP,#0x0]
    EOR             R3, R3, R8
    EOR             R2, R2, R6
    ORRS            R2, R2, R3
    BNE             loc_10FD40
    CMP             R6, #0
    MOVGE           R4, #7
    BLT             loc_10FE6C

loc_10FD40
    LDR             R3, [SP,#0x48]
    LDRD            R2, R3, [R3]
    SUBS            R12, R2, R8
    SBCS            R12, R3, R6
    BLT             loc_10FD64
    LDR             R2, [SP,#0x4]
    LDR             R2, [R2]
    SUB             R9, R4, R2
    B               loc_10FD98

loc_10FD64
    LDR             R12, [SP,#0x0]
    CMP             R12, #0
    ADDLT           R9, R4, #1
    BLT             loc_10FD98
    LDR             LR, [SP,#0x8]
    SUBS            R2, R2, LR
    SBCS            R2, R3, R12
    LDRLT           R9, [SP,#0x4]
    BLT             loc_10FD98
    LDR             R2, [SP,#0x4C]
    LDR             R2, [R2]
    SUB             R2, R4, R2
    ADD             R9, R2, #8

loc_10FD98
    LDR             R2, [SP,#0x4]
    MOV             R5, #0
    CMP             R9, R2
    MOVGT           R9, R2
    CMP             R9, #0
    BLE             loc_10FE10

loc_10FDB0
    SUB             R2, R4, R5
    ADD             R2, R2, #8
    ADD             R7, R1, R5,LSL#4
    MOV             R3, R2,ASR#31
    ADD             R3, R2, R3,LSR#29
    BIC             R3, R3, #7
    SUB             R2, R2, R3
    ADD             R3, R0, R2,LSL#4
    LDR             R10, [R3,#0x28]
    ADD             LR, R3, #0x30 ; '0'
    ADD             R2, R3, #0x34 ; '4'
    ADD             R11, R3, #0x36 ; '6'
    STR             R10, [R7]
    LDR             R3, [R3,#0x2C]
    ADD             R5, R5, #1
    CMP             R9, R5
    STR             R3, [R7,#4]
    LDR             R3, [LR]
    STR             R3, [R7,#8]
    LDRH            R2, [R2]
    STRH            R2, [R7,#0xC]
    LDRH            R2, [R11]
    STRH            R2, [R7,#0xE]
    BGT             loc_10FDB0

loc_10FE10
    LDR             R12, [R0,#0x10]
    LDRD            R2, R3, [R0]
    LDRD            R10, R11, [R0,#8]
    LDR             LR, [SP,#0xC]
    CMP             R12, LR
    BNE             loc_10FCF4
    EOR             R2, R2, R8
    EOR             R3, R3, R6
    ORRS            R2, R2, R3
    BNE             loc_10FCF4
    LDR             R3, [SP,#0x8]
    LDR             R2, [SP,#0x0]
    EOR             R3, R3, R10
    EOR             R2, R2, R11
    ORRS            R2, R2, R3
    BNE             loc_10FCF4
    LDR             R1, [SP,#0x28]
    LDR             R0, [SP,#0x48]
    STR             R9, [R1]
    STR             R6, [R0,#4]
    STR             R8, [R0]
    LDR             R0, [SP,#0x4C]
    STR             R4, [R0]

loc_10FE6C
    ADD             SP, SP, #0x24 ; '$'
    POP             {R4-R11,PC}
}
}
}
}