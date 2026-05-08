#include <nn/fs/fs_FileBase.h>
#include <nn/fs/fs_Paramaters.h>
#include <nn/Result.h>

// TODO:: ALL

namespace nn{
namespace fs{
namespace detail{

__asm Result FileBase::TryRead(int* pReadOut, void* pBuffer, size_t pSize){
    PUSH            {R4-R9,LR}
    MOVS            R5, R3
    SUB             SP, SP, #0xC
    MOV             R7, R0
    MOV             R9, R1
    MOV             R6, R2
    MOV             R8, #0
    BEQ             loc_10D96C

loc_10D914
    LDM             R7, {R0,R2,R3}
    STR             R5, [SP,#0x4]
    BIC             R1, R0, #1
    ADD             R0, SP, #0x8
    STR             R6, [SP,#0x0]
    BL              __cpp(nn::fs::CTR::MPCore::detail::UserFileSystem::TryReadFile)
    MOVS            R1, R0,LSR#31
    NOP
    BNE             loc_10D974
    ADD             R1, R7, #4
    LDR             R12, [SP,#0x8]
    LDM             R1, {R0,R3}
    ADD             R8, R8, R12
    ADDS            R0, R0, R12
    ADC             R4, R3, R12,ASR#31
    STM             R1, {R0,R4}
    CMP             R12, R5
    BEQ             loc_10D96C
    CMP             R12, #0
    ADDNE           R6, R6, R12
    SUBNE           R5, R5, R12
    BNE             loc_10D914

loc_10D96C
    MOV             R0, #0
    STR             R8, [R9]

loc_10D974
    ADD             SP, SP, #0xC

locret_10D978
    POP             {R4-R9,PC}
}

__asm Result FileBase::TryWrite(int* pReadOut, const void* pBuffer, size_t pSize, bool pFlush=true){
    PUSH            {R4-R11,LR}
    SUB             SP, SP, #0x14
    MOVS            R5, R3
    MOV             R4, R0
    MOV             R9, R1
    LDR             R8, [SP,#0x38]
    MOV             R7, #0
    MOVNE           R6, R2
    BEQ             loc_45EAF8

loc_45EA7C
    ADD             R0, R4, #4
    CMP             R8, #0
    LDRD            R2, R3, [R0]
    LDR             R1, [R4]
    ADD             R10, SP, #0x4
    ADD             R12, SP, #0xC
    ORREQ           R1, R1, #1
    BICNE           R1, R1, #1
    STR             R1, [R4]
    STR             R6, [SP,#0x0]
    BIC             R1, R1, #1
    MOV             R0, R12
    STM             R10, {R5,R8}
    BL              __cpp(nn::fs::CTR::MPCore::detail::UserFileSystem::TryWriteFile)
    MOVS            R1, R0,LSR#31
    NOP
    BNE             loc_45EB00
    ADD             R3, R4, #4
    LDR             R0, [SP,#0xC]
    LDM             R3, {R2,R12}
    ADD             R7, R7, R0
    ADDS            R2, R2, R0
    ADC             R1, R12, R0,ASR#31
    STR             R1, [R4,#8]
    CMP             R0, R5
    STR             R2, [R4,#4]
    BEQ             loc_45EAF8
    CMP             R0, #0
    ADDNE           R6, R6, R0
    SUBNE           R5, R5, R0
    BNE             loc_45EA7C

loc_45EAF8
    MOV             R0, #0
    STR             R7, [R9]

loc_45EB00
    ADD             SP, SP, #0x14
    POP             {R4-R11,PC}
}

__asm Result FileBase::TrySeek(s64 pSeekOut, nn::fs::PositionBase pPosBase){
    PUSH            {R4-R8,LR}
    SUB             SP, SP, #8
    MOV             R8, R0
    LDR             R0, [SP,#0x20]
    MOV             R6, R2
    MOV             R7, R3
    CMP             R0, #0
    BEQ             loc_120D64
    CMP             R0, #1
    BEQ             loc_120D38
    CMP             R0, #2
    LDRNE           R0, =0xE0E046BD
    BNE             loc_120D7C
    LDR             R0, [R8]
    BIC             R1, R0, #1
    MOV             R0, SP
    BL              __cpp(nn::fs::CTR::MPCore::detail::UserFileSystem::TryGetFileSize)
    ANDS            R1, R0, #0x80000000
    BMI             loc_120D48
    LDR             R4, [SP,#0x4]
    LDR             R5, [SP,#0x0]
    STR             R4, [R8,#0x10]
    STR             R5, [R8,#0xC]
    B               loc_120D54

loc_120D38
    LDRD            R0, R1, [R8,#4]
    ADDS            R6, R6, R0
    ADC             R7, R1, R3
    B               loc_120D64

loc_120D48
    MOV             R1, #0
    STR             R1, [R8,#0xC]
    STR             R1, [R8,#0x10]

loc_120D54
    MOVS            R1, R0,LSR#31
    BNE             loc_120D7C
    ADDS            R6, R6, R5
    ADC             R7, R7, R4

loc_120D64
    ADD             SP, SP, #8
    MOV             R2, R6
    MOV             R3, R7
    MOV             R0, R8
    POP             {R4-R8,LR}
    B               __cpp(nn::fs::detail::FileBase::TrySetPosition)

loc_120D7C
    ADD             SP, SP, #8
    POP             {R4-R8,PC}
}

__asm Result FileBase::TrySetPosition(s64 pPosSet){
    PUSH            {R4-R9,LR}
    SUBS            R4, R3, #0
    SUB             SP, SP, #0xC
    MOV             R8, R0
    LDR             R9, =0xE0E046C1
    MOV             R7, R2
    BLT             loc_1281C4
    LDR             R1, [R8,#0xC]
    LDR             R0, [R8,#0x10]
    SUBS            R1, R7, R1
    SBCS            R0, R4, R0
    BLT             loc_1281D0
    LDR             R0, [R8]
    BIC             R1, R0, #1
    MOV             R0, SP
    BL              __cpp(nn::fs::CTR::MPCore::detail::UserFileSystem::TryGetFileSize)
    ANDS            R1, R0, #0x80000000
    BMI             loc_1281A4
    LDR             R5, [SP,#0x4]
    LDR             R6, [SP,#0x0]
    STR             R5, [R8,#0x10]
    STR             R6, [R8,#0xC]
    B               loc_1281B0

loc_1281A4
    MOV             R1, #0
    STR             R1, [R8,#0xC]
    STR             R1, [R8,#0x10]

loc_1281B0
    MOVS            R1, R0,LSR#31
    BNE             loc_1281C8
    SUBS            R0, R6, R7
    SBCS            R0, R5, R4
    BGE             loc_1281D0

loc_1281C4
    MOV             R0, R9

loc_1281C8
    ADD             SP, SP, #0xC
    POP             {R4-R9,PC}

loc_1281D0
    STR             R7, [R8,#4]!
    MOV             R0, #0
    STR             R4, [R8,#4]
    ADD             SP, SP, #0xC
    POP             {R4-R9,PC}
}

__asm Result FileBase::TryGetSize(s64* pOutSize) const{
    PUSH            {R4,R5,LR}
    MOV             R4, R0
    LDR             R0, [R0]
    MOV             R5, R1
    SUB             SP, SP, #0xC
    BIC             R1, R0, #1
    MOV             R0, SP
    BL              __cpp(nn::fs::CTR::MPCore::detail::UserFileSystem::TryGetFileSize)
    MOV             R1, R0
    ANDS            R0, R0, #0x80000000
    BMI             loc_113C30
    LDMFD           SP, {R0,R2}
    ADD             R4, R4, #0xC
    STM             R4, {R0,R2}
    STM             R5, {R0,R2}
    B               loc_113C3C

loc_113C30
    MOV             R0, #0
    STR             R0, [R4,#0xC]
    STR             R0, [R4,#0x10]

loc_113C3C
    ADD             SP, SP, #0xC
    MOV             R0, R1
    POP             {R4,R5,PC}
}

__asm Result FileBase::TrySetSize(s64 size){
    PUSH            {R4-R6,LR}
    MOV             R6, R0
    LDR             R0, [R0]
    MOV             R5, R2
    MOV             R4, R3
    BIC             R0, R0, #1
    BL              __cpp(nn::fs::CTR::MPCore::detail::UserFileSystem::TryGetFileSize)
    ANDS            R1, R0, #0x80000000
    BMI             locret_45EA38
    ADD             R3, R6, #4
    STR             R4, [R6,#0x10]
    STR             R5, [R6,#0xC]
    LDM             R3, {R3,R12}
    SUBS            R3, R5, R3
    SBCS            R3, R4, R12
    STRLT           R5, [R6,#4]!
    STRLT           R4, [R6,#4]
    BGE             locret_45EA38

locret_45EA38
    POP             {R4-R6,PC}
}

Result FileBase::TryFlush(){
    void* buf = this->mFile;
    this->mFile = (void*)(((uintptr_t)buf) & 0xfffffffe);
    UserFileSystem::TryFlush((void*)(((uintptr_t)buf) & 0xfffffffe));
}

} // detail
} // fs
} // nn