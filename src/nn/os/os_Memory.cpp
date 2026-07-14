// Filename: os_Memory.cpp
//
// Project: Horizon Decompilation

#include <nn/os/os_Memory.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/os/os_Default.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/svc.h>

extern "C" bit8 Load$$LR$$TEXT_SECTION$$Base[];
extern "C" bit8 Load$$LR$$TEXT_SECTION$$Length[];

namespace nn{
namespace os{
namespace {
    uptr sDeviceMemoryAddress = 0;
    size_t sDeviceMemorySize = 0;
    size_t sDeviceHeapSize = 0;
}

uptr GetDeviceMemoryAddress(){
    NN_TASSERTMSG_(sDeviceMemoryAddress != NULL, "Device Memory is NOT Initialized.");
    return sDeviceMemoryAddress;
}

uptr GetAppMemorySize(){
    return sDeviceMemorySize;
}

size_t GetDeviceMemorySize(){
    return sDeviceMemorySize;
}

Result SetDeviceMemorySize(size_t size){
    // TODO
}

// Sets/Initializes CTR Heap for MemoryBlock set of funcs.
void SetupHeapForMemoryBlock(size_t heapSize){
    // TODO
}

size_t GetHeapSize(){
    return sDeviceHeapSize;
}

uptr GetCodeRegionAddress(){
    //return reinterpret_cast<uptr>(Load$$LR$$TEXT_SECTION$$Base);
    return 0x100000;
}

size_t GetCodeRegionSize(){
    //return reinterpret_cast<size_t>(Load$$LR$$TEXT_SECTION$$Length);
    return 0x53cb98;
}

size_t GetUsingMemorySize(){

}

}
}