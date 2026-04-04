#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/os/os_Types.h"
#include "nn/os/os_MemoryBlock.h"

namespace nn{
namespace os{

    class SharedMemoryBlock : public nn::os::MemoryBlockBase, public nn::os::HandleObj{
    public:
        bool mSpaceAllocated;
        s8 reversed[3]; // lazy 2 spellLMAOLKMAO
        int reversed2;

        Result AttachAndMap(nn::Handle handle, size_t size, bool readOnly);
        Result Map(size_t size, bool readOnly);
        void Finalize();
        ~SharedMemoryBlock();
    };

namespace detail{
    void InitializeMemory();
}

}
}