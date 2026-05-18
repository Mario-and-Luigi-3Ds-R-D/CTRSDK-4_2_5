#include <nn/cfg/CTR/cfg_IpcUser.h>

namespace nn {
namespace cfg {
namespace CTR {
namespace detail {
namespace IpcUser{
    nn::Handle sSession = 0;

__asm Result GetConfig (void* pData, size_t size, bit32 key){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R3, =0x10082
    STR             R3, [R4,#0x80]!
    ADD             R12, R4, #4
    STM             R12, {R1,R2}
    MOV             R2, #0xC
    STR             R0, [R4,#0x10]
    LDR             R0, =__cpp(&sSession)
    ORR             R1, R2, R1,LSL#4
    STR             R1, [R4,#0xC]
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result GetRegion (CfgRegionCode* regionCode){
    PUSH            {R4-R6,LR}
    MOV             R5, R0
    MRC             p15, 0, R4,c13,c0, 3
    MOV             R0, #0x20000
    STR             R0, [R4,#0x80]!
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_11923C
    LDRB            R0, [R4,#8]
    STRB            R0, [R5]
    LDR             R0, [R4,#4]

locret_11923C
    POP             {R4-R6,PC}
}

}
}
}
}
}