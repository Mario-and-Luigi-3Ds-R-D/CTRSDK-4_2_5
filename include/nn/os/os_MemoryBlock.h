#pragma once

#include "nn/types.h"
#include "nn/Handle.h"
#include "nn/os/os_AddressSpaceManager.h"
#include "nn/os/os_Types.h"

#define NN_OS_MEMORY_PAGE_SIZE 0x1000

namespace nn{
namespace os{
extern nnosAddressSpaceManager sSpaceManager;

    class MemoryBlock : public MemoryBlockBase{
        void Initialize(size_t pSize);
        void Finalize();
        ~MemoryBlock();
    };

static size_t GetPageAlignedSize(size_t size) {
    return (size + NN_OS_MEMORY_PAGE_SIZE - 1) & ~(NN_OS_MEMORY_PAGE_SIZE - 1); 
}

void InitializeMemoryBlock(uptr begin, size_t size);

namespace detail{
bool IsMemoryBlockEnabled();
uptr AllocateFromMemoryBlockSpace(MemoryBlockBase* p, size_t size);
void FreeToMemorySpace(MemoryBlockBase* p);
void Switch(nnosMemoryBlockBase* pTo, nnosMemoryBlockBase* pFrom);

} // detail

namespace{
bool sIsMemoryBlockEnabled;

} // namespace
}
}

typedef union nnosMemoryBlock{
    char buf[20];
    uint alignment_holder;
} nnosMemoryBlock;

void nnosMemoryBlockAllocate(nnosMemoryBlock* p, size_t size);