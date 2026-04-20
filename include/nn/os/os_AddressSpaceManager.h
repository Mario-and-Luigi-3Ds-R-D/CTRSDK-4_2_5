#pragma once

#include "nn/os/os_CriticalSection.h"
#include "nn/os/os_MemoryBlockBase.h"

namespace nn{
namespace os{
    class AddressSpaceManager{
    public:
        struct BlockList{
            nn::fnd::IntrusiveLinkedList::Item* mHead;
        };

        uptr mSpaceBegin;
        uptr mSpaceEnd;
        BlockList mBlockList;
        CriticalSection mLock;

        uptr Allocate(MemoryBlockBase *pBlock,size_t size,size_t skipSize);
        void Free(MemoryBlockBase *p);
        void Switch(MemoryBlockBase *pTo,MemoryBlockBase *pFrom);
    };

}
}

union nnosAddressSpaceManager{
    char buf[24];
    bit32 mAlignmentHolder;
};

extern "C" {
    void nnosAddressSpaceManagerInitialize(nnosAddressSpaceManager* p, uptr begin, size_t size);
    void nnosAddressSpaceManagerSwitch(nnosAddressSpaceManager* p, nnosMemoryBlockBase* pTo, nnosMemoryBlockBase* pFrom);
}