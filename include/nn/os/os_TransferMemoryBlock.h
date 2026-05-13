#pragma once

#include "nn/types.h"
#include "nn/os/os_Types.h"
#include "nn/os/os_MemoryBlock.h"

namespace nn{
namespace os{
    class TransferMemoryBlock : public nn::os::MemoryBlockBase, public nn::os::HandleObj{
    public:
        bool mSpaceAllocated;
        s8 reseversed1[3];
        int reseversed2;

    public:
        void Finalize();
        void Initialize(void* p, size_t size, bit32 myPermission, bit32 otherPermission);
        ~TransferMemoryBlock();
        
    private:
        void Unmap(void);
        Result TryInitialize(void* p,size_t size,bit32 myPermission,bit32   otherPermission );
    };

}
}