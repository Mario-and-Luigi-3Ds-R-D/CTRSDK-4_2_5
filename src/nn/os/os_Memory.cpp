#include <nn/os/os_Memory.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/os/os_Default.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/svc/svc_Api.h>

extern "C" bit8 Load$$LR$$TEXT_SECTION$$Base[];
extern "C" bit8 Load$$LR$$TEXT_SECTION$$Length[];

namespace nn{
namespace os{
namespace {
    uptr sDeviceMemoryAddress = 0;
    size_t sDeviceMemorySize = 0;
    size_t sDeviceHeapSize = 0;

}

uptr GetMemoryAddress(){
    return os::sDeviceMemoryAddress;
}

uptr GetAppMemorySize(){
    return os::sDeviceMemorySize;
}

size_t GetDeviceMemorySize(){
    return os::sDeviceMemorySize;
}
// Sets/Initializes CTR Memory Size

Result SetDeviceMemorySize(size_t pSize){
    // TODO
}

// Sets/Initializes CTR Heap for MemoryBlock set of funcs.
void SetupHeapForMemoryBlock(size_t heapSize){
    // TODO
}

size_t GetHeapSize(){
    return os::sDeviceHeapSize;
}

uptr GetCodeRegionAddress(){
    //return reinterpret_cast<uptr>(Load$$LR$$TEXT_SECTION$$Base);
    return 0x100000;
}

size_t GetCodeRegionSize(){
    //return reinterpret_cast<size_t>(Load$$LR$$TEXT_SECTION$$Length);
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