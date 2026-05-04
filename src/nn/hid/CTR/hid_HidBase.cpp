#include <nn/hid/CTR/hid_HidBase.h>
#include <nn/hid/CTR/detail/Ipc/hid_Ipc.h>
#include <nn/srv/srv_Api.h>
#include <string.h>


namespace nn{
namespace hid{
namespace CTR{

HidDevices::~HidDevices(){
    this->mSharedMemoryBlock.Finalize();
    this->mSharedMemoryBlock.Close();
    this->debugPad.Close();
    this->gyroscope.Close();
    this->accelerometer.Close();
    this->touchPanel.Close();
    this->pad.Close();
}

__asm Result HidDevices::Initialize(const char* portName){
}

__asm void HidDevices::Finalize(){
    PUSH            {R4-R6,LR}
    MOV             R4, R0
    LDR             R6, =__cpp(&isInitialized)
    LDRB            R0, [R6]
    CMP             R0, #0
    BEQ             locret_107B2C
    LDR             R0, [R4]
    MOV             R5, #0
    STR             R5, [R4]
    SVC             0x23 ; '#'
    MOVS            R0, R0,LSR#31
    BLNE            __cpp(nndbgPanic)
    LDR             R0, [R4,#8]
    STR             R5, [R4,#8]
    SVC             0x23 ; '#'
    MOVS            R0, R0,LSR#31
    BLNE            __cpp(nndbgPanic)
    LDR             R0, [R4,#0x10]
    STR             R5, [R4,#0x10]
    SVC             0x23 ; '#'
    MOVS            R0, R0,LSR#31
    BLNE            __cpp(nndbgPanic)
    LDR             R0, [R4,#0x1C]
    STR             R5, [R4,#0x1C]
    SVC             0x23 ; '#'
    MOVS            R0, R0,LSR#31
    BLNE            __cpp(nndbgPanic)
    LDR             R0, [R4,#0x24]
    STR             R5, [R4,#0x24]
    SVC             0x23 ; '#'
    MOVS            R0, R0,LSR#31
    BLNE            __cpp(nndbgPanic)
    ADD             R0, R4, #0x2C ; ','
    BL              __cpp(nn::os::SharedMemoryBlock::Finalize)
    LDR             R4, =__cpp(&detail::Ipc::sSession)
    LDR             R0, [R4]
    SVC             0x23 ; '#'
    LDR             R1, =__cpp(&isInitialized)
    MOVS            R0, R0,LSR#31
    LDR             R1, [R1]
    STR             R1, [R4]
    BLNE            __cpp(nndbgPanic)
    STRB            R5, [R6]

locret_107B2C
    POP             {R4-R6,PC}
}

}
}
}