#pragma once

#include "nn/types.h"
#include "nn/Result.h"

namespace nn{
namespace os{
    
    uptr GetMemoryAddress(void);
    uptr GetAppMemorySize();
    size_t GetDeviceMemorySize(void);
    Result SetDeviceMemorySize(size_t);
    void SetupHeapForMemoryBlock(void);
    size_t GetHeapSize(void);
    Result SetHeapSize(size_t);
    int GetCodeRegionAddress(); // 100
    int GetCodeRegionSize(); // 100

namespace{

    int sDeviceMemoryAddress; // 0x0
    int sDeviceMemorySize; // 0x4
    int sDeviceHeapSize; // 0x8
    
}
}
}