#include <nn/hid/CTR/detail/Ipc/hid_Ipc.h>

namespace nn{
namespace hid{
namespace CTR{
namespace detail{
namespace Ipc{

nn::Handle sSession;

__asm Result EnableAccelerometer(){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0x110000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result DisableAccelerometer(){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0x120000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result EnableGyroscopeLow(){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0x130000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result DisableGyroscopeLow(){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0x140000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result GetGyroscopeLowCalibrateParam(GyroscopeLowCalibrateParam *){
    PUSH            {R4-R6,LR}
    MOV             R5, R0
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0x160000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_4620E8
    LDR             R1, [R4,#8]
    STR             R1, [R5]
    LDR             R1, [R4,#0xC]
    STR             R1, [R5,#4]
    LDR             R1, [R4,#0x10]
    STR             R1, [R5,#8]
    LDR             R1, [R4,#0x14]
    STR             R1, [R5,#0xC]
    LDRH            R0, [R4,#0x18]
    STRH            R0, [R5,#0x10]
    LDR             R0, [R4,#4]

locret_4620E8
    POP             {R4-R6,PC}
}

__asm Result GetGyroscopeLowRawToDpsCoefficient(){
    PUSH            {R4-R6,LR}
    MOV             R5, R0
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0x150000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_462124
    VLDR            S0, [R4,#8]
    VSTR            S0, [R5]
    LDR             R0, [R4,#4]

locret_462124
    POP             {R4-R6,PC}
}

__asm Result GetIPCHandles(Handle *pSharedMemoryHandle,Handle *pPadEvent,Handle *pTouchPanelEvent,Handle *pAccelerometerEvent,Handle *pGyroscopeLowEvent,Handle *pDebugPadEvent){
    PUSH            {R4-R10,LR}
    MOV             R5, R0
    ADD             R0, SP, #0x20
    MOV             R6, R1
    LDM             R0, {R9,R10}
    MOV             R7, R2
    MOV             R8, R3
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0xA0000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_10E8A8
    LDR             R0, [R4,#0xC]
    STR             R0, [R5]
    LDR             R0, [R4,#0x10]
    STR             R0, [R6]
    LDR             R0, [R4,#0x14]
    STR             R0, [R7]
    LDR             R0, [R4,#0x18]
    STR             R0, [R8]
    LDR             R0, [R4,#0x1C]
    STR             R0, [R9]
    LDR             R0, [R4,#0x20]
    STR             R0, [R10]
    LDR             R0, [R4,#4]

locret_10E8A8
    POP             {R4-R10,PC}
}

}
}
}
}
}