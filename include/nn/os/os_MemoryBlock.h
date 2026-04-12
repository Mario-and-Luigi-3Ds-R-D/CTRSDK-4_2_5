#pragma once

#include "nn/types.h"
#include "nn/Handle.h"
#include "nn/os/os_Types.h"
#include "nn/fnd/fnd_Intrusive.h"

namespace nn{
namespace os{

    class MemoryBlockBase : public nn::fnd::IntrusiveLinkedList{
    public:
        uptr mAddr;
        size_t mSize;
        bool mReadOnly;
        s8 rev[3];
    };

    class MemoryBlock : public MemoryBlockBase{
        void Initialize(size_t pSize);
        void Finalize();
        ~MemoryBlock();
    };

void InitializeMemoryBlock();

namespace{

bool sIsMemoryBlockEnabled;

}
}
}

typedef union nnosMemoryBlock{
    char buf[20];
    uint alignment_holder;
} nnosMemoryBlock;

void nnosMemoryBlockAllocate(nnosMemoryBlock* p, size_t size);