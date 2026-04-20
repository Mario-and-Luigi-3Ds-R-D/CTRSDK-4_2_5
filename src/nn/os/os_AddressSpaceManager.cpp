#include <nn/os/os_AddressSpaceManager.h>
#include <nn/fnd/fnd_Intrusive.h>

namespace nn{
namespace os{

// I raged trying to grt ts to wortk
// 
// Allocates to the AddressSpaceManager using sizes and block base.
__asm uptr AddressSpaceManager::Allocate(MemoryBlockBase* pBlock, size_t size, size_t skipSize){
    PUSH            {R4-R10,LR}
    MOV             R5, R1
    MOV             R7, R0
    ADD             R0, R0, #0xC
    MOV             R9, R2
    MOV             R10, R3
    MOV             R6, R0
    BL              __cpp(nn::os::CriticalSection::Enter)
    LDR             R12, [R7,#8]
    MOV             R3, #0
    CMP             R12, #0
    BEQ             loc_13285C
    LDR             R4, [R12]
    LDR             R1, [R7,#4]
    CMP             R4, #0
    ADDNE           R8, R9, R10
    BEQ             loc_13290C

loc_132820
    ADD             R0, R4, #8
    LDM             R0, {R0,R2}
    ADD             R2, R2, R0
    SUB             R1, R1, R2
    CMP             R8, R1
    BHI             loc_132840
    MOV             R3, R4
    B               loc_13285C

loc_132840
    CMP             R12, R4
    SUB             R1, R0, R10
    BEQ             loc_13285C
    LDR             R4, [R4]
    CMP             R4, #0
    BNE             loc_132820
    B               loc_13290C

loc_13285C
    CMP             R3, #0
    BEQ             loc_13290C
    LDRD            R0, R1, [R3,#8]
    CMP             R12, #0
    ADD             R0, R0, R1
    ADD             R8, R0, R10
    LDRNE           R0, [R12]
    MOVEQ           R0, #0
    MOV             R1, R3
    CMP             R0, R3
    LDRNE           R0, [R1,#4]
    CMPNE           R0, #0
    BEQ             loc_1328E8
    CMP             R12, R0
    BNE             loc_1328CC
    MOV             R0, R5
    CMP             R12, #0
    STREQ           R0, [R0,#4]
    STREQ           R0, [R0]
    BEQ             loc_1328C4
    STR             R12, [R5,#4]
    LDR             R2, [R12]
    STR             R5, [R2,#4]
    LDR             R2, [R12]
    STR             R2, [R5]
    STR             R5, [R12]

loc_1328C4
    STR             R0, [R7,#8]
    B               loc_132978

loc_1328CC
    STR             R0, [R5,#4]
    LDR             R2, [R0]
    STR             R5, [R2,#4]
    LDR             R2, [R0]
    STR             R2, [R5]
    STR             R5, [R0]
    B               loc_132978

loc_1328E8
    CMP             R12, #0
    BEQ             loc_13296C
    STR             R12, [R5,#4]
    LDR             R1, [R12]
    STR             R5, [R1,#4]
    LDR             R1, [R12]
    STR             R1, [R5]
    STR             R5, [R12]
    B               loc_132978

loc_13290C
    LDR             R8, [R7]
    CMP             R12, #0
    BEQ             loc_13294C
    LDR             R0, [R12,#8]
    ADD             R1, R8, R9
    ADD             R1, R1, R10
    CMP             R1, R0
    BHI             loc_13295C
    STR             R12, [R5,#4]
    LDR             R2, [R12]
    STR             R5, [R2,#4]
    LDR             R2, [R12]
    STR             R2, [R5]
    STR             R5, [R12]
    STR             R5, [R7,#8]
    B               loc_132978

loc_13294C
    LDR             R1, [R7,#4]
    ADD             R0, R8, R9
    CMP             R1, R0
    BCS             loc_13296C

loc_13295C
    MOV             R0, R6
    BL              __cpp(nn::os::CriticalSection::Leave)
    MOV             R0, #0
    POP             {R4-R10,PC}

loc_13296C
    STR             R5, [R5,#4]
    STR             R5, [R5]
    STR             R5, [R7,#8]

loc_132978
    STRD            R8, R9, [R5,#8]
    MOV             R0, R6
    BL              __cpp(nn::os::CriticalSection::Leave)
    MOV             R0, R8
    POP             {R4-R10,PC}
}

// TODO: Recreate this, please.
// 
// Free the space manager.
__asm void AddressSpaceManager::Free(MemoryBlockBase *p){
    PUSH            {R4-R6,LR}
    MOV             R6, R0
    ADD             R0, R0, #0xC
    MOV             R4, R1
    MOV             R5, R0
    BL              __cpp(nn::os::CriticalSection::Enter)
    LDR             R1, [R4]
    MOV             R0, #0
    CMP             R1, R4
    STREQ           R0, [R6,#8]
    BEQ             loc_128418
    LDR             R1, [R6,#8]
    MOV             R2, R4
    CMP             R1, R4
    LDREQ           R1, [R1,#4]
    STREQ           R1, [R6,#8]
    LDR             R1, [R4,#4]
    LDR             R2, [R2]
    STR             R2, [R1]
    LDM             R4, {R1,R2}
    STR             R2, [R1,#4]

loc_128418
    STR             R0, [R4,#4]
    STR             R0, [R4]
    STR             R0, [R4,#8]
    STR             R0, [R4,#0xC]
    MOV             R0, R5
    POP             {R4-R6,LR}
    B               __cpp(nn::os::CriticalSection::Leave)
}

// Switch statement for ADR SpaceManager
//
//
__asm void AddressSpaceManager::Switch(MemoryBlockBase *pTo,MemoryBlockBase *pFrom){
    PUSH            {R4-R8,LR}
    ADD             R6, R0, #0xC
    MOV             R7, R0
    MOV             R4, R1
    MOV             R5, R2
    MOV             R0, R6
    BL              __cpp(nn::os::CriticalSection::Enter)
    LDRD            R0, R1, [R5,#8]
    STRD            R0, R1, [R4,#8]
    LDR             R2, [R7,#8]
    CMP             R2, R5
    BNE             loc_45EFA0
    CMP             R2, #0
    STREQ           R4, [R4,#4]
    STREQ           R4, [R4]
    BEQ             loc_45EF98
    STR             R2, [R4,#4]
    LDR             R1, [R2]
    STR             R4, [R1,#4]
    LDR             R1, [R2]
    STR             R1, [R4]
    STR             R4, [R2]

loc_45EF98
    STR             R4, [R7,#8]
    B               loc_45EFE4

loc_45EFA0
    MOVS            R0, R5
    BEQ             loc_45EFC4
    STR             R0, [R4,#4]
    LDR             R1, [R0]
    STR             R4, [R1,#4]
    LDR             R1, [R0]
    STR             R1, [R4]
    STR             R4, [R0]
    B               loc_45EFE4

loc_45EFC4
    CMP             R2, #0
    BEQ             loc_45F034
    STR             R2, [R4,#4]
    LDR             R0, [R2]
    STR             R4, [R0,#4]
    LDR             R0, [R2]
    STR             R0, [R4]
    STR             R4, [R2]

loc_45EFE4
    MOV             R0, #0
    STR             R0, [R5,#8]
    STR             R0, [R5,#0xC]
    LDR             R1, [R5]
    CMP             R1, R5
    STREQ           R0, [R7,#8]
    BEQ             loc_45F020
    LDR             R1, [R7,#8]
    CMP             R1, R5
    LDREQ           R1, [R1,#4]
    STREQ           R1, [R7,#8]
    LDM             R5, {R1,R2}
    STR             R1, [R2]
    LDM             R5, {R1,R2}
    STR             R2, [R1,#4]

loc_45F020
    STR             R0, [R5,#4]
    STR             R0, [R5]
    MOV             R0, R6
    POP             {R4-R8,LR}
    B               __cpp(nn::os::CriticalSection::Leave)

loc_45F034
    STR             R4, [R4,#4]
    STR             R4, [R4]
    STR             R4, [R7,#8]
    B               loc_45EFE4
}

}
}

// TODO: Remake these.

extern "C" {

__asm void nnosAddressSpaceManagerInitialize(nnosAddressSpaceManager* p, uptr begin, size_t size){
    PUSH            {R4-R6,LR}
    CMP             R0, #0
    BEQ             loc_116730
    MOV             R12, #0
    STR             R12, [R0,#8]
    STR             R12, [R0,#0xC]
    MOV             R4, #0xFFFFFFFF
    STR             R4, [R0,#0x14]
    STR             R12, [R0,#0x10]
    STR             R12, [R0,#4]
    STR             R12, [R0]

loc_116730
    MOV             R4, R0
    LDR             R0, [R0]
    MOV             R5, R1
    MOV             R6, R2
    CMP             R0, #0
    LDREQ           R0, [R4,#4]
    CMPEQ           R0, #0
    BNE             locret_116764
    ADD             R0, R4, #0xC
    BL              __cpp(nn::os::CriticalSection::Initialize)
    ADD             R0, R5, R6
    STR             R0, [R4,#4]
    STR             R5, [R4]

locret_116764
    POP             {R4-R6,PC}
}

// Pointer to -> AddressSpaceMan::Switch
__asm void nnosAddressSpaceManagerSwitch(nnosAddressSpaceManager* p, nnosMemoryBlockBase* pTo, nnosMemoryBlockBase* pFrom){
    B               __cpp(nn::os::AddressSpaceManager::Switch)
}

}