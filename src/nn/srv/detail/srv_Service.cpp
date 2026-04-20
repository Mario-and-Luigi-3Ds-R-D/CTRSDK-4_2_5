#include <nn/srv/detail/srv_Service.h>

namespace nn{
namespace srv{
namespace detail{
namespace Service{
    nn::Handle sSession = 0;

__asm Result EnableNotication(nn::Handle* pSemaphore){
    PUSH            {R4-R6,LR}
    MOV             R5, R0
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0x20000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32
    ANDS            R1, R0, #0x80000000
    BMI             locret_10EECC
    LDR             R0, [R4,#0xC]
    STR             R0, [R5]
    LDR             R0, [R4,#4]

locret_10EECC
    POP             {R4-R6,PC}
}

/*__asm Result GetServiceHandle(nn::Handle* pOut, const char* pService, s32 nameLen, u32 flags){
    PUSH            {R4-R8,LR}
    MOV             R5, R0
    MOV             R6, R2
    MOV             R7, R3
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R0, =0x50100
    ADD             R4, R4, #0x80
    ADD             R2, R4, #4
    STR             R0, [R4]
    MOV             R0, R2
    BL              __cpp(__ARM_common_memcpy4_8)
    LDR             R0, =__cpp(&sSession)
    STRD            R6, R7, [R4,#0xC]
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_119CC4
    LDR             R0, [R4,#0xC]
    STR             R0, [R5]
    LDR             R0, [R4,#4]

locret_119CC4
    POP             {R4-R8,PC}
}*/

Result GetServiceHandle(nn::Handle* pOut, const char* pService, s32 nameLen, u32 flags){

}

__asm Result ReceiveNotification(bit32 *pOut){
    PUSH            {R4-R6,LR}
    MOV             R5, R0
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0xB0000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_119D04
    LDR             R0, [R4,#8]
    STR             R0, [R5]
    LDR             R0, [R4,#4]

locret_119D04
    POP             {R4-R6,PC}
}

__asm Result RegisterClient(void){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R0, =0x10002
    STR             R0, [R4,#0x80]!
    MOV             R0, #0x20 ; ' '
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

}
}
}
}