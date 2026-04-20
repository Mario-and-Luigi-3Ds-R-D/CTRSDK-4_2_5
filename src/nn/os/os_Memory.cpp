#include <nn/os/os_Memory.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/os/os_Default.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/svc/svc_Api.h>

namespace nn{
namespace os{

uptr GetMemoryAddress(){
    return sDeviceMemoryAddress;
}

uptr GetAppMemorySize(){
    return sDeviceMemorySize;
}

size_t GetDeviceMemorySize(){
    return sDeviceMemorySize;
}
// Sets/Initializes CTR Memory Size

__asm Result SetDeviceMemorySize(size_t pSize){

    PUSH            {R4-R6,LR}
    MOV             R4, R0
    LDR             R2, =0xE0E01BF2
    MOVS            R0, R0,LSL#20
    SUB             SP, SP, #0x10
    BNE             loc_1074B0
    LDR             R5, =__cpp(&nn::os::sDeviceMemorySize)
    MOV             R1, R5
    LDR             R0, [R5,#4]
    LDR             R1, [R1]
    CMP             R4, R0
    BLS             loc_10750C
    CMP             R0, #0
    BEQ             loc_1074BC
    ORR             R3, R0, R4
    MOVS            R3, R3,LSL#12
    BEQ             loc_1074BC

loc_1074B0
    MOV             R0, R2

loc_1074B4

    ADD             SP, SP, #0x10
    POP             {R4-R6,PC}

loc_1074BC

    CMP             R0, #0
    SUB             R3, R4, R0
    ADDNE           R1, R1, R0
    MOV             R2, #3
    ADD             R0, R2, #0x10000
    STMEA           SP, {R0,R2}
    MOVEQ           R1, #0
    MOV             R2, #0
    ADD             R0, SP, #8
    BL              __cpp(nn::svc::ControlMemory)
    ANDS            R1, R0, #0x80000000
    NOP
    BMI             loc_1074B4
    LDR             R1, [R5,#4]
    CMP             R1, #0
    LDREQ           R1, [SP,#8]
    STREQ           R1, [R5]

loc_107500
    STR             R4, [R5,#4]
    ADD             SP, SP, #0x10
    POP             {R4-R6,PC}

loc_10750C
    MOV             R6, #0
    MOV             R2, #1
    SUB             R3, R0, R4
    STMEA           SP, {R2,R6}
    ADD             R1, R1, R4
    MOV             R2, R6
    ADD             R0, SP, #8
    BL              __cpp(nn::svc::ControlMemory)
    ANDS            R1, R0, #0x80000000
    NOP
    BMI             loc_1074B4
    CMP             R4, #0
    STREQ           R6, [R5]
    B               loc_107500
}

// Sets/Initializes CTR Heap for MemoryBlock set of funcs.
__asm void SetupHeapForMemoryBlock(){

    PUSH            {R4,R5,LR}
    MOV             R4, R0
    MOVS            R0, R0,LSL#20
    LDR             R5, =__cpp(&nn::os::sDeviceHeapSize)
    LDRNE           R0, =0xE0E01BF2
    SUB             SP, SP, #0xC
    BNE             loc_1075E0
    LDR             R0, [R5,#8]
    CMP             R4, R0
    BLS             loc_1075B4
    MOV             R2, #3
    ADD             R1, R0, #0x8000000
    SUB             R3, R4, R0
    STR             R2, [SP,#0]
    STR             R2, [SP,#4]
    MOV             R2, #0
    ADD             R0, SP, #8
    BL              __cpp(nn::svc::ControlMemory)
    ANDS            R1, R0, #0x80000000
    BMI             loc_1075E0

loc_1075AC
    STR             R4, [R5,#8]
    B               loc_1075E0

loc_1075B4
    MOV             R12, #0
    MOV             R2, #1
    SUB             R3, R0, R4
    STMEA           SP, {R2,R12}
    ADD             R1, R4, #0x8000000
    MOV             R2, R12
    ADD             R0, SP, #8
    BL              __cpp(nn::svc::ControlMemory)
    ANDS            R1, R0, #0x80000000
    NOP
    BPL             loc_1075AC

loc_1075E0

    MOVS            R1, R0,LSR#31
    BLNE            __cpp(nn::os::CTR::detail::HandleInternalError)
    LDR             R1, [R5,#8]
    MOV             R0, #0x8000000
    BL              __cpp(nn::os::InitializeMemoryBlock)
    ADD             SP, SP, #0xC
    POP             {R4,R5,LR}
    B               __cpp(nn::os::SetDefaultAutoStackManager)
}

size_t GetHeapSoze(){
    return sDeviceHeapSize;
}

int GetCodeRegionAddress(){
    return 0x10000;
}

int GetCodeRegionSize(){
    return 0x53cb98;
}

__asm size_t GetUsingMemorySize(){
    PUSH            {LR}
    SUB             SP, SP, #0x14
    MOV             R0, #0
    STR             R0, [SP,#0x8]
    LDR             R0, =__cpp(0x0069A448)
    LDR             R1, [R0,#8]
    STR             R1, [SP,#0xC]
    LDR             R1, [R0]
    ADD             R0, SP, #0x8
    BL              __cpp(nn::svc::GetResourceLimit)
    LDR             R1, [SP,#0x8]
    MOV             R3, #1
    ADD             R2, SP, #0xC
    MOV             R0, SP
    SVC             0x3A ; ':'
    LDR             R0, [SP,#0x8]
    SVC             0x23 ; '#'
    LDR             R0, [SP,#0x0]
    ADD             SP, SP, #0x14
    POP             {PC}
}

}
}