#include <nn/fs/fs_FileBase.h>
#include <nn/fs/fs_Paramaters.h>
#include <nn/Result.h>

// TODO:: ALL

namespace nn{
namespace fs{
namespace detail{

Result FileBase::TryRead(s32* pOut, void* buffer, size_t size) {
    Result res;
    u32 n = 0;
    if (size != 0) {
        while (true) {
            s32 bytesRead;
            NN_UTIL_RETURN_IF_FAILED(FileBaseImpl::TryReadFile(&bytesRead, this->mPosition, buffer, size));

            n += bytesRead;
            this->mPosition += bytesRead;

            if (bytesRead == size || bytesRead == 0)
                break;

            buffer = (void*)((int)buffer + bytesRead);
            size -= bytesRead;
        }
    }
    *pOut = n;
    return ResultSuccess();
}

Result FileBase::TryWrite(int* pReadOut, const void* pBuffer, size_t pSize, bool pFlush=true){

}

__asm Result FileBase::TrySeek(s64 pSeekOut, PositionBase pPosBase){
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

Result FileBase::TryGetSize(s64* pOut) const{
    nn::util::Int64<s64>* pointer;
    s64 ret;
    Result res = this->FileBaseImpl::TryGetSize(&ret);
    if(res.IsSuccess()){
        this->mSize = ret;
        *pOut = ret;
    }
    else{
        this->mSize = 0;
    }
    return res;
}

Result FileBase::TrySetSize(s64 size){

}

Result FileBase::TryFlush(){
    this->FileBaseImpl::TryFlush();
}

} // detail
} // fs
} // nn