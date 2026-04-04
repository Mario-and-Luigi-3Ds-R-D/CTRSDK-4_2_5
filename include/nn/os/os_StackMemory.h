#pragma once

#include "nn/types.h"
#include "nn/os/os_MemoryBlock.h"

namespace nn{
namespace os{

    class StackMemoryBlock : public nn::os::MemoryBlockBase{
    public:
        uptr mMemoryAddress;
    };

}
}

typedef union nnosStackMemoryBlock{
    char buf[20];
    uint alignment_holder;
} nnosStackMemoryBlock;

void nnosStackMemoryBlockAllocate(nnosStackMemoryBlock* p, size_t size);
void nnosStackMemoryBlockFree(nnosStackMemoryBlock* p);
void nnosStackMemoryBlockGetStack(nnosStackMemoryBlock* p);
void nnosStackMemoryBlockInitialize(nnosMemoryBlock* p);