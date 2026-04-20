#include <nn/os/os_TransferMemoryBlock.h>
#include <nn/os/os_SharedMemory.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/svc/svc_Api.h>

namespace nn{
namespace os{

TransferMemoryBlock::~TransferMemoryBlock(){
    this->Finalize();
    this->Close();
}

__asm void TransferMemoryBlock::Finalize(){
    PUSH            {R4-R6,LR}
    MOV             R4, R0
    LDR             R0, [R0,#0x14]
    CMP             R0, #0
    BEQ             locret_45F130
    LDR             R1, [R4,#8]
    MOV             R5, #0
    CMP             R1, #0
    BEQ             loc_45F11C
    LDRB            R2, [R4,#0x18]
    CMP             R2, #0
    STREQ           R5, [R4,#8]
    STREQ           R5, [R4,#0xC]
    BEQ             loc_45F11C
    SVC             0x20
    MOV             R0, R4
    BL              __cpp(nn::os::detail::FreeToSharedMemorySpace)

loc_45F11C
    LDR             R0, [R4,#0x14]!
    CMP             R0, #0
    BEQ             locret_45F130
    SVC             0x23
    STR             R5, [R4]

locret_45F130
    POP             {R4-R6,PC}
}

// Initialize TranferMemoryBlock, nn::mic lib uses this, so it wouldnt do much remaking this shit.

__asm Result TransferMemoryBlock::Initialize(){
    PUSH            {R4-R6,LR}
    MOV             R4, R0
    LDR             R0, [R0,#8]
    SUB             SP, SP, #8
    MOV             R5, R1
    CMP             R0, #0
    LDR             R12, [SP,#0x18]
    LDRNE           R0, =0x8A01BF9
    MOV             R6, R2
    BNE             loc_45F0B0
    MOVS            R0, R5,LSL#20
    LDRNE           R0, =0xE0E01BF1
    BNE             loc_45F0B0
    MOVS            R0, R6,LSL#20
    LDRNE           R0, =0xE0E01BF2
    BNE             loc_45F0B0
    MOV             R0, #0
    STR             R0, [SP,#0x4]
    ADD             R0, SP, #0x4
    STR             R12, [SP,#0x0]
    BL              __cpp(nn::svc::CreateMemoryBlock)
    MOVS            R1, R0,LSR#31
    BNE             loc_45F0B0
    LDR             R2, [SP,#0x4]
    STR             R2, [R4,#0x14]
    ADD             R4, R4, #8
    STM             R4, {R5,R6}

loc_45F0B0
    MOVS            R1, R0,LSR#31
    BEQ             loc_45F0C4
    ADD             SP, SP, #8
    POP             {R4-R6,LR}
    B               __cpp(nn::os::CTR::detail::HandleInternalError)

loc_45F0C4
    ADD             SP, SP, #8
    POP             {R4-R6,PC}
}
}
}