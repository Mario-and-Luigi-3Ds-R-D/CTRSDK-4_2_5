#include <cstdlib>
#include <exception>

#include <nn/os/CTR/os_CppException.h>
#include <nn/os/os_ThreadLocal.h>

extern "C" __weak void __ARM_exceptions_buffer_required(void);
extern "C" void* __ARM_exceptions_buffer_init(void);

namespace nn{
namespace os{
namespace CTR{
void DefaultTerminateHandler(){
    std::abort();
}

void DefaultUnexpectedHandler(){
    std::terminate();
}
__asm void nn::os::CTR::SetupThreadCppExceptionEnvironment(){
    PUSH            {R4,LR}
    MRC             p15, 0, R0,c13,c0, 3
    ADD             R2, R0, #0x60 ; '`'
    STR             R2, [R0,#0x5C]
    LDR             R0, =0
    MOV             R1, #0
    MOV             R4, R2
    CMP             R0, #0
    LDR             R0, =__cpp(nn::os::CTR::DefaultUnexpectedHandler)
    STR             R0, [R2,#4]
    LDR             R0, =__cpp(nn::os::CTR::DefaultTerminateHandler)
    STR             R0, [R2,#8]
    STR             R1, [R2]
    STRB            R1, [R2,#0xC]
    STR             R1, [R2,#0x10]
    STR             R1, [R2,#0x14]
    MOVEQ           R0, #0
    STR             R1, [R2,#0x18]
    BLNE            __cpp(__ARM_exceptions_buffer_init)
    STR             R0, [R4,#0x1C]
    POP             {R4,PC}
}


}
}
}