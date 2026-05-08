#pragma once

#include "nn/os/os_CriticalSection.h"
#include "nn/os/os_MemoryBlockBase.h"
#include "nn/fnd/fnd_Intrusive.h"

namespace nn{
namespace os{
    class AddressSpaceManager{
    public:
        typedef fnd::IntrusiveLinkedList<MemoryBlockBase> BlockList;
        typedef os::CriticalSection Lock;

        uptr mSpaceBegin;
        uptr mSpaceEnd;
        BlockList mBlockList;
        CriticalSection mLock;

        AddressSpaceManager() { mSpaceBegin = mSpaceEnd = 0; }
        uptr Allocate(MemoryBlockBase *pBlock,size_t size,size_t skipSize);
        void Free(MemoryBlockBase *p);
        void Switch(MemoryBlockBase *pTo,MemoryBlockBase *pFrom);
        void Initialize(uptr begin, size_t size);

    private:
        MemoryBlockBase* FindSpace(size_t size, size_t skipSize);
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