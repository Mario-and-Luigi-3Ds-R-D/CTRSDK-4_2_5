#pragma once

#include <nn/hidlow/CTR/hidlow_AccelerometerLifoRing.h>

namespace nn{
namespace hidlow{
namespace CTR{
__asm void AccelerometerLifoRing::ReadData(hid::CTR::AccelerometerStatus *status,s32 bufferNum,s32 *pReadCount,s64 *pTick,s32 *pIndex){
    PUSH            {R0-R11,LR}
    SUB             SP, SP, #4
    MOV             R12, #0
    CMP             R2, #0
    LDR             R3, [SP,#0x18]
    STR             R12, [R3]
    BLE             loc_11BBF8
    CMP             R2, #7
    MOVGT           R2, #7
    STR             R2, [SP,#0x0]

loc_11BAB4
    LDR             R9, [R0,#0x10]
    LDRD            R2, R3, [R0]
    SUBS            R4, R9, #0
    MOV             R5, R2
    MOV             LR, R3
    LDRD            R2, R3, [R0,#8]
    MOV             R11, R2
    MOV             R10, R3
    BGT             loc_11BAF8
    BNE             loc_11BBF8
    EOR             R2, R5, R11
    EOR             R3, LR, R10
    ORRS            R2, R2, R3
    BNE             loc_11BAF8
    CMP             LR, #0
    MOVGE           R4, #7
    BLT             loc_11BBF8

loc_11BAF8
    LDR             R3, [SP,#0x38]
    LDRD            R2, R3, [R3]
    SUBS            R12, R2, R5
    SBCS            R12, R3, LR
    BLT             loc_11BB1C
    LDR             R2, [SP,#0x3C]
    LDR             R2, [R2]
    SUB             R8, R4, R2
    B               loc_11BB48

loc_11BB1C
    CMP             R10, #0
    ADDLT           R8, R4, #1
    BLT             loc_11BB48
    SUBS            R2, R2, R11
    SBCS            R2, R3, R10
    LDRLT           R8, [SP,#0x0]
    BLT             loc_11BB48
    LDR             R2, [SP,#0x3C]
    LDR             R2, [R2]
    SUB             R2, R4, R2
    ADD             R8, R2, #8

loc_11BB48
    LDR             R2, [SP,#0x0]
    MOV             R12, #0
    CMP             R8, R2
    MOVGT           R8, R2
    CMP             R8, #0
    BLE             loc_11BBAC

loc_11BB60
    SUB             R2, R4, R12
    ADD             R2, R2, #8
    MOV             R3, R2,ASR#31
    ADD             R3, R2, R3,LSR#29
    BIC             R3, R3, #7
    SUB             R2, R2, R3
    ADD             R3, R12, R12,LSL#1
    ADD             R2, R2, R2,LSL#1
    ADD             R6, R1, R3,LSL#1
    ADD             R3, R0, R2,LSL#1
    ADD             R12, R12, #1
    LDRH            R7, [R3,#0x20]
    CMP             R8, R12
    STRH            R7, [R6]
    LDRH            R2, [R3,#0x22]
    STRH            R2, [R6,#2]
    LDRH            R2, [R3,#0x24]
    STRH            R2, [R6,#4]
    BGT             loc_11BB60

loc_11BBAC
    LDR             R12, [R0,#0x10]
    LDRD            R2, R3, [R0]
    LDRD            R6, R7, [R0,#8]
    CMP             R12, R9
    BNE             loc_11BAB4
    EOR             R2, R2, R5
    EOR             R3, R3, LR
    ORRS            R2, R2, R3
    BNE             loc_11BAB4
    EOR             R2, R6, R11
    EOR             R3, R7, R10
    ORRS            R2, R2, R3
    BNE             loc_11BAB4
    LDR             R1, [SP,#0x18]
    LDR             R0, [SP,#0x38]
    STR             R8, [R1]
    STM             R0, {R5,LR}
    LDR             R0, [SP,#0x3C]
    STR             R4, [R0]

loc_11BBF8
    ADD             SP, SP, #0x14
    POP             {R4-R11,PC}
}
}
}
}