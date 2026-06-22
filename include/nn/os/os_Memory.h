#pragma once

#include "nn/types.h"
#include "nn/Result.h"

namespace nn{
namespace os{
    uptr GetMemoryAddress();
    uptr GetAppMemorySize();
    size_t GetDeviceMemorySize();
    Result SetDeviceMemorySize(size_t);
    void SetupHeapForMemoryBlock(size_t);
    size_t GetHeapSize();
    uptr GetDeviceMemoryAddress();
    uptr GetCodeRegionAddress();
    size_t GetCodeRegionSize();
    size_t GetUsingMemorySize(); // ASM

}
}