#pragma once

#include "nn/types.h"
#include "nn/Result.h"

namespace nn{
namespace os{
    uptr GetMemoryAddress(void); // 100%
    uptr GetAppMemorySize(); // 100%
    size_t GetDeviceMemorySize(void); // 100%
    Result SetDeviceMemorySize(size_t); // ASM
    void SetupHeapForMemoryBlock(size_t); // ASM
    size_t GetHeapSize(void); // 100%
    uptr GetCodeRegionAddress(); // 100%
    size_t GetCodeRegionSize(); // 100%
    size_t GetUsingMemorySize(); // ASM

}
}