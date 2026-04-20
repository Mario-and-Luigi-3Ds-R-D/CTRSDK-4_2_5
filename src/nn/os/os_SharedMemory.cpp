#include <nn/os/os_SharedMemory.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_Types.h>
#include <nn/svc/svc_Api.h>

namespace nn{
namespace os{

/*namespace{
nnosAddressSpaceManager sSpaceManager;

}*/

namespace detail{
void InitializeSharedMemory(){
    nnosAddressSpaceManagerInitialize(&os::sSpaceManager,0x10000000,0x4000000);
}

}

__asm Result SharedMemoryBlock::AttachAndMap(nn::Handle handle, size_t size, bool readOnly){
    ADD             R2, R2, #0xF00
    ADD             R2, R2, #0xFF
    PUSH            {R4,R5}
    MOV             R4, R2,LSR#12
    STR             R1, [R0,#0x14]
    MOV             R4, R4,LSL#12
    MOV             R1, R4
    POP             {R4,R5}
    MOV             R2, R3
    B               __cpp(SharedMemoryBlock::Map)
}

__asm Result SharedMemoryBlock::Map(size_t size, bool readOnly){
    PUSH            {R4-R6,LR}
    MOV             R4, R0
    LDR             R0, [R0,#8]
    MOV             R5, R2
    CMP             R0, #0
    LDRNE           R0, =0x8A01BF9
    BNE             locret_1283B0
    MOVS            R0, R1,LSL#20
    LDRNE           R0, =0xE0E01BF2
    BNE             locret_1283B0
    MOV             R2, R1
    LDR             R0, =__cpp(&nn::os::sSpaceManager)
    MOV             R3, #0x1000
    MOV             R1, R4
    BL              __cpp(nn::os::AddressSpaceManager::Allocate)
    MOVS            R1, R0
    LDREQ           R0, =0xD8601837
    BEQ             locret_1283B0
    CMP             R5, #0
    STRB            R5, [R4,#0x10]
    LDR             R0, [R4,#0x14]
    MOVNE           R2, #1
    MOVEQ           R2, #3
    MOV             R3, #0x10000000
    SVC             0x1F
    MOVS            R1, R0,LSR#31
    MOVEQ           R1, #1
    STRBEQ          R1, [R4,#0x18]

locret_1283B0
    POP             {R4-R6,PC}
}

__asm void SharedMemoryBlock::Finalize(){
    PUSH            {R4-R6,LR}
    MOV             R4, R0
    LDR             R0, [R0,#0x14]
    CMP             R0, #0
    BEQ             locret_121074
    LDR             R1, [R4,#8]
    MOV             R5, #0
    CMP             R1, #0
    BEQ             loc_121060
    LDRB            R2, [R4,#0x18]
    CMP             R2, #0
    STREQ           R5, [R4,#8]
    STREQ           R5, [R4,#0xC]
    BEQ             loc_121060
    SVC             0x20 ; ' '
    MOVS            R1, R0,LSR#31
    BLNE            __cpp(nn::os::CTR::detail::HandleInternalError)
    LDR             R0, =__cpp(&sSpaceManager)
    MOV             R1, R4
    BL              __cpp(nn::os::AddressSpaceManager::Free)

loc_121060
    LDR             R0, [R4,#0x14]!
    CMP             R0, #0
    BEQ             locret_121074
    SVC             0x23 ; '#'
    STR             R5, [R4]

locret_121074
    POP             {R4-R6,PC}
}

}
}