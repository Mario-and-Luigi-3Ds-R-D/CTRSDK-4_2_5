#include <nn/os/os_StackMemory.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/os/CTR/os_ErrorHandler.h>

namespace nn{
namespace os{
//    extern nnosAddressSpaceManager sSpaceManager;

namespace detail{

void InitializeStackMemory(){
    nnosAddressSpaceManagerInitialize(&os::sSpaceManager,0xe000000, 0x2000000);
}

void Switch(nnosMemoryBlockBase* pTo, nnosMemoryBlockBase* pFrom){
    nnosAddressSpaceManagerSwitch(&os::sSpaceManager,pTo,pFrom);
}

}
}
}

__asm void nnosStackMemoryBlockAllocate(nnosStackMemoryBlock* p, size_t size){
    CMP             R0, #0
    BXEQ            LR
    PUSH            {R4-R6,LR}
    MOV             R2, #0
    STR             R2, [R0]
    STR             R2, [R0,#4]
    STR             R2, [R0,#8]
    STR             R2, [R0,#0xC]
    MOV             R4, R0
    MOV             R5, R1
    STRB            R2, [R0,#0x10]
    BL              __cpp(nn::os::detail::IsMemoryBlockEnabled)
    CMP             R0, #0
    BEQ             locret_613014
    LDR             R0, [R4,#8]
    CMP             R0, #0
    BNE             locret_613014
    ADD             R0, R5, #0xF00
    ADD             R0, R0, #0xFF
    MOV             R1, R0,LSR#12
    MOV             R0, R4
    MOV             R1, R1,LSL#12
    BL              __cpp(nn::os::detail::AllocateFromMemoryBlockSpace)
    CMP             R0, #0
    BNE             locret_613014
    POP             {R4-R6,LR}
    LDR             R0, =0xD8601837
    B               __cpp(nn::os::CTR::detail::HandleInternalError)

locret_613014
    POP             {R4-R6,PC}
}

__asm void nnosStackMemoryBlockFree(nnosStackMemoryBlock* p){
    LDR             R1, [R0,#8]
    CMP             R1, #0
    BEQ             locret_613030
    B               __cpp(nn::os::detail::FreeToMemorySpace)

locret_613030
    BX              LR
}

__asm void nnosStackMemoryBlockGetStacBottom(nnosStackMemoryBlock* p){
    LDR             R1, [R0,#8]
    LDR             R0, [R0,#0xC]
    ADD             R0, R0, R1
    BX              LR
}

__asm void nnosStackMemoryBlockInitialize(nnosStackMemoryBlock* p){
    CMP             R0, #0
    BEQ             locret_613064
    MOV             R1, #0
    STR             R1, [R0]
    STR             R1, [R0,#4]
    STR             R1, [R0,#8]
    STR             R1, [R0,#0xC]
    STRB            R1, [R0,#0x10]

locret_613064
    BX              LR
}