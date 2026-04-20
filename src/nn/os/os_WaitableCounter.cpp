#include "nn/os/os_WaitableCounter.h"
#include "nn/svc/svc_Api.h"

namespace nn{
namespace os{

s32 WaitableCounter::sHandle;
// Initializes the WaitableCounter.
__asm void WaitableCounter::Initialize(void) {
    PUSH            {R3-R5,LR}
    LDR             R4, =__cpp(&sHandle)
    LDR             R0, [R4]
    CMP             R0, #0
    BNE             locret_1073F0
    MOV             R0, #0
    STR             R0, [SP,#0x0]
    MOV             R0, SP
    BL              __cpp(nn::svc::CreateAddressArbiter)
    AND             R0, R0, #0x80000000
    CMP             R0, #0
    LDRGE           R0, [SP,#0x0]
    STRGE           R0, [R4]

locret_1073F0
    POP             {R3-R5,PC}
}

} // os
} // nn