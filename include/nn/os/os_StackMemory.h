#pragma once

#include "nn/types.h"
#include "nn/os/os_AddressSpaceManager.h"

namespace nn{
namespace os{
namespace{
    nnosAddressSpaceManager sSpaceManager;

}
namespace detail{
    void InitializeStackMemory();
    void Switch(nnosMemoryBlockBase* pTo, nnosMemoryBlockBase* pFrom);
    
}

    class StackMemoryBlock : public nn::os::MemoryBlockBase{
    public:
        uptr mMemoryAddress;

        uptr GetStackBottom() const { return GetAddress() + GetSize(); }
    };
}
}

typedef union nnosStackMemoryBlock{
    char buf[20];
    uint alignment_holder;
} nnosStackMemoryBlock;

extern "C"{
void nnosStackMemoryBlockAllocate(nnosStackMemoryBlock* p, size_t size);
void nnosStackMemoryBlockFree(nnosStackMemoryBlock* p);
uptr nnosStackMemoryBlockGetStackBottom(nnosStackMemoryBlock* p);
void nnosStackMemoryBlockInitialize(nnosStackMemoryBlock* p);

}