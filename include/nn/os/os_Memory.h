#pragma once

#include "nn/types.h"
#include "nn/Result.h"

namespace nn{
namespace os{
    uptr GetMemoryAddress(void); // 100%
    uptr GetAppMemorySize(); // 100%
    size_t GetDeviceMemorySize(void); // 100%
    Result SetDeviceMemorySize(size_t); // ASM
    void SetupHeapForMemoryBlock(void); // ASM
    size_t GetHeapSize(void); // 100%
    Result SetHeapSize(size_t); // ASM
    int GetCodeRegionAddress(); // 100%
    int GetCodeRegionSize(); // 100%
    size_t GetUsingMemorySize(); // ASM

namespace{

    int sDeviceMemoryAddress; // 0x0
    int sDeviceMemorySize; // 0x4
    int sDeviceHeapSize; // 0x8
    
}
}
}