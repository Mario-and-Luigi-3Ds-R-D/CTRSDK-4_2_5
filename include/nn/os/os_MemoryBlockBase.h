#pragma once

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

}
}


typedef union nnosMemoryBlockBase{

} nnosMemoryBlockBase;